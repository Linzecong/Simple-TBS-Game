/*基地窗口*/

#ifndef BASEWIDGET_H
#define BASEWIDGET_H
#include "ui_basewidget.h"
#include <QWidget>
#include<QMessageBox>
#include <QPropertyAnimation>
#include "../Framework/Player.h"
#include "../Framework/System.h"
#include "StudyWidget.h"
#include "TrainWidget.h"


namespace Ui {
class BaseWidget;
}

class BaseWidget : public QDialog{
public:
    Player* Me;
public:
    BaseWidget(Player* a,GameSystem* system);
    ~BaseWidget();

    Unit NewUnit;//用于判断是否有新单位
    int HasNewUnit;
    bool IsEnd;
    GameSystem* System;

    void mousePressEvent(QMouseEvent *e){}//重写pressevent，实现禁止拖动屏幕

private:
    Ui::BaseWidget *ui;

    void Study_Click();
    void Train_Click();
    void Base_Click();
    void End_Click(){IsEnd=1;this->close();}

    void showHelp(){
        QMessageBox::information(this,"haha","hahah");//帮助信息，还未写
    }

    void close_Click(){//关闭动画
        QPropertyAnimation* ActionWShow = new QPropertyAnimation(this, "geometry");
        ActionWShow->setDuration(500);
        ActionWShow->setStartValue(this->geometry());
        ActionWShow->setEndValue(QRect(this->width()/2,this->height(),0,0));
        ActionWShow->start(QAbstractAnimation::DeleteWhenStopped);
        connect(ActionWShow, SIGNAL(finished()), this, SLOT(close()));
    }

    bool check();
};

BaseWidget::BaseWidget(Player *a, GameSystem *system):ui(new Ui::BaseWidget){
    System=system;
    ui->setupUi(this);
    Me=a;
    HasNewUnit=-1;
    IsEnd=0;
    ui->Name->setText("玩家"+QString::number(Me->ID));

    int cost=0;
    for(int i=0;i<Me->UnitList.length();i++)
        cost+=Me->UnitList[i].MaintenanceCost;
    ui->Coin->setText(QString::number(Me->Coin)+"(-"+QString::number(cost)+")");

    ui->Capacity->setText(QString::number(Me->Capacity)+"(+"+QString::number(Me->Ori_Capacity)+"*"+QString::number(Me->BaseList.length())+")");

    for(int i=0;i<Me->BaseList.length();i++)
        ui->BaseList->addItem("基地"+QString::number(i+1));

    for(int i=0;i<Me->UnitList.length();i++)
        ui->UnitList->addItem((Me->UnitList[i].Name)+"  行动力："+QString::number(Me->UnitList[i].ActionPoint)+"  生命力："+QString::number(Me->UnitList[i].Life));

    connect(ui->StudyButton,&QPushButton::clicked,this,&BaseWidget::Study_Click);
    connect(ui->TrainUnitButton,&QPushButton::clicked,this,&BaseWidget::Train_Click);
    connect(ui->BaseList,&QListWidget::clicked,this,&BaseWidget::Base_Click);
    connect(ui->EndButton,&QPushButton::clicked,this,&BaseWidget::End_Click);
    connect(ui->CancelButton,&QPushButton::clicked,this,&BaseWidget::close_Click);
    connect(ui->HelpButton,&QPushButton::clicked,this,&BaseWidget::showHelp);

    ui->StudyButton->setEnabled(false);
    ui->TrainUnitButton->setEnabled(false);

    int H=QApplication::desktop()->height();
    int W=QApplication::desktop()->width();

    ui->StudyButton->setFixedSize(W/4,H/16);
   ui->TrainUnitButton->setFixedSize(W/4,H/16);
   ui->EndButton->setFixedSize(W/4,H/16);
   ui->CancelButton->setFixedSize(W/4,H/16);
    ui->HelpButton->setFixedSize(W/4,H/16);


}
BaseWidget::~BaseWidget(){
    delete ui;
}

void BaseWidget::Study_Click(){
    StudyWidget* study=new StudyWidget(Me);
    study->exec();
    if(study->IsStudied){
        ui->StudyButton->setEnabled(false);
        ui->TrainUnitButton->setEnabled(false);
        Me->BaseList[ui->BaseList->currentRow()].IsUsed=1;
    }
    int cost=0;
    for(int i=0;i<Me->UnitList.length();i++)
        cost+=Me->UnitList[i].MaintenanceCost;
    ui->Coin->setText(QString::number(Me->Coin)+"(-"+QString::number(cost)+")");
    delete study;
}

void BaseWidget::Train_Click(){
    TrainWidget* train=new TrainWidget(Me,Me->BaseList[ui->BaseList->currentRow()]);
    train->exec();

    if(train->IsTrained){
        ui->StudyButton->setEnabled(false);
        ui->TrainUnitButton->setEnabled(false);
        Me->BaseList[ui->BaseList->currentRow()].IsUsed=1;
        NewUnit=train->Choose;
        ui->UnitList->addItem((NewUnit.Name)+"  行动力："+QString::number(NewUnit.ActionPoint)+"  生命力："+QString::number(NewUnit.Life));
        HasNewUnit=(NewUnit.UnitType==Unit::NORMAL?0:1);


        if(HasNewUnit>=0){
            if(HasNewUnit==0)
                System->GameMap.GameMap[NewUnit.X][NewUnit.Y].NormalUnit.append(&System->Player_Turn->UnitList[System->Player_Turn->UnitList.length()-1]);
            else{
                System->GameMap.GameMap[NewUnit.X][NewUnit.Y].FlyUnit.append(&System->Player_Turn->UnitList[System->Player_Turn->UnitList.length()-1]);
            }
        }
    }

    int cost=0;
    for(int i=0;i<Me->UnitList.length();i++)
        cost+=Me->UnitList[i].MaintenanceCost;
    ui->Coin->setText(QString::number(Me->Coin)+"(-"+QString::number(cost)+")");
    delete train;
}

void BaseWidget::Base_Click(){
    if(Me->BaseList[ui->BaseList->currentRow()].IsUsed==0){
        if(check())
        ui->TrainUnitButton->setEnabled(true);
        else
        ui->TrainUnitButton->setEnabled(false);
        ui->StudyButton->setEnabled(true);
    }
    else{
        ui->StudyButton->setEnabled(false);
        ui->TrainUnitButton->setEnabled(false);
    }

}

bool BaseWidget::check(){
    int BX=Me->BaseList[ui->BaseList->currentRow()].X;
    int BY=Me->BaseList[ui->BaseList->currentRow()].Y;
    int sum=0;
    for(int i=0;i<Me->UnitList.length();i++)
        if(Me->UnitList[i].X==BX&&Me->UnitList[i].Y==BY)
            sum++;
    if(sum>=3)
        return false;
    else
        return true;
}

#endif // BASEWIDGET_H

/*基地窗口*/

#ifndef BASEWIDGET_H
#define BASEWIDGET_H
#include "ui_basewidget.h"
#include <QWidget>
#include<QMessageBox>
#include <QPropertyAnimation>
#include "../Framework/Player.h"
#include "StudyWidget.h"
#include "TrainWidget.h"

namespace Ui {
class BaseWidget;
}

class BaseWidget : public QDialog{
public:
    Player* Me;
public:
    BaseWidget(Player* a);
    ~BaseWidget();

    Unit NewUnit;//用于判断是否有新单位
    int HasNewUnit;
    bool IsEnd;

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
};

BaseWidget::BaseWidget(Player *a):ui(new Ui::BaseWidget){
    ui->setupUi(this);
    Me=a;
    HasNewUnit=-1;
    IsEnd=0;
    ui->Name->setText("玩家"+QString::number(Me->ID));

    int cost=0;
    for(int i=0;i<Me->UnitList.length();i++)
        cost+=Me->UnitList[i].MaintenanceCost;
    ui->Coin->setText(QString::number(Me->Coin)+"(-"+QString::number(cost)+")");

    ui->Capacity->setText(QString::number(Me->Capacity));

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
    }

    int cost=0;
    for(int i=0;i<Me->UnitList.length();i++)
        cost+=Me->UnitList[i].MaintenanceCost;
    ui->Coin->setText(QString::number(Me->Coin)+"(-"+QString::number(cost)+")");
    delete train;
}

void BaseWidget::Base_Click(){
    if(Me->BaseList[ui->BaseList->currentRow()].IsUsed==0){
        ui->StudyButton->setEnabled(true);
        ui->TrainUnitButton->setEnabled(true);
    }
    else{
        ui->StudyButton->setEnabled(false);
        ui->TrainUnitButton->setEnabled(false);
    }
}

#endif // BASEWIDGET_H

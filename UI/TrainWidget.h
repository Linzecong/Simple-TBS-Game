/*训练窗口*/

#ifndef TRAINWIDGET_H
#define TRAINWIDGET_H

#include <QDialog>
#include "ui_trainwidget.h"
#include "../Framework/Player.h"

namespace Ui {
class TrainWidget;
}

class TrainWidget : public QDialog{
public:
    Player* Me;
public:
     TrainWidget(Player* a,Base b);
    ~TrainWidget();
     void List_Click();
     void Train_Click();
     Unit Choose;
     bool IsTrained;
     Base MyBase;
private:
    Ui::TrainWidget *ui;
};

TrainWidget::TrainWidget(Player* a,Base b):ui(new Ui::TrainWidget){
    this->setWindowState(Qt::WindowMaximized);
    ui->setupUi(this);
    Me=a;
    MyBase=b;
    IsTrained=false;
    for(int i=0;i<Me->CanTrainList.length();i++)
        ui->CanTrainList->addItem((Unit(Me->CanTrainList[i]).Name));
    ui->TrainButton->setEnabled(false);
    connect(ui->CanTrainList,&QListWidget::clicked,this,&TrainWidget::List_Click);
    connect(ui->TrainButton,&QPushButton::clicked,this,&TrainWidget::Train_Click);

    int H=QApplication::desktop()->height();
    int W=QApplication::desktop()->width();
    ui->TrainButton->setFixedSize(W/4,H/16);


}

void TrainWidget::List_Click(){
    Choose=Unit(Me->CanTrainList[ui->CanTrainList->currentRow()]);
    ui->Des->setText((Choose.Des));
    ui->ActionPoint->setText(QString::number(Choose.ActionPoint));

    ui->ATKType->setText(Choose.ATKType==Unit::BOTH?"陆空":(Choose.ATKType==Unit::SKY?"对空":"对地"));
    ui->UnitType->setText(Choose.UnitType==Unit::NORMAL?"陆地":"飞行");
    ui->ATKAfterMove->setText(Choose.ATKAfterMove?"是":"否");
    ui->MoveAfterATK->setText(Choose.MoveAfterATK?"是":"否");
    ui->ATK_Grand->setText(QString::number(Choose.ATK_Grand));
    ui->ATK_Sky->setText(QString::number(Choose.ATK_Sky));
    ui->DEF->setText(QString::number(Choose.DEF));
    ui->Life->setText(QString::number(Choose.Life));
    ui->ATKRange->setText(QString::number(Choose.ATKRange));
    ui->ViewRange->setText(QString::number(Choose.ViewRange));
    ui->MaintenanceCost->setText(QString::number(Choose.MaintenanceCost));
    ui->Cost->setText(QString::number(Choose.Cost)+"/"+QString::number(Me->Coin));
    ui->Bonus->setText("加成表：地攻|空攻|防御\n");
    ui->Bonus->setText(ui->Bonus->text()+"草地    ："+QString::number(Choose.Bonus[0][0])+"      |"+QString::number(Choose.Bonus[0][1])+"      |"+QString::number(Choose.Bonus[0][2])+"\n");
    ui->Bonus->setText(ui->Bonus->text()+"沙地    ："+QString::number(Choose.Bonus[1][0])+"      |"+QString::number(Choose.Bonus[1][1])+"      |"+QString::number(Choose.Bonus[1][2])+"\n");
    ui->Bonus->setText(ui->Bonus->text()+"森林    ："+QString::number(Choose.Bonus[2][0])+"      |"+QString::number(Choose.Bonus[2][1])+"      |"+QString::number(Choose.Bonus[2][2])+"\n");



    if(Choose.Cost>Me->Coin)
        ui->TrainButton->setEnabled(false);
    else
        ui->TrainButton->setEnabled(true);
}

void TrainWidget::Train_Click(){
    Choose=Me->train(Choose.ID,MyBase);
    IsTrained=1;
    this->close();
}

TrainWidget::~TrainWidget(){
    delete ui;
}

#endif // TRAINWIDGET_H

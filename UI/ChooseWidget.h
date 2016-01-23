/*选择地图界面*/

#ifndef CHOOSEWIDGET_H
#define CHOOSEWIDGET_H
#include "BattleWidget.h"
#include <QWidget>
#include "MyItem.h"
#include "../Framework/Map.h"
#include "../Framework/Player.h"
#include "../Framework/System.h"
#include "ui_choosewidget.h"
#include <QComboBox>
#include <QtOpenGL/QGLWidget>

namespace Ui {
class ChooseWidget;
}

class ChooseWidget : public QWidget{
public:
    QGraphicsScene myscene;
    Map* mymap;
    QList<QList<MyItem*> > item;
    ChooseWidget();
    ~ChooseWidget();
    void setView();//查看地图
    void showField();//显示战斗窗口

private:
    Ui::ChooseWidget *ui;
    double Size;
};

ChooseWidget::ChooseWidget():ui(new Ui::ChooseWidget){
    ui->setupUi(this);
    ui->graphicsView->setScene(&myscene);
    connect(ui->comboBox,static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&ChooseWidget::setView);
    connect(ui->pushButton,&QPushButton::clicked,this,&ChooseWidget::showField);
    //ui->graphicsView->setViewport(new QGLWidget);
    Size=1;
    setView();
}

ChooseWidget::~ChooseWidget(){
    delete ui;
}

void ChooseWidget::setView(){
    int index=ui->comboBox->currentIndex();
    myscene.clear();
    item.clear();
    mymap= new Map(index+1);
    MyItem* temp;
    for(int i=0;i<=mymap->Width;i++){
        QList<MyItem*> templist;
        for(int j=0;j<=mymap->Height;j++){
            templist.append(temp);
        }
        item.append(templist);
    }
    for(int i=0;i<=mymap->Width;i++)
        for(int j=0;j<=mymap->Height;j++){
            item[i][j]=new MyItem(&mymap->GameMap[i][j],Size);
            if(i%2==0)
                item[i][j]->setPos(i*60*Size,j*70*Size);
            else
                item[i][j]->setPos(i*60*Size,j*70*Size+35*Size);
            myscene.addItem(item[i][j]);
        }
}

void ChooseWidget::showField(){
    int index=ui->comboBox->currentIndex()+1;
    int race=ui->comboBox_2->currentIndex()+1;
    Map tempMap(index);
    int player=1;//rand，设置玩家，其他为AI，暂无设计

    //设置玩家列表，设置基地列表
    QList<Player> tempPlayerList;
    for(int i=1;i<=tempMap.PlayerCount;i++){
        QList<Base> tempBase;
        for(int j=0;j<=tempMap.Width;j++)
            for(int k=0;k<=tempMap.Height;k++)
                if(tempMap.GameMap[j][k].Construction!=NULL)
                    if(tempMap.GameMap[j][k].Construction->Player==i)
                        tempBase.append(*(tempMap.GameMap[j][k].Construction));
        if(i==player){
            Player tempPlayer(i,race,tempBase,false);
            tempPlayerList.append(tempPlayer);
        }
        else{
            Player tempPlayer(i,1,tempBase,true);
            tempPlayerList.append(tempPlayer);
        }
    }

    GameSystem GSystem(tempMap,tempPlayerList);
    BattleWidget* a=new BattleWidget(GSystem);
    a->showMaximized();
    this->close();
}


#endif // CHOOSEWIDGET_H

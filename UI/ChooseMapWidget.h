/*选择地图界面*/

#ifndef CHOOSEWIDGET_H
#define CHOOSEWIDGET_H
#include "BattleWidget.h"
#include"ChooseRaceWidget.h"
#include <QWidget>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QVBoxLayout>
#include<QApplication>
#include<QDesktopWidget>
#include "MyItem.h"
#include "../Framework/Map.h"
#include "../Framework/Player.h"
#include "../Framework/System.h"




class ChooseWidget : public QWidget{
public:
    QGraphicsScene myscene;
    Map* mymap;
    QList<QList<MyItem*> > item;
    ChooseWidget();
    ~ChooseWidget();

    void setView();//查看地图
    void PreviousClick();
    void NextClick();
    void showRace();//显示种族选择窗口

    int CurrentMap;

private:
    QVBoxLayout *MainLayout;
    QHBoxLayout *ChooseLayout;
    QPushButton *Previous;
    QLabel *MapName;
    QPushButton *Next;
    QPushButton *GoOn;
    QGraphicsView *GraphicsView;

    double Size;
};

ChooseWidget::ChooseWidget(){
    MainLayout=new QVBoxLayout(this);
    ChooseLayout=new QHBoxLayout(this);
    Previous=new QPushButton("",this);
    MapName=new QLabel("",this);
    Next=new QPushButton("",this);
    GoOn=new QPushButton("",this);

    GraphicsView=new QGraphicsView(&myscene,this);

    connect(Previous,&QPushButton::clicked,this,&ChooseWidget::PreviousClick);
    connect(Next,&QPushButton::clicked,this,&ChooseWidget::NextClick);
    connect(GoOn,&QPushButton::clicked,this,&ChooseWidget::showRace);


    ChooseLayout->addWidget(Previous);
    ChooseLayout->addWidget(MapName);
    ChooseLayout->addWidget(Next);

    int H=QApplication::desktop()->height();
    int W=QApplication::desktop()->width();

    MainLayout->addSpacing(H/19);
    MainLayout->addLayout(ChooseLayout);
    MainLayout->addWidget(GraphicsView);
    MainLayout->addWidget(GoOn,0,Qt::AlignCenter);
    this->setLayout(MainLayout);

    this->setStyleSheet("background:transparent;border-image:url(:/pixmap/background/choosemap.png);");

    Previous->setFixedSize(W/4,H/16);
    MapName->setFixedSize(W/4,H/16);
    MapName->setAlignment(Qt::AlignCenter);
    Next->setFixedSize(W/4,H/16);
    GoOn->setFixedSize(W/3,H/16);

    Previous->setStyleSheet("QPushButton{background: transparent;border-image:url(:/pixmap/button/previous1.png);}QPushButton:pressed{background: transparent;border-image:url(:/pixmap/button/previous2.png);}");
    Next->setStyleSheet("QPushButton{background: transparent;border-image:url(:/pixmap/button/next1.png);}QPushButton:pressed{background: transparent;border-image:url(:/pixmap/button/next2.png);}");
    GoOn->setStyleSheet("QPushButton{background: transparent;border-image:url(:/pixmap/button/goon1.png);}QPushButton:pressed{background: transparent;border-image:url(:/pixmap/button/goon2.png);}");
    MapName->setStyleSheet("border-image:url(:/pixmap/solid.png);");

    GraphicsView->setBackgroundBrush(QBrush(QColor(97,75,46)));

   // ui->graphicsView->setViewport(new QGLWidget);
    GraphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    GraphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    Previous->setFocusPolicy(Qt::NoFocus);
    Next->setFocusPolicy(Qt::NoFocus);
    GoOn->setFocusPolicy(Qt::NoFocus);

    Size=1;
    CurrentMap=0;
    setView();
}

ChooseWidget::~ChooseWidget(){
}

void ChooseWidget::setView(){
    int index=CurrentMap;
    myscene.clear();
    item.clear();
    mymap= new Map(index+1);

    MapName->setText(QString::number(index+1)+"/2:"+mymap->Name);

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

void ChooseWidget::PreviousClick(){
    CurrentMap--;
    if(CurrentMap==-1)
        CurrentMap=1;
    setView();
}

void ChooseWidget::NextClick(){
    CurrentMap++;
    if(CurrentMap==2)
        CurrentMap=0;
    setView();
}

void ChooseWidget::showRace(){
    ChooseRaceWidget* temp=new ChooseRaceWidget(CurrentMap+1);
    temp->show();
    this->close();
}


#endif // CHOOSEWIDGET_H

#ifndef CHOOSERACEWIDGET
#define CHOOSERACEWIDGET
#include "BattleWidget.h"
#include <QWidget>
#include "../Framework/Map.h"
#include "../Framework/Player.h"
#include "../Framework/System.h"
#include<QLabel>
#include<QPushButton>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<functional>
#include<QApplication>
#include<QDesktopWidget>

class ChooseRaceWidget : public QWidget{
public:

    ChooseRaceWidget(int map);
    ~ChooseRaceWidget(){}
    QVBoxLayout* MainLayout;

    QList<QHBoxLayout* > RaceLayout;
    Map* tempMap;

    std::function<void()> preclick[4];
    std::function<void()> nextclick[4];

    void showField();
    int RaceList[4];

    QHBoxLayout* tempRaceLayout[4];
    QPushButton* tempPreButton[4];
    QPushButton* tempNextButton[4];
    QLabel* tempRace[4];
    QLabel* tempName[4];
};

ChooseRaceWidget::ChooseRaceWidget(int map){
    this->setStyleSheet("background:transparent;border-image:url(:/pixmap/background/chooserace.png);");

    tempMap=new Map(map);
    int H=QApplication::desktop()->height();
    int W=QApplication::desktop()->width();
    MainLayout=new QVBoxLayout(this);
    MainLayout->addSpacing(H/19);
    preclick[0]=[&](){if(--RaceList[0]==-1)RaceList[0]=3;if(RaceList[0]==1)tempRace[0]->setText("人类");if(RaceList[0]==2)tempRace[0]->setText("恶魔");if(RaceList[0]==3)tempRace[0]->setText("天使");if(RaceList[0]==0)tempRace[0]->setText("随机");};
    nextclick[0]=[&](){if(++RaceList[0]==4)RaceList[0]=0;if(RaceList[0]==1)tempRace[0]->setText("人类");if(RaceList[0]==2)tempRace[0]->setText("恶魔");if(RaceList[0]==3)tempRace[0]->setText("天使");if(RaceList[0]==0)tempRace[0]->setText("随机");};
    preclick[1]=[&](){if(--RaceList[1]==-1)RaceList[1]=3;if(RaceList[1]==1)tempRace[1]->setText("人类");if(RaceList[1]==2)tempRace[1]->setText("恶魔");if(RaceList[1]==3)tempRace[1]->setText("天使");if(RaceList[1]==0)tempRace[1]->setText("随机");};
    nextclick[1]=[&](){if(++RaceList[1]==4)RaceList[1]=0;if(RaceList[1]==1)tempRace[1]->setText("人类");if(RaceList[1]==2)tempRace[1]->setText("恶魔");if(RaceList[1]==3)tempRace[1]->setText("天使");if(RaceList[1]==0)tempRace[1]->setText("随机");};
    preclick[2]=[&](){if(--RaceList[2]==-1)RaceList[2]=3;if(RaceList[2]==1)tempRace[2]->setText("人类");if(RaceList[2]==2)tempRace[2]->setText("恶魔");if(RaceList[2]==3)tempRace[2]->setText("天使");if(RaceList[2]==0)tempRace[2]->setText("随机");};
    nextclick[2]=[&](){if(++RaceList[2]==4)RaceList[2]=0;if(RaceList[2]==1)tempRace[2]->setText("人类");if(RaceList[2]==2)tempRace[2]->setText("恶魔");if(RaceList[2]==3)tempRace[2]->setText("天使");if(RaceList[2]==0)tempRace[2]->setText("随机");};
    preclick[3]=[&](){if(--RaceList[3]==-1)RaceList[3]=3;if(RaceList[3]==1)tempRace[3]->setText("人类");if(RaceList[3]==2)tempRace[3]->setText("恶魔");if(RaceList[3]==3)tempRace[3]->setText("天使");if(RaceList[3]==0)tempRace[3]->setText("随机");};
    nextclick[3]=[&](){if(++RaceList[3]==4)RaceList[3]=0;if(RaceList[3]==1)tempRace[3]->setText("人类");if(RaceList[3]==2)tempRace[3]->setText("恶魔");if(RaceList[3]==3)tempRace[3]->setText("天使");if(RaceList[3]==0)tempRace[3]->setText("随机");};

    for(int i=0;i<tempMap->PlayerCount;i++){
        RaceList[i]=0;
        tempRaceLayout[i]=new QHBoxLayout(this);
        tempPreButton[i]=new QPushButton("",this);
        tempNextButton[i]=new QPushButton("",this);
        tempRace[i]=new QLabel("随机",this);
        tempName[i]=new QLabel("玩家",this);

        tempPreButton[i]->setFixedSize(W/4,H/16);
        tempRace[i]->setFixedSize(W/4,H/16);
        tempNextButton[i]->setFixedSize(W/4,H/16);
        tempRace[i]->setAlignment(Qt::AlignCenter);

        tempName[i]->setAlignment(Qt::AlignCenter);

        tempPreButton[i]->setFocusPolicy(Qt::NoFocus);
        tempNextButton[i]->setFocusPolicy(Qt::NoFocus);


        tempPreButton[i]->setStyleSheet("QPushButton{background: transparent;border-image:url(:/pixmap/button/previous1.png);}QPushButton:pressed{background: transparent;border-image:url(:/pixmap/button/previous2.png);}");
        tempNextButton[i]->setStyleSheet("QPushButton{background: transparent;border-image:url(:/pixmap/button/next1.png);}QPushButton:pressed{background: transparent;border-image:url(:/pixmap/button/next2.png);}");
        tempRace[i]->setStyleSheet("border-image:url(:/pixmap/solid.png);");
        tempName[i]->setStyleSheet("border-image:url(:/pixmap/solid.png);");

        if(i>0)
            tempName[i]->setText("电脑"+QString::number(i));
        tempRaceLayout[i]->addWidget(tempPreButton[i]);
        tempRaceLayout[i]->addWidget(tempRace[i]);
        tempRaceLayout[i]->addWidget(tempNextButton[i]);
        MainLayout->addWidget(tempName[i],0,Qt::AlignCenter);
        MainLayout->addLayout(tempRaceLayout[i]);
        connect(tempPreButton[i],&QPushButton::clicked,this,ChooseRaceWidget::preclick[i]);
        connect(tempNextButton[i],&QPushButton::clicked,this,ChooseRaceWidget::nextclick[i]);
    }
    QPushButton* Begin=new QPushButton("",this);
    Begin->setFixedSize(W/3,H/16);
    Begin->setFocusPolicy(Qt::NoFocus);
    Begin->setStyleSheet("QPushButton{background: transparent;border-image:url(:/pixmap/button/goon1.png);}QPushButton:pressed{background: transparent;border-image:url(:/pixmap/button/goon2.png);}");


    MainLayout->addWidget(Begin,0,Qt::AlignCenter);
    this->setLayout(MainLayout);
    connect(Begin,&QPushButton::clicked,this,&ChooseRaceWidget::showField);
}



void ChooseRaceWidget::showField(){

    //设置玩家列表，设置基地列表
    QList<Player> tempPlayerList;
    for(int i=1;i<=tempMap->PlayerCount;i++){
        QList<Base> tempBase;
        for(int j=0;j<=tempMap->Width;j++)
            for(int k=0;k<=tempMap->Height;k++)
                if(tempMap->GameMap[j][k].Construction!=NULL)
                    if(tempMap->GameMap[j][k].Construction->Player==i)
                        tempBase.append(*(tempMap->GameMap[j][k].Construction));
        if(i==1){
            Player tempPlayer(i,RaceList[i-1],tempBase,false);
            tempPlayerList.append(tempPlayer);
        }
        else{
            Player tempPlayer(i,RaceList[i-1],tempBase,true);
            tempPlayerList.append(tempPlayer);
        }
    }

    GameSystem GSystem(tempMap->ID,tempPlayerList);
    BattleWidget* a=new BattleWidget(GSystem);
    a->showFullScreen();
    this->close();
}


#endif // CHOOSERACEWIDGET




/*玩家*/
/*此头文件包含对玩家的定义*/

#ifndef PLAYER_H
#define PLAYER_H
#include"Unit.h"
#include"Base.h"
#include"Technology.h"
#include<QList>

class Player{
public:
    int ID;//玩家编号
    int Race;//玩家种族
    int Coin;//资金
    int Capacity;//产能
    int Ori_Capacity;//产能
    QList<Unit> UnitList;//已有单位列表
    QList<Base> BaseList;//已有基地列表
    QList<int> CanTrainList;//可训练的单位ID列表
    QList<int> StudiedList;//已研究ID列表
    QList<int> CanStudyList;//可研究ID列表

    int IsAI;//是否是电脑，暂无设计
    bool IsDead;//是否已经死亡

public:
    Player(int id,int race, QList<Base> baselist, int ai);
    ~Player(){}

    void study(int tech);
    Unit train(int id, Base base);
};

Player::Player(int id, int race, QList<Base> baselist, int ai):IsAI(ai),ID(id),Race(race),IsDead(false),BaseList(baselist){

    /*********此处初始化玩家科技和各种数值***************/
    switch(Race){
    case 1://人类
        StudiedList.append(100);
        CanStudyList.append(101);
        CanTrainList.append(101);
        Coin=100;
        Capacity=50;Ori_Capacity=10;
        break;
    case 2://恶魔
        StudiedList.append(200);
        CanStudyList.append(201);
        CanTrainList.append(201);
        Coin=100;
        Capacity=50;Ori_Capacity=10;
        break;
    case 3://天使
        StudiedList.append(300);
        CanStudyList.append(301);
        CanTrainList.append(301);
        Coin=100;
        Capacity=50;Ori_Capacity=10;
        break;
    case 0://随机
        Race=1;
        StudiedList.append(100);
        CanStudyList.append(101);
        CanTrainList.append(101);
        Coin=100;
        Capacity=50;Ori_Capacity=10;
        break;
    }


}

void Player::study(int tech){
    StudiedList.append(tech);
    Coin-=Technology(tech).Cost;
    CanStudyList.removeOne(tech);

    /*********此处为学习科技后获得的效果*************/
    switch(tech) {
    case 101:
        CanTrainList.append(102);
        CanStudyList.append(102);
        CanStudyList.append(103);
        break;
    case 102:
        Capacity+=5*BaseList.length();
        break;
    case 103:
        Capacity+=5*BaseList.length();
        CanStudyList.append(104);
        break;
    case 104:
        CanTrainList.append(103);
        CanStudyList.append(105);

        break;
    case 105:
        CanTrainList.append(104);
        CanStudyList.append(106);
        break;
    case 106:
        for(int i=0;i<UnitList.length();i++)
            UnitList[i].Life=UnitList[i].Ori_Life;
        CanStudyList.append(107);
        break;
    case 107:
        CanTrainList.append(105);
        Capacity+=20*BaseList.length();
        CanStudyList.append(108);
        break;
    case 108:
        CanTrainList.append(106);
        Capacity+=20*BaseList.length();
        CanStudyList.append(109);
        break;
    case 109:
        Capacity+=50*BaseList.length();
        CanStudyList.append(110);
        break;
    case 110:
        CanTrainList.append(107);
        for(int i=0;i<UnitList.length();i++)
            UnitList[i].DEF++;
        break;



    case 201:
        CanTrainList.append(202);
        CanStudyList.append(202);
        CanStudyList.append(203);
        break;
    case 202:
        for(int i=0;i<UnitList.length();i++)
            if(UnitList[i].ID==201){
                UnitList[i].DEF--;
                UnitList[i].Ori_ATK_Grand++;
            }
        break;
    case 203:
        Capacity+=10*BaseList.length();
        CanStudyList.append(204);
        break;
    case 204:
        CanTrainList.append(203);
        CanStudyList.append(205);

        break;
    case 205:
        CanTrainList.append(204);
        CanStudyList.append(206);
        break;
    case 206:
        for(int i=0;i<UnitList.length();i++)
            if(UnitList[i].ID==203)
            UnitList[i].ATKRange++;
        CanStudyList.append(207);
        break;
    case 207:
        CanTrainList.append(205);
        Capacity+=20*BaseList.length();
        CanStudyList.append(208);
        break;
    case 208:
        CanTrainList.append(206);
        Capacity+=20*BaseList.length();
        CanStudyList.append(209);
        break;
    case 209:
        Capacity+=40*BaseList.length();
        CanStudyList.append(210);
        break;
    case 210:
        CanTrainList.append(207);
        for(int i=0;i<UnitList.length();i++)
            UnitList[i].Life==UnitList[i].Ori_Life;
        break;


    case 301:
        CanTrainList.append(302);
        CanStudyList.append(302);
        CanStudyList.append(303);
        break;
    case 302:
        for(int i=0;i<UnitList.length();i++)
            UnitList[i].Ori_ATK_Grand++;
        break;
    case 303:
        Capacity+=10*BaseList.length();
        CanStudyList.append(304);
        break;
    case 304:
        CanTrainList.append(303);
        CanStudyList.append(305);

        break;
    case 305:
        CanTrainList.append(304);
        CanStudyList.append(306);
        break;
    case 306:
        for(int i=0;i<UnitList.length();i++)
            UnitList[i].Life=UnitList[i].Ori_Life;
        CanStudyList.append(307);
        break;
    case 307:
        CanTrainList.append(305);
        Capacity+=20*BaseList.length();
        CanStudyList.append(308);
        break;
    case 308:
        CanTrainList.append(306);
        Capacity+=30*BaseList.length();
        CanStudyList.append(309);
        break;
    case 309:
        Capacity+=40*BaseList.length();
        for(int i=0;i<UnitList.length();i++)
            UnitList[i].Life=UnitList[i].Ori_Life;
        CanStudyList.append(310);
        break;
    case 310:
        CanTrainList.append(307);
        Capacity+=80*BaseList.length();
        break;
    }
}

Unit Player::train(int id,Base base){
    Unit temp(id,ID,base.X,base.Y);
    temp.ActionPoint=0;
    temp.IsATKed=1;
    temp.IsCure=1;
    Coin-=temp.Cost;
    this->UnitList.append(temp);
    return temp;
}

#endif // PLAYER

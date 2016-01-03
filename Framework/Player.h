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
    Player(int id, QList<Base> baselist, int ai);
    ~Player(){}

    void study(int tech);
    Unit train(int id, Base base);
};

Player::Player(int id, QList<Base> baselist, int ai):IsAI(ai),ID(id),IsDead(false),BaseList(baselist){
    /*********此处初始化玩家科技和各种数值***************/
    StudiedList.append(0);
    CanStudyList.append(1);
    CanTrainList.append(1);
    Coin=50;
    Capacity=Ori_Capacity=5;
}

void Player::study(int tech){
    StudiedList.append(tech);
    Coin-=Technology(tech).Cost;
    CanStudyList.removeOne(tech);

    /*********此处为学习科技后获得的效果*************/
    switch(tech) {
    case 0:
        CanTrainList.append(1);
        CanStudyList.append(1);
        break;
    case 1:
        CanTrainList.append(2);
        CanStudyList.append(2);
        break;
    case 2:
        CanTrainList.append(3);
        CanTrainList.append(4);
        CanStudyList.append(3);
        break;
    case 3:
        CanTrainList.append(5);
        CanStudyList.append(4);
        break;
    case 4:
        Capacity+=10;
        break;
    }
}

Unit Player::train(int id,Base base){
    Unit temp(id,ID,base.X,base.Y);
    Coin-=temp.Cost;
    this->UnitList.append(temp);
    return temp;
}

#endif // PLAYER

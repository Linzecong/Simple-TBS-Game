/*系统*/
/*此头文件包含对整个游戏系统，游戏逻辑的定义*/

#ifndef SYSTEM_H
#define SYSTEM_H
#include"Map.h"
#include"Player.h"

class GameSystem{
public:
    Map GameMap;//地图
    QList<Player> PlayerList;//玩家列表
    int Turn;//回合
    Player* Player_Turn;//当前回合的玩家

public:
    GameSystem(Map map, QList<Player> list);
    GameSystem(){}
    ~GameSystem(){}

    void moveTo(int x,int y,Unit* unit);//移动单位
    bool canMoveTo(int x,int y,Unit* unit);//判断单位是否能移动到指定位置

    int attack(Unit* atk, Unit* def, Player *atkplayer, Player* defplayer, int range);//攻击，返回伤害值
    static bool canAttack(Unit* atk, Unit* def, int range);//判断两个单位的类型是否能攻击
    void turnout();//结束回合
};

GameSystem::GameSystem(Map map,QList<Player> list){
    GameMap=map;
    PlayerList=list;
    Turn=0;
    Player_Turn=&PlayerList[0];
}

void GameSystem::moveTo(int x, int y, Unit* unit){
    switch(unit->UnitType){
    case Unit::NORMAL:
        GameMap.GameMap[unit->X][unit->Y].NormalUnit.removeOne(unit);
        unit->X=x;
        unit->Y=y;
        GameMap.GameMap[x][y].NormalUnit.append(unit);
        break;
    case Unit::FLY:
        GameMap.GameMap[unit->X][unit->Y].FlyUnit.removeOne(unit);
        unit->X=x;
        unit->Y=y;
        GameMap.GameMap[x][y].FlyUnit.append(unit);
        break;
    }
    if(unit->ATKAfterMove==false)//如果不能攻击后移动
        unit->IsATKed=true;
}

bool GameSystem::canMoveTo(int x, int y, Unit* unit){
    if(unit->canMove()==false)
        return false;
    Map* map= this->GameMap.findWay(unit->X,unit->Y);
    int temp=map->GameMap[x][y].Data;
    delete map;
    if(temp>unit->ActionPoint)
        return false;
    else
        return true;
}

int GameSystem::attack(Unit *atk, Unit *def,Player* atkplayer,Player* defplayer,int range){
    int BonusATKType=GameMap.GameMap[atk->X][atk->Y].Type;
    int BonusDEFType=GameMap.GameMap[def->X][def->Y].Type;

    int damage=0;
    if(def->UnitType!=Unit::FLY)
        damage=atk->ATK_Grand+atk->Bonus[BonusATKType][0]-def->DEF-def->Bonus[BonusDEFType][2];
    else
        damage=atk->ATK_Sky+atk->Bonus[BonusATKType][1]-def->DEF-def->Bonus[BonusDEFType][2];

    if(damage<0)
        damage=0;

    def->Life-=damage;

    //攻击方也会受到伤害
    if(canAttack(def,atk,range)){
        int damage1=0;
        if(atk->UnitType!=Unit::FLY)
            damage1=def->ATK_Grand+def->Bonus[BonusDEFType][0]-atk->DEF-atk->Bonus[BonusATKType][2];
        else
            damage1=def->ATK_Sky+def->Bonus[BonusDEFType][1]-atk->DEF-atk->Bonus[BonusATKType][2];


        if(damage1<0)
            damage1=0;

        atk->Life-=damage1;
    }

    //如果死亡
    if(def->Life<=0){
        if(def->UnitType==Unit::NORMAL)
            GameMap.GameMap[def->X][def->Y].NormalUnit.removeOne(def);
        else
            GameMap.GameMap[def->X][def->Y].FlyUnit.removeOne(def);
        defplayer->UnitList.removeOne(*def);
    }

    if(atk->Life<=0){
        if(atk->UnitType==Unit::NORMAL)
            GameMap.GameMap[atk->X][atk->Y].NormalUnit.removeOne(atk);
        else
            GameMap.GameMap[atk->X][atk->Y].FlyUnit.removeOne(atk);
        atkplayer->UnitList.removeOne(*atk);
    }

    atk->IsATKed=true;
    if(atk->MoveAfterATK==false)
        atk->ActionPoint=0;

    return damage;
}

bool GameSystem::canAttack(Unit *atk, Unit *def,int range){
    if((atk->ATKType==Unit::GRAND||atk->ATKType==Unit::BOTH)&&(def->UnitType==Unit::NORMAL)&&(atk->ATKRange>=range))
        return true;
    if((atk->ATKType==Unit::SKY||atk->ATKType==Unit::BOTH)&&(def->UnitType==Unit::FLY)&&(atk->ATKRange>=range))
        return true;
    return false;
}

void GameSystem::turnout(){
    /*初始化当前玩家各种数值*/
    int cost=0;
    for(int i=0;i<Player_Turn->UnitList.length();i++){
        cost+=Player_Turn->UnitList[i].MaintenanceCost;
        Player_Turn->UnitList[i].ActionPoint=Player_Turn->UnitList[i].Ori_ActionPoint;
        Player_Turn->UnitList[i].IsATKed=0;
        if(Player_Turn->UnitList[i].IsCure=1){
            Player_Turn->UnitList[i].Life+=Player_Turn->UnitList[i].CurePoint;
            if(Player_Turn->UnitList[i].Life>Player_Turn->UnitList[i].Ori_Life)
                Player_Turn->UnitList[i].Life=Player_Turn->UnitList[i].Ori_Life;
            Player_Turn->UnitList[i].IsCure=0;
        }
    }
    Player_Turn->Coin-=cost;
    Player_Turn->Coin+=Player_Turn->Capacity;
    Player_Turn->Capacity+=10;
    Player_Turn->Ori_Capacity+=10;
    for(int i=0;i<Player_Turn->BaseList.length();i++){
        Player_Turn->BaseList[i].IsUsed=0;
    }

    /*循环玩家列表，找到下一个存活的玩家，并指定当前玩家*/
    do{
        int temp=Player_Turn->ID+1;
        if(temp>PlayerList.length()){
            temp=1;
            Turn++;
        }
        else
            Turn++;
        for(int i=1;i<=PlayerList.length();i++)
            if(temp==PlayerList[i-1].ID)
                Player_Turn=&PlayerList[i-1];
    }while(Player_Turn->IsDead);

}

#endif // HEXAGON_H

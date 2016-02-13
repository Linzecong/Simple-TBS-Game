/*单位*/
/*此头文件定义各单位的信息*/

#ifndef UNIT_H
#define UNIT_H
#include<QString>

class Unit{
public:
    int ID;//单位ID
    int MaintenanceCost;//维修费
    int Cost;//生产所需金钱
    QString Name;//名字
    QString Des;//介绍

    int Player;//所属玩家

    enum ATKTYPE{GRAND,SKY,BOTH}ATKType;//攻击类型（对空对地）
    enum UNITTYPE{NORMAL,FLY}UnitType;//单位类型

    int ATK_Grand;//目前地面攻击力
    int ATK_Sky;//目前对空攻击力
    int ATK_Base;//基地攻击力
    int DEF;//目前防御力

    int Bonus[3][3];//地形攻击防御加成

    int Life;//目前生命值
    int CurePoint;//每次治疗量
    int IsCure;//是否治疗

    int ATKRange;//目前攻击距离
    int ActionPoint;//目前行动力
    int ViewRange;//目前视野范围

    bool ATKAfterMove;//是否可以移动后攻击
    bool MoveAfterATK;//是否可以攻击后移动

    int Ori_ATK_Grand;//基础数值
    int Ori_ATK_Sky;
    int Ori_DEF;
    int Ori_Life;
    int Ori_ATKRange;
    int Ori_ActionPoint;
    int Ori_ViewRange;

    bool ATKAble;//是否可以攻击
    bool IsATKed;//是否已经攻击

    int X;//目前位置
    int Y;

public:
    bool operator==(Unit temp);
    bool canAttack();//判断此单位是否能攻击
    bool canMove();//判断此单位是否能移动
    Unit(int id,int player,int x,int y);
};

bool Unit::operator==(Unit temp){
    if(ID==temp.ID&&DEF==temp.DEF&&Life==temp.Life)
        if(ATKRange==temp.ATKRange&&ActionPoint==temp.ActionPoint)
            if(ATK_Grand==temp.ATK_Grand&&ATK_Sky==temp.ATK_Sky)
                if(ViewRange==temp.ViewRange&&IsATKed==temp.IsATKed)
                    return true;
    return false;
}

bool Unit::canAttack(){
    if(ATKAble==true&&IsATKed==false)
        return true;
    return false;

}

bool Unit::canMove(){
    if(IsATKed==true&&MoveAfterATK==true&&ActionPoint>0)
        return true;
    if(IsATKed==false&&ActionPoint>0)
        return true;
    return false;
}

Unit::Unit(int id=1, int player=0, int x=0, int y=0):ID(id),Player(player),X(x),Y(y),IsCure(0),IsATKed(false){
    /****************此处定义详细的单位信息****************/
    switch(id){
    case 101:
        MaintenanceCost=2;
        Cost=20;
        Name="步兵";
        Des="这是一个机枪兵";
        ATKType=GRAND;//攻击类型（对空对地）
        UnitType=NORMAL;//单位类型
        ATKAfterMove=true;//是否可以移动后攻击
        MoveAfterATK=false;//是否可以攻击后移动
        ATK_Grand=Ori_ATK_Grand=5;//基础数值
        ATK_Sky=Ori_ATK_Sky=0;
        ATK_Base=2;
        DEF=Ori_DEF=2;

        Bonus[0][0]=0;Bonus[0][1]=0;Bonus[0][2]=0;
        Bonus[1][0]=0;Bonus[1][1]=0;Bonus[1][2]=0;
        Bonus[2][0]=0;Bonus[2][1]=0;Bonus[2][2]=1;

        Life=Ori_Life=5;
        CurePoint=1;
        ATKRange=Ori_ATKRange=1;
        ActionPoint=Ori_ActionPoint=5;
        ViewRange=Ori_ViewRange=2;
        ATKAble=true;
        break;
    case 102:
        MaintenanceCost=5;
        Cost=40;
        Name="火箭兵";
        Des="这是一个防空兵";
        ATKType=BOTH;//攻击类型（对空对地）
        UnitType=NORMAL;//单位类型
        ATKAfterMove=false;//是否可以移动后攻击
        MoveAfterATK=false;//是否可以攻击后移动
        ATK_Grand=Ori_ATK_Grand=5;//基础数值
        ATK_Sky=Ori_ATK_Sky=3;
        ATK_Base=4;
        DEF=Ori_DEF=1;
        Bonus[0][0]=0;Bonus[0][1]=1;Bonus[0][2]=0;
        Bonus[1][0]=0;Bonus[1][1]=0;Bonus[1][2]=0;
        Bonus[2][0]=0;Bonus[2][1]=0;Bonus[2][2]=0;
        Life=Ori_Life=5;
        CurePoint=1;
        ATKRange=Ori_ATKRange=2;
        ActionPoint=Ori_ActionPoint=4;
        ViewRange=Ori_ViewRange=2;
        ATKAble=true;
        break;
    case 103:
        MaintenanceCost=12;
        Cost=80;
        Name="机甲战士";
        Des="这是坦克";
        ATKType=GRAND;//攻击类型（对空对地）
        UnitType=NORMAL;//单位类型
        ATKAfterMove=true;//是否可以移动后攻击
        MoveAfterATK=false;//是否可以攻击后移动
        ATK_Grand=Ori_ATK_Grand=6;//基础数值
        ATK_Sky=Ori_ATK_Sky=0;
        ATK_Base=5;
        DEF=Ori_DEF=2;
        Bonus[0][0]=0;Bonus[0][1]=0;Bonus[0][2]=0;
        Bonus[1][0]=0;Bonus[1][1]=0;Bonus[1][2]=0;
        Bonus[2][0]=0;Bonus[2][1]=0;Bonus[2][2]=0;
        Life=Ori_Life=8;
        CurePoint=1;
        ATKRange=Ori_ATKRange=1;
        ActionPoint=Ori_ActionPoint=4;
        ViewRange=Ori_ViewRange=2;
        ATKAble=true;
        break;
    case 104:
        MaintenanceCost=20;
        Cost=120;
        Name="全能战士";
        Des="这是轰炸机";
        ATKType=BOTH;//攻击类型（对空对地）
        UnitType=NORMAL;//单位类型
        ATKAfterMove=true;//是否可以移动后攻击
        MoveAfterATK=false;//是否可以攻击后移动
        ATK_Grand=Ori_ATK_Grand=6;//基础数值
        ATK_Sky=Ori_ATK_Sky=4;
        ATK_Base=8;
        DEF=Ori_DEF=2;
        Bonus[0][0]=0;Bonus[0][1]=0;Bonus[0][2]=0;
        Bonus[1][0]=0;Bonus[1][1]=0;Bonus[1][2]=0;
        Bonus[2][0]=1;Bonus[2][1]=0;Bonus[2][2]=1;
        Life=Ori_Life=8;
        CurePoint=1;
        ATKRange=Ori_ATKRange=1;
        ActionPoint=Ori_ActionPoint=5;
        ViewRange=Ori_ViewRange=3;
        ATKAble=true;
        IsATKed=false;
        break;
    case 105:
        MaintenanceCost=50;
        Cost=250;
        Name="光速战机";
        Des="这是歼击机";
        ATKType=BOTH;//攻击类型（对空对地）
        UnitType=FLY;//单位类型
        ATKAfterMove=true;//是否可以移动后攻击
        MoveAfterATK=true;//是否可以攻击后移动
        ATK_Grand=Ori_ATK_Grand=7;//基础数值
        ATK_Sky=Ori_ATK_Sky=3;
        ATK_Base=8;
        DEF=Ori_DEF=1;
        Bonus[0][0]=0;Bonus[0][1]=0;Bonus[0][2]=0;
        Bonus[1][0]=0;Bonus[1][1]=0;Bonus[1][2]=-1;
        Bonus[2][0]=0;Bonus[2][1]=1;Bonus[2][2]=1;
        Life=Ori_Life=8;
        CurePoint=1;
        ATKRange=Ori_ATKRange=1;
        ActionPoint=Ori_ActionPoint=6;
        ViewRange=Ori_ViewRange=3;
        ATKAble=true;
        break;
    case 106:
        MaintenanceCost=80;
        Cost=350;
        Name="量子战机";
        Des="这是歼击机";
        ATKType=BOTH;//攻击类型（对空对地）
        UnitType=FLY;//单位类型
        ATKAfterMove=true;//是否可以移动后攻击
        MoveAfterATK=false;//是否可以攻击后移动
        ATK_Grand=Ori_ATK_Grand=6;//基础数值
        ATK_Sky=Ori_ATK_Sky=5;
        ATK_Base=15;
        DEF=Ori_DEF=2;
        Bonus[0][0]=0;Bonus[0][1]=0;Bonus[0][2]=0;
        Bonus[1][0]=0;Bonus[1][1]=0;Bonus[1][2]=0;
        Bonus[2][0]=0;Bonus[2][1]=0;Bonus[2][2]=1;
        Life=Ori_Life=8;
        CurePoint=2;
        ATKRange=Ori_ATKRange=1;
        ActionPoint=Ori_ActionPoint=7;
        ViewRange=Ori_ViewRange=3;
        ATKAble=true;
        break;
    case 107:
        MaintenanceCost=120;
        Cost=600;
        Name="瓦解炮";
        Des="这是歼击机";
        ATKType=GRAND;//攻击类型（对空对地）
        UnitType=NORMAL;//单位类型
        ATKAfterMove=false;//是否可以移动后攻击
        MoveAfterATK=false;//是否可以攻击后移动
        ATK_Grand=Ori_ATK_Grand=12;//基础数值
        ATK_Sky=Ori_ATK_Sky=0;
        ATK_Base=25;
        DEF=Ori_DEF=1;
        Bonus[0][0]=0;Bonus[0][1]=0;Bonus[0][2]=0;
        Bonus[1][0]=0;Bonus[1][1]=0;Bonus[1][2]=0;
        Bonus[2][0]=0;Bonus[2][1]=0;Bonus[2][2]=0;
        Life=Ori_Life=8;
        CurePoint=1;
        ATKRange=Ori_ATKRange=4;
        ActionPoint=Ori_ActionPoint=4;
        ViewRange=Ori_ViewRange=4;
        ATKAble=true;
        break;

    case 201:
        MaintenanceCost=2;
        Cost=15;
        Name="沉沦魔";
        Des="这是一个机枪兵";
        ATKType=GRAND;//攻击类型（对空对地）
        UnitType=NORMAL;//单位类型
        ATKAfterMove=true;//是否可以移动后攻击
        MoveAfterATK=false;//是否可以攻击后移动
        ATK_Grand=Ori_ATK_Grand=5;//基础数值
        ATK_Sky=Ori_ATK_Sky=0;
        ATK_Base=5;
        DEF=Ori_DEF=2;

        Bonus[0][0]=0;Bonus[0][1]=0;Bonus[0][2]=0;
        Bonus[1][0]=0;Bonus[1][1]=0;Bonus[1][2]=1;
        Bonus[2][0]=0;Bonus[2][1]=0;Bonus[2][2]=0;

        Life=Ori_Life=5;
        CurePoint=1;
        ATKRange=Ori_ATKRange=1;
        ActionPoint=Ori_ActionPoint=4;
        ViewRange=Ori_ViewRange=2;
        ATKAble=true;
        break;
    case 202:
        MaintenanceCost=5;
        Cost=40;
        Name="剧毒蜘蛛";
        Des="这是一个防空兵";
        ATKType=GRAND;//攻击类型（对空对地）
        UnitType=NORMAL;//单位类型
        ATKAfterMove=true;//是否可以移动后攻击
        MoveAfterATK=false;//是否可以攻击后移动
        ATK_Grand=Ori_ATK_Grand=6;//基础数值
        ATK_Sky=Ori_ATK_Sky=0;
        ATK_Base=5;
        DEF=Ori_DEF=0;
        Bonus[0][0]=0;Bonus[0][1]=1;Bonus[0][2]=0;
        Bonus[1][0]=0;Bonus[1][1]=0;Bonus[1][2]=0;
        Bonus[2][0]=1;Bonus[2][1]=0;Bonus[2][2]=0;
        Life=Ori_Life=5;
        CurePoint=2;
        ATKRange=Ori_ATKRange=1;
        ActionPoint=Ori_ActionPoint=7;
        ViewRange=Ori_ViewRange=3;
        ATKAble=true;
        break;
    case 203:
        MaintenanceCost=10;
        Cost=80;
        Name="邪恶法师";
        Des="这是坦克";
        ATKType=BOTH;//攻击类型（对空对地）
        UnitType=NORMAL;//单位类型
        ATKAfterMove=true;//是否可以移动后攻击
        MoveAfterATK=false;//是否可以攻击后移动
        ATK_Grand=Ori_ATK_Grand=5;//基础数值
        ATK_Sky=Ori_ATK_Sky=4;
        ATK_Base=5;
        DEF=Ori_DEF=2;
        Bonus[0][0]=0;Bonus[0][1]=0;Bonus[0][2]=0;
        Bonus[1][0]=0;Bonus[1][1]=1;Bonus[1][2]=0;
        Bonus[2][0]=0;Bonus[2][1]=0;Bonus[2][2]=0;
        Life=Ori_Life=8;
        CurePoint=1;
        ATKRange=Ori_ATKRange=1;
        ActionPoint=Ori_ActionPoint=4;
        ViewRange=Ori_ViewRange=2;
        ATKAble=true;
        break;
    case 204:
        MaintenanceCost=20;
        Cost=100;
        Name="邪恶毒蜂";
        Des="这是轰炸机";
        ATKType=GRAND;//攻击类型（对空对地）
        UnitType=FLY;//单位类型
        ATKAfterMove=true;//是否可以移动后攻击
        MoveAfterATK=false;//是否可以攻击后移动
        ATK_Grand=Ori_ATK_Grand=5;//基础数值
        ATK_Sky=Ori_ATK_Sky=0;
        ATK_Base=8;
        DEF=Ori_DEF=2;
        Bonus[0][0]=0;Bonus[0][1]=0;Bonus[0][2]=0;
        Bonus[1][0]=0;Bonus[1][1]=0;Bonus[1][2]=0;
        Bonus[2][0]=1;Bonus[2][1]=0;Bonus[2][2]=1;
        Life=Ori_Life=8;
        CurePoint=2;
        ATKRange=Ori_ATKRange=2;
        ActionPoint=Ori_ActionPoint=5;
        ViewRange=Ori_ViewRange=3;
        ATKAble=true;
        break;
    case 205:
        MaintenanceCost=50;
        Cost=250;
        Name="镰刀魔";
        Des="这是歼击机";
        ATKType=GRAND;//攻击类型（对空对地）
        UnitType=NORMAL;//单位类型
        ATKAfterMove=true;//是否可以移动后攻击
        MoveAfterATK=false;//是否可以攻击后移动
        ATK_Grand=Ori_ATK_Grand=7;//基础数值
        ATK_Sky=Ori_ATK_Sky=0;
        ATK_Base=8;
        DEF=Ori_DEF=3;
        Bonus[0][0]=0;Bonus[0][1]=0;Bonus[0][2]=0;
        Bonus[1][0]=1;Bonus[1][1]=0;Bonus[1][2]=1;
        Bonus[2][0]=0;Bonus[2][1]=0;Bonus[2][2]=0;
        Life=Ori_Life=10;
        CurePoint=2;
        ATKRange=Ori_ATKRange=1;
        ActionPoint=Ori_ActionPoint=5;
        ViewRange=Ori_ViewRange=2;
        ATKAble=true;
        break;
    case 206:
        MaintenanceCost=80;
        Cost=350;
        Name="剧毒蜂王";
        Des="这是歼击机";
        ATKType=BOTH;//攻击类型（对空对地）
        UnitType=FLY;//单位类型
        ATKAfterMove=true;//是否可以移动后攻击
        MoveAfterATK=false;//是否可以攻击后移动
        ATK_Grand=Ori_ATK_Grand=7;//基础数值
        ATK_Sky=Ori_ATK_Sky=4;
        ATK_Base=15;
        DEF=Ori_DEF=1;
        Bonus[0][0]=0;Bonus[0][1]=0;Bonus[0][2]=0;
        Bonus[1][0]=0;Bonus[1][1]=1;Bonus[1][2]=0;
        Bonus[2][0]=1;Bonus[2][1]=0;Bonus[2][2]=1;
        Life=Ori_Life=8;
        CurePoint=2;
        ATKRange=Ori_ATKRange=2;
        ActionPoint=Ori_ActionPoint=5;
        ViewRange=Ori_ViewRange=2;
        ATKAble=true;
        break;
    case 207:
        MaintenanceCost=120;
        Cost=500;
        Name="堕天使";
        Des="这是歼击机";
        ATKType=BOTH;//攻击类型（对空对地）
        UnitType=NORMAL;//单位类型
        ATKAfterMove=true;//是否可以移动后攻击
        MoveAfterATK=false;//是否可以攻击后移动
        ATK_Grand=Ori_ATK_Grand=8;//基础数值
        ATK_Sky=Ori_ATK_Sky=6;
        ATK_Base=20;
        DEF=Ori_DEF=3;
        Bonus[0][0]=0;Bonus[0][1]=0;Bonus[0][2]=0;
        Bonus[1][0]=0;Bonus[1][1]=0;Bonus[1][2]=0;
        Bonus[2][0]=0;Bonus[2][1]=0;Bonus[2][2]=0;
        Life=Ori_Life=10;
        CurePoint=2;
        ATKRange=Ori_ATKRange=2;
        ActionPoint=Ori_ActionPoint=7;
        ViewRange=Ori_ViewRange=3;
        ATKAble=true;
        break;


    case 301:
        MaintenanceCost=2;
        Cost=20;
        Name="天使";
        Des="这是一个机枪兵";
        ATKType=GRAND;//攻击类型（对空对地）
        UnitType=NORMAL;//单位类型
        ATKAfterMove=true;//是否可以移动后攻击
        MoveAfterATK=false;//是否可以攻击后移动
        ATK_Grand=Ori_ATK_Grand=5;//基础数值
        ATK_Sky=Ori_ATK_Sky=0;
        ATK_Base=2;
        DEF=Ori_DEF=2;

        Bonus[0][0]=0;Bonus[0][1]=0;Bonus[0][2]=0;
        Bonus[1][0]=0;Bonus[1][1]=0;Bonus[1][2]=0;
        Bonus[2][0]=0;Bonus[2][1]=0;Bonus[2][2]=0;

        Life=Ori_Life=5;
        CurePoint=1;
        ATKRange=Ori_ATKRange=1;
        ActionPoint=Ori_ActionPoint=4;
        ViewRange=Ori_ViewRange=3;
        ATKAble=true;
        break;
    case 302:
        MaintenanceCost=5;
        Cost=40;
        Name="大天使";
        Des="这是一个防空兵";
        ATKType=GRAND;//攻击类型（对空对地）
        UnitType=NORMAL;//单位类型
        ATKAfterMove=true;//是否可以移动后攻击
        MoveAfterATK=false;//是否可以攻击后移动
        ATK_Grand=Ori_ATK_Grand=6;//基础数值
        ATK_Sky=Ori_ATK_Sky=0;
        ATK_Base=4;
        DEF=Ori_DEF=1;
        Bonus[0][0]=0;Bonus[0][1]=0;Bonus[0][2]=0;
        Bonus[1][0]=0;Bonus[1][1]=0;Bonus[1][2]=0;
        Bonus[2][0]=0;Bonus[2][1]=0;Bonus[2][2]=0;
        Life=Ori_Life=8;
        CurePoint=2;
        ATKRange=Ori_ATKRange=1;
        ActionPoint=Ori_ActionPoint=4;
        ViewRange=Ori_ViewRange=2;
        ATKAble=true;
        break;
    case 303:
        MaintenanceCost=12;
        Cost=80;
        Name="能天使";
        Des="这是坦克";
        ATKType=SKY;//攻击类型（对空对地）
        UnitType=FLY;//单位类型
        ATKAfterMove=true;//是否可以移动后攻击
        MoveAfterATK=false;//是否可以攻击后移动
        ATK_Grand=Ori_ATK_Grand=0;//基础数值
        ATK_Sky=Ori_ATK_Sky=4;
        ATK_Base=5;
        DEF=Ori_DEF=1;
        Bonus[0][0]=0;Bonus[0][1]=0;Bonus[0][2]=0;
        Bonus[1][0]=0;Bonus[1][1]=0;Bonus[1][2]=0;
        Bonus[2][0]=0;Bonus[2][1]=0;Bonus[2][2]=1;
        Life=Ori_Life=8;
        CurePoint=1;
        ATKRange=Ori_ATKRange=1;
        ActionPoint=Ori_ActionPoint=5;
        ViewRange=Ori_ViewRange=2;
        ATKAble=true;
        break;
    case 304:
        MaintenanceCost=30;
        Cost=150;
        Name="力天使";
        Des="这是轰炸机";
        ATKType=GRAND;//攻击类型（对空对地）
        UnitType=NORMAL;//单位类型
        ATKAfterMove=true;//是否可以移动后攻击
        MoveAfterATK=false;//是否可以攻击后移动
        ATK_Grand=Ori_ATK_Grand=7;//基础数值
        ATK_Sky=Ori_ATK_Sky=0;
        ATK_Base=8;
        DEF=Ori_DEF=2;
        Bonus[0][0]=0;Bonus[0][1]=0;Bonus[0][2]=1;
        Bonus[1][0]=0;Bonus[1][1]=0;Bonus[1][2]=0;
        Bonus[2][0]=1;Bonus[2][1]=0;Bonus[2][2]=0;
        Life=Ori_Life=8;
        CurePoint=1;
        ATKRange=Ori_ATKRange=1;
        ActionPoint=Ori_ActionPoint=4;
        ViewRange=Ori_ViewRange=2;
        ATKAble=true;
        IsATKed=false;
        break;
    case 305:
        MaintenanceCost=50;
        Cost=250;
        Name="高阶天使";
        Des="这是歼击机";
        ATKType=SKY;//攻击类型（对空对地）
        UnitType=FLY;//单位类型
        ATKAfterMove=true;//是否可以移动后攻击
        MoveAfterATK=false;//是否可以攻击后移动
        ATK_Grand=Ori_ATK_Grand=0;//基础数值
        ATK_Sky=Ori_ATK_Sky=6;
        ATK_Base=8;
        DEF=Ori_DEF=1;
        Bonus[0][0]=0;Bonus[0][1]=1;Bonus[0][2]=1;
        Bonus[1][0]=0;Bonus[1][1]=0;Bonus[1][2]=-1;
        Bonus[2][0]=0;Bonus[2][1]=0;Bonus[2][2]=0;
        Life=Ori_Life=8;
        CurePoint=1;
        ATKRange=Ori_ATKRange=1;
        ActionPoint=Ori_ActionPoint=5;
        ViewRange=Ori_ViewRange=2;
        ATKAble=true;
        break;
    case 306:
        MaintenanceCost=100;
        Cost=400;
        Name="六翼天使";
        Des="这是歼击机";
        ATKType=BOTH;//攻击类型（对空对地）
        UnitType=NORMAL;//单位类型
        ATKAfterMove=true;//是否可以移动后攻击
        MoveAfterATK=false;//是否可以攻击后移动
        ATK_Grand=Ori_ATK_Grand=8;//基础数值
        ATK_Sky=Ori_ATK_Sky=4;
        ATK_Base=15;
        DEF=Ori_DEF=3;
        Bonus[0][0]=0;Bonus[0][1]=1;Bonus[0][2]=0;
        Bonus[1][0]=0;Bonus[1][1]=0;Bonus[1][2]=0;
        Bonus[2][0]=0;Bonus[2][1]=0;Bonus[2][2]=1;
        Life=Ori_Life=10;
        CurePoint=2;
        ATKRange=Ori_ATKRange=1;
        ActionPoint=Ori_ActionPoint=5;
        ViewRange=Ori_ViewRange=3;
        ATKAble=true;
        break;
    case 307:
        MaintenanceCost=150;
        Cost=600;
        Name="创世神";
        Des="这是歼击机";
        ATKType=BOTH;//攻击类型（对空对地）
        UnitType=NORMAL;//单位类型
        ATKAfterMove=true;//是否可以移动后攻击
        MoveAfterATK=true;//是否可以攻击后移动
        ATK_Grand=Ori_ATK_Grand=7;//基础数值
        ATK_Sky=Ori_ATK_Sky=4;
        ATK_Base=20;
        DEF=Ori_DEF=4;
        Bonus[0][0]=0;Bonus[0][1]=0;Bonus[0][2]=0;
        Bonus[1][0]=0;Bonus[1][1]=0;Bonus[1][2]=0;
        Bonus[2][0]=0;Bonus[2][1]=0;Bonus[2][2]=0;
        Life=Ori_Life=10;
        CurePoint=3;
        ATKRange=Ori_ATKRange=3;
        ActionPoint=Ori_ActionPoint=7;
        ViewRange=Ori_ViewRange=3;
        ATKAble=true;
        break;
    }
}

#endif // UNIT_H

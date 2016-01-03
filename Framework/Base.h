/*基地*/
/*此头文件包含对基地的定义*/

#ifndef BUILDING_H
#define BUILDING_H

class Base{
public:
    int X;//坐标
    int Y;
    bool IsUsed;//是否已经使用（生产单位或者研究科技）
    int Player;//所属玩家

public:
    Base(int x,int y,int player);
};

Base::Base(int x=0, int y=0, int player=0):X(x),Y(y),IsUsed(0),Player(player){}

#endif // BUILDING

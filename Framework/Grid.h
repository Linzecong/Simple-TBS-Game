/*格子*/
/*此头文件包含对游戏中棋盘的格子的定义*/

#ifndef GRID_H
#define GRID_H
#include"Unit.h"
#include"Base.h"
#include<QList>

class Grid{
public:
    QList<Unit* > NormalUnit;//该格子存在的地面单位
    QList<Unit* > FlyUnit;//该格子存在的飞行单位
    Base* Construction;//该格子存在的基地，没有时为NULL
    int Cost;//经过该格子消耗的行动力
    int X;//坐标
    int Y;
    int Data;//寻路用，保存从某格子到此格子所需的行动力
    enum GRIDTYPE{GRASS,SAND,FOREST,HILL}Type;//格子类型

public:
    Grid();
    Grid(GRIDTYPE type);//初始化
    ~Grid();

    void setType(GRIDTYPE type);//设置格子类型
    void addUnit(Unit* temp);//在此格子中添加单位
};

Grid::Grid():Construction(NULL),Cost(1),X(0),Y(0),Data(0),Type(GRASS){}

Grid::Grid(Grid::GRIDTYPE type):Construction(NULL),X(0),Y(0),Data(0){
    setType(type);
}

Grid::~Grid(){}

void Grid::setType(Grid::GRIDTYPE type){
    switch(type){
    case GRASS:
        Cost=1;
        break;
    case SAND:
        Cost=2;
        break;
    case FOREST:
        Cost=3;
        break;
    case HILL:
        Cost=10;
        break;
    }
    Type=type;
}

void Grid::addUnit(Unit *temp){
    switch (temp->UnitType) {
    case Unit::NORMAL:
        NormalUnit.append(temp);
        break;
    case Unit::FLY:
        FlyUnit.append(temp);
        break;
    }
}

#endif // GRID_H

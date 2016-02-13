/*棋盘*/
/*此头文件包含对棋盘和寻路有关的算法定义*/

#ifndef MAP_H
#define MAP_H
#include"Grid.h"
#include<QString>
#include<QList>
#include<QQueue>

class Map{
public:
    QList<QList<Grid> > GameMap;//储存格子
    int ID;//该棋盘ID
    int PlayerCount;//该棋盘允许的玩家数
    int Width;//宽度,从0开始
    int Height;//高度，从0开始

    QString Name;
    QString Des;

public:
    Map(const Map& x);
    Map(int id);//根据ID生成地图
    Map(int x,int y);
    Map(){}
    ~Map(){}
public:
    Map* findWay(int x, int y, int playerid);//寻路
    static Map* findViewOrATKRange(int mapx,int mapy,int x,int y);//视野和攻击距离用

private:
    Grid grid(int x,int y){return GameMap[x][y];}
    Grid gridu(int x,int y);
    Grid gridd(int x,int y);
    Grid gridlu(int x,int y);
    Grid gridru(int x,int y);
    Grid gridld(int x,int y);
    Grid gridrd(int x,int y);

    void marku(int x,int y);
    void markd(int x,int y);
    void marklu(int x,int y);
    void markru(int x,int y);
    void markld(int x,int y);
    void markrd(int x,int y);


};

Map::Map(const Map &x){
    Width=x.Width;
    Height=x.Height;
    GameMap=x.GameMap;
}

Map::Map(int x, int y):Width(x-1),Height(y-1){
    for(int i=0;i<x;i++){
        QList<Grid> abc;
        GameMap.append(abc);
        for(int j=0;j<y;j++){
            Grid temp;
            GameMap[i].append(temp);
            GameMap[i][j].X=i;
            GameMap[i][j].Y=j;
        }
    }
}

Grid Map::gridu(int x, int y){
    Grid temp;
    if(y==0)return temp;
    return GameMap[x][y-1];
}

Grid Map::gridd(int x, int y){
    Grid temp;
    if(y==Height)return temp;
    return GameMap[x][y+1];
}

Grid Map::gridlu(int x, int y){
    Grid temp;
    if(x==0||(y==0&&x%2==0))return temp;

    if(x%2==1)
        return GameMap[x-1][y];
    else
        return GameMap[x-1][y-1];
}

Grid Map::gridru(int x, int y){
    Grid temp;
    if(x==Width||(y==0&&x%2==0))return temp;

    if(x%2==1)
        return GameMap[x+1][y];
    else
        return GameMap[x+1][y-1];
}

Grid Map::gridld(int x, int y){
    Grid temp;
    if(x==0||(y==Height&&x%2==1))return temp;

    if(x%2==1)
        return GameMap[x-1][y+1];
    else
        return GameMap[x-1][y];
}

Grid Map::gridrd(int x, int y){
    Grid temp;
    if(x==Width||(y==Height&&x%2==1))return temp;

    if(x%2==1)
        return GameMap[x+1][y+1];
    else
        return GameMap[x+1][y];
}

void Map::marku(int x, int y){
    if(y==0)return;


    if(GameMap[x][y-1].Data==0)
        GameMap[x][y-1].Data=GameMap[x][y].Data+GameMap[x][y-1].Cost;
    else{
        int temp=GameMap[x][y].Data+GameMap[x][y-1].Cost;
        if(temp<GameMap[x][y-1].Data||GameMap[x][y-1].Data==0)
            GameMap[x][y-1].Data=temp;

    }
}

void Map::markd(int x, int y){
    if(y==Height)return;

    if(GameMap[x][y+1].Data==0)
        GameMap[x][y+1].Data=GameMap[x][y].Data+GameMap[x][y+1].Cost;
    else{
        int temp=GameMap[x][y].Data+GameMap[x][y+1].Cost;
        if(temp<GameMap[x][y+1].Data||GameMap[x][y+1].Data==0)
            GameMap[x][y+1].Data=temp;

    }
}

void Map::marklu(int x, int y){
    if(x==0||(y==0&&x%2==0))return;

    if(x%2==1){
        if(GameMap[x-1][y].Data==0)
            GameMap[x-1][y].Data=GameMap[x][y].Data+GameMap[x-1][y].Cost;
        else{
            int temp=GameMap[x][y].Data+GameMap[x-1][y].Cost;
            if(temp<GameMap[x-1][y].Data||GameMap[x-1][y].Data==0)
                GameMap[x-1][y].Data=temp;
        }
    }
    else{
        if(GameMap[x-1][y-1].Data==0)
            GameMap[x-1][y-1].Data=GameMap[x][y].Data+GameMap[x-1][y-1].Cost;
        else{
            int temp=GameMap[x][y].Data+GameMap[x-1][y-1].Cost;
            if(temp<GameMap[x-1][y-1].Data||GameMap[x-1][y-1].Data==0)
                GameMap[x-1][y-1].Data=temp;
        }
    }
}

void Map::markru(int x, int y){
    if(x==Width||(y==0&&x%2==0))return;

    if(x%2==1){
        if(GameMap[x+1][y].Data==0)
            GameMap[x+1][y].Data=GameMap[x][y].Data+GameMap[x+1][y].Cost;
        else{
            int temp=GameMap[x][y].Data+GameMap[x+1][y].Cost;
            if(temp<GameMap[x+1][y].Data||GameMap[x+1][y].Data==0)
                GameMap[x+1][y].Data=temp;
        }
    }
    else{
        if(GameMap[x+1][y-1].Data==0)
            GameMap[x+1][y-1].Data=GameMap[x][y].Data+GameMap[x+1][y-1].Cost;
        else{
            int temp=GameMap[x][y].Data+GameMap[x+1][y-1].Cost;
            if(temp<GameMap[x+1][y-1].Data||GameMap[x+1][y-1].Data==0)
                GameMap[x+1][y-1].Data=temp;
        }
    }
}

void Map::markld(int x, int y){
    if(x==0||(y==Height&&x%2==1))return;

    if(x%2==1){
        if(GameMap[x-1][y+1].Data==0)
            GameMap[x-1][y+1].Data=GameMap[x][y].Data+GameMap[x-1][y+1].Cost;
        else{
            int temp=GameMap[x][y].Data+GameMap[x-1][y+1].Cost;
            if(temp<GameMap[x-1][y+1].Data||GameMap[x-1][y+1].Data==0)
                GameMap[x-1][y+1].Data=temp;
        }
    }
    else{
        if(GameMap[x-1][y].Data==0)
            GameMap[x-1][y].Data=GameMap[x][y].Data+GameMap[x-1][y].Cost;
        else{
            int temp=GameMap[x][y].Data+GameMap[x-1][y].Cost;
            if(temp<GameMap[x-1][y].Data||GameMap[x-1][y].Data==0)
                GameMap[x-1][y].Data=temp;
        }
    }
}

void Map::markrd(int x, int y){
    if(x==Width||(y==Height&&x%2==1))return;

    if(x%2==1){
        if(GameMap[x+1][y+1].Data==0)
            GameMap[x+1][y+1].Data=GameMap[x][y].Data+GameMap[x+1][y+1].Cost;
        else{
            int temp=GameMap[x][y].Data+GameMap[x+1][y+1].Cost;
            if(temp<GameMap[x+1][y+1].Data||GameMap[x+1][y+1].Data==0)
                GameMap[x+1][y+1].Data=temp;
        }
    }
    else{
        if(GameMap[x+1][y].Data==0)
            GameMap[x+1][y].Data=GameMap[x][y].Data+GameMap[x+1][y].Cost;
        else{
            int temp=GameMap[x][y].Data+GameMap[x+1][y].Cost;
            if(temp<GameMap[x+1][y].Data||GameMap[x+1][y].Data==0)
                GameMap[x+1][y].Data=temp;
        }
    }
}

Map *Map::findWay(int x, int y,int playerid){
    Map* map=new Map(*this);

    for(int i=0;i<=map->Width;i++)
        for(int j=0;j<=map->Height;j++)
            if(!map->GameMap[i][j].NormalUnit.isEmpty()){
                if(map->GameMap[i][j].NormalUnit[0]->Player!=playerid)
                   map->GameMap[i][j].Cost+=(map->GameMap[i][j].NormalUnit.length())*2;
            }
            else
                if(!map->GameMap[i][j].FlyUnit.isEmpty())
                    if(map->GameMap[i][j].FlyUnit[0]->Player!=playerid)
                   map->GameMap[i][j].Cost+=(map->GameMap[i][j].FlyUnit.length())*2;


    Map* mapmark=new Map(*this);
    QQueue<Grid> a;
    Grid abc=map->grid(x,y);
    a.enqueue(abc);
    while(a.isEmpty()!=true){
        Grid temp=a.dequeue();
        mapmark->GameMap[temp.X][temp.Y].Data=-1;
        map->marku(temp.X,temp.Y);
        map->markru(temp.X,temp.Y);
        map->markrd(temp.X,temp.Y);
        map->markd(temp.X,temp.Y);
        map->markld(temp.X,temp.Y);
        map->marklu(temp.X,temp.Y);
        a.enqueue(map->gridu(temp.X,temp.Y));
        a.enqueue(map->gridru(temp.X,temp.Y));
        a.enqueue(map->gridrd(temp.X,temp.Y));
        a.enqueue(map->gridd(temp.X,temp.Y));
        a.enqueue(map->gridld(temp.X,temp.Y));
        a.enqueue(map->gridlu(temp.X,temp.Y));
        int size=a.size();
        QQueue<Grid> b;
        for(int i=0;i<size;i++){
            Grid temp1=a.dequeue();
            if((temp1.X!=0||temp1.Y!=0)&&mapmark->GameMap[temp1.X][temp1.Y].Data==0)
                b.enqueue(temp1);
        }
        a=b;

    }

    mapmark=new Map(*this);
    QQueue<Grid> a1;
    Grid abc1=map->grid(x,y);
    a1.enqueue(abc1);
    while(a1.isEmpty()!=true){
        Grid temp=a1.dequeue();
        mapmark->GameMap[temp.X][temp.Y].Data=-1;
        map->marklu(temp.X,temp.Y);
        map->markld(temp.X,temp.Y);
        map->markd(temp.X,temp.Y);
        map->markrd(temp.X,temp.Y);
        map->markru(temp.X,temp.Y);
        map->marku(temp.X,temp.Y);
        a1.enqueue(map->gridlu(temp.X,temp.Y));
        a1.enqueue(map->gridld(temp.X,temp.Y));
        a1.enqueue(map->gridd(temp.X,temp.Y));
        a1.enqueue(map->gridrd(temp.X,temp.Y));
        a1.enqueue(map->gridru(temp.X,temp.Y));
        a1.enqueue(map->gridu(temp.X,temp.Y));
        int size=a1.size();
        QQueue<Grid> b1;
        for(int i=0;i<size;i++){
            Grid temp1=a1.dequeue();
            if((temp1.X!=0||temp1.Y!=0)&&mapmark->GameMap[temp1.X][temp1.Y].Data==0)
                b1.enqueue(temp1);
        }
        a1=b1;
    }
    return map;
}

Map *Map::findViewOrATKRange(int mapx, int mapy, int x, int y){
    Map* map=new Map(mapx,mapy);

    Map* mapmark=new Map(mapx,mapy);

    QQueue<Grid> a;
    Grid abc=map->grid(x,y);
    a.enqueue(abc);
    while(a.isEmpty()!=true){
        Grid temp=a.dequeue();
        mapmark->GameMap[temp.X][temp.Y].Data=-1;
        map->marku(temp.X,temp.Y);
        map->markru(temp.X,temp.Y);
        map->markrd(temp.X,temp.Y);
        map->markd(temp.X,temp.Y);
        map->markld(temp.X,temp.Y);
        map->marklu(temp.X,temp.Y);

        a.enqueue(map->gridu(temp.X,temp.Y));
        a.enqueue(map->gridru(temp.X,temp.Y));
        a.enqueue(map->gridrd(temp.X,temp.Y));
        a.enqueue(map->gridd(temp.X,temp.Y));
        a.enqueue(map->gridld(temp.X,temp.Y));
        a.enqueue(map->gridlu(temp.X,temp.Y));

        int size=a.size();
        QQueue<Grid> b;
        for(int i=0;i<size;i++){
            Grid temp1=a.dequeue();
            if((temp1.X!=0||temp1.Y!=0)&&mapmark->GameMap[temp1.X][temp1.Y].Data==0)
                b.enqueue(temp1);
        }
        a=b;

    }
    return map;
}

/********************************************************************************/
/*******************************此处为各种棋盘详细定义*******************************/
/********************************************************************************/

Map::Map(int id){
    ID=id;
    if(id==1){
        PlayerCount=2;

        /*此处定义大小*/
        Width=8;
        Height=4;
        Name="庇护所";
        Des="双人对战地图！！";
        for(int i=0;i<=Width;i++){
            QList<Grid> abc;
            GameMap.append(abc);
            for(int j=0;j<=Height;j++){
                Grid temp(Grid::GRASS);
                GameMap[i].append(temp);
                GameMap[i][j].X=i;
                GameMap[i][j].Y=j;
            }
        }

        /*此处定义基地位置*/

        GameMap[0][2]=Grid(Grid::GRASS,new Base(0,2,1));
        GameMap[1][0]=Grid(Grid::GRASS,new Base(1,0,1));
        GameMap[1][3]=Grid(Grid::GRASS,new Base(1,3,1));


        GameMap[8][2]=Grid(Grid::GRASS,new Base(8,2,2));
        GameMap[7][0]=Grid(Grid::GRASS,new Base(7,0,2));
        GameMap[7][3]=Grid(Grid::GRASS,new Base(7,3,2));
        /*此处定义格子类型*/
        GameMap[0][0].setType(Grid::SAND);
        GameMap[0][1].setType(Grid::SAND);
        GameMap[0][3].setType(Grid::HILL);
        GameMap[0][4].setType(Grid::HILL);

        GameMap[8][0].setType(Grid::SAND);
        GameMap[8][1].setType(Grid::SAND);
        GameMap[8][3].setType(Grid::HILL);
        GameMap[8][4].setType(Grid::HILL);

        GameMap[6][1].setType(Grid::SAND);
        GameMap[7][1].setType(Grid::SAND);
        GameMap[2][1].setType(Grid::SAND);
        GameMap[1][1].setType(Grid::SAND);

        GameMap[6][3].setType(Grid::FOREST);
        GameMap[6][4].setType(Grid::GRASS);
        GameMap[2][3].setType(Grid::FOREST);
        GameMap[2][4].setType(Grid::GRASS);

        GameMap[4][0].setType(Grid::FOREST);
        GameMap[4][1].setType(Grid::FOREST);
        GameMap[4][2].setType(Grid::SAND);
        GameMap[4][3].setType(Grid::FOREST);

        GameMap[3][4].setType(Grid::SAND);
        GameMap[4][4].setType(Grid::FOREST);
        GameMap[5][4].setType(Grid::SAND);
    }

    if(id==2){
        PlayerCount=4;
        Width=6;
        Height=6;
        Name="战地";
        Des="四人对战地图！！";

        for(int i=0;i<7;i++){
            QList<Grid> abc;
            GameMap.append(abc);
            for(int j=0;j<7;j++){
                Grid temp(Grid::GRASS);
                GameMap[i].append(temp);
                GameMap[i][j].X=i;
                GameMap[i][j].Y=j;
            }
        }



        GameMap[1][1]=Grid(Grid::SAND,new Base(1,1,1));
        GameMap[5][1]=Grid(Grid::SAND,new Base(5,1,2));
        GameMap[1][5]=Grid(Grid::SAND,new Base(1,5,3));
        GameMap[5][5]=Grid(Grid::SAND,new Base(5,5,4));

        GameMap[0][0].setType(Grid::SAND);
        GameMap[0][1].setType(Grid::SAND);
        GameMap[6][0].setType(Grid::HILL);
        GameMap[6][1].setType(Grid::HILL);

        GameMap[0][5].setType(Grid::FOREST);
        GameMap[6][5].setType(Grid::FOREST);
        GameMap[3][3].setType(Grid::FOREST);

        GameMap[0][6].setType(Grid::HILL);
        GameMap[6][6].setType(Grid::HILL);
        GameMap[0][4].setType(Grid::HILL);
        GameMap[6][4].setType(Grid::HILL);

        GameMap[2][4].setType(Grid::SAND);
        GameMap[4][4].setType(Grid::SAND);

    }
}

#endif // GameMap_H

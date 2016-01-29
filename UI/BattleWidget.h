/*战斗窗口*/

#ifndef WIDGET_H
#define WIDGET_H
#include<QDebug>
#include<QMessageBox>
#include<QDialog>
#include<QListWidget>
#include<QListWidgetItem>
#include<QLabel>
#include<QScrollBar>
#include<QGraphicsView>
#include<QGraphicsItem>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QPolygonF>
#include<QTimer>
#include<QPropertyAnimation>
#include<QtOpenGL/QGLWidget>
#include<QGraphicsProxyWidget>
#include"../Framework/Map.h"
#include"../Framework/System.h"
#include"../Framework/Unit.h"
#include"MyItem.h"
#include"BaseWidget.h"
#include"DataWidget.h"
#include"ActionWidget.h"
#include"MyListItem.h"


class BattleWidget : public QWidget{
private:
    enum STATE{CHOOSEGRID,MOVE,ATTACK}State;//当前状态

    QGraphicsScene Scene;//场景
    QGraphicsView View;//屏幕
    QList<QList<MyItem*> > Item;//格子
    MyItem* CurrentItem;//目前处于操作状态的格子
    Unit* CurrentUnit;//目前处于操作状态的单位
    Map* DataMap;

    GameSystem System;//游戏系统
    Map* MyMap;//地图指针，简化书写


    double Size;//格子大小，全局大小比例
    void paintMap();//绘制地图
    void resetState();//重置状态
    void resetList(QPointF pos);//点击屏幕时，设置单位框框

    void click();//当场景被点击时，通过判断状态，实现不同效果

    void showBase_Click();
    void myUnitList_Click();
    void enemyUnitList_Click();
    void move_Click();
    void attack_Click();
    void cure_Click();

    void longPressed();//长按后出发的效果
    int time;//保存按住的时间
    void longPress(){
        time++;
        if(time==8){
            longPressed();
            time=0;
        }
    }
    void zero(){time=0;}//没有长按的话，将按住时间置零

    void setView();//设置视野


private:
    DataWidget* Data_Widget;//数据框
    ActionWidget* Action_Widget;//行动框
    QListWidget* MyUnitList;//我方单位框，以后可能要重写，使用原生的太丑
    QListWidget* EnemyUnitList;//敌方单位框

    QList<Unit*> MyUnitList_P;//保存某个格子中，我方单位的指针
    QList<Unit*> EnemyUnitList_P;

    BaseWidget* Base_Widget;//基地框，显示回合各种操作

private:
    /*各种动画*/
    QPropertyAnimation* ActionWShow;
    QPropertyAnimation* DataWShow;
    QPropertyAnimation* MyListShow;
    QPropertyAnimation* EnemyListShow;
    QPropertyAnimation* ActionWHide;
    QPropertyAnimation* DataWHide;
    QPropertyAnimation* MyListHide;
    QPropertyAnimation* EnemyListHide;
    void setUpAnimation(QPointF temp);

public:
    BattleWidget(GameSystem a);
    ~BattleWidget(){}
    void resizeEvent(QResizeEvent * e){
        View.setGeometry(this->geometry());
    }
    QTimer UpdateTimer;
    void updatescene(){
        for(int i=0;i<=MyMap->Width;i++)
            for(int j=0;j<=MyMap->Height;j++)
                Item[i][j]->changePixmapState();
        Scene.update();
    }
};

void BattleWidget::setUpAnimation(QPointF temp){
    ActionWShow = new QPropertyAnimation(Action_Widget, "geometry");
    ActionWShow->setDuration(200);
    ActionWShow->setStartValue(QRect(temp.x()-65*Size-40*Size,temp.y()-90*Size,0,0));
    ActionWShow->setEndValue(QRect(temp.x()-65*Size-40*Size,temp.y()-90*Size,65*Size,90*Size));

    DataWShow = new QPropertyAnimation(Data_Widget, "geometry");
    DataWShow->setDuration(200);
    DataWShow->setStartValue(QRect(temp.x()+65*Size+40*Size,temp.y()-90*Size,0,0));
    DataWShow->setEndValue(QRect(temp.x()+40*Size,temp.y()-90*Size,65*Size,90*Size));

    MyListShow = new QPropertyAnimation(MyUnitList, "geometry");
    MyListShow->setDuration(200);
    MyListShow->setStartValue(QRect(temp.x()-70*Size-20*Size,temp.y()+35*Size,0,0));
    MyListShow->setEndValue(QRect(temp.x()-70*Size-20*Size,temp.y()+35*Size,70*Size,MyUnitList_P.length()*100));

    EnemyListShow = new QPropertyAnimation(EnemyUnitList, "geometry");
    EnemyListShow->setDuration(200);
    EnemyListShow->setStartValue(QRect(temp.x()+70*Size+20*Size,temp.y()+35*Size,0,0));
    EnemyListShow->setEndValue(QRect(temp.x()+20*Size,temp.y()+35*Size,70*Size,EnemyUnitList_P.length()*100));

}

void BattleWidget::longPressed(){
    if(State==ATTACK||State==MOVE)
        resetState();
    else{
        for(int i=0;i<=MyMap->Width;i++)
            for(int j=0;j<=MyMap->Height;j++)
                if(Item[i][j]->IsHover==true)
                    if(!Item[i][j]->MyGrid->Construction==NULL)
                        showBase_Click();
    }
}

BattleWidget::BattleWidget(GameSystem a){
    time=0;
    Size=4;//以后要通过屏幕太小更改
    State=CHOOSEGRID;
    UpdateTimer.start(500);
    System=a;
    System.Player_Turn=&System.PlayerList[0];
    MyMap=&System.GameMap;

    /*在每个基地上方生成3个默认单位*/
    for(int i=1;i<=System.PlayerList.length();i++){
        for(int j=0;j<System.PlayerList[i-1].BaseList.length();j++){
            Unit abc(1,i,System.PlayerList[i-1].BaseList[j].X,System.PlayerList[i-1].BaseList[j].Y);
            System.PlayerList[i-1].UnitList.append(abc);
            System.PlayerList[i-1].UnitList.append(abc);
            System.PlayerList[i-1].UnitList.append(abc);
            System.GameMap.GameMap[System.PlayerList[i-1].BaseList[j].X][System.PlayerList[i-1].BaseList[j].Y].NormalUnit.append(&System.PlayerList[i-1].UnitList[0]);
            System.GameMap.GameMap[System.PlayerList[i-1].BaseList[j].X][System.PlayerList[i-1].BaseList[j].Y].NormalUnit.append(&System.PlayerList[i-1].UnitList[1]);
            System.GameMap.GameMap[System.PlayerList[i-1].BaseList[j].X][System.PlayerList[i-1].BaseList[j].Y].NormalUnit.append(&System.PlayerList[i-1].UnitList[2]);
        }
    }

    /*设置屏幕参数*/
    View.setParent(this);
    View.setScene(&Scene);
    View.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    View.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    View.setViewport(new QGLWidget);//用OpenGL渲染

    /*设置框框参数*/
    Data_Widget=new DataWidget(Size);
    Action_Widget=new ActionWidget(Size);
    MyUnitList=new QListWidget;
    EnemyUnitList=new QListWidget;
    Scene.addWidget(Action_Widget)->setZValue(2);//将框框置前
    Scene.addWidget(Data_Widget)->setZValue(2);
    Scene.addWidget(MyUnitList)->setZValue(2);
    Scene.addWidget(EnemyUnitList)->setZValue(2);
    Action_Widget->setVisible(false);
    Data_Widget->setVisible(false);
    MyUnitList->setVisible(false);
    EnemyUnitList->setVisible(false);
    MyUnitList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    MyUnitList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    EnemyUnitList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    EnemyUnitList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    connect(MyUnitList,&QListWidget::clicked,this,&BattleWidget::myUnitList_Click);
    connect(EnemyUnitList,&QListWidget::clicked,this,&BattleWidget::enemyUnitList_Click);
    connect(Action_Widget->Move,&QPushButton::clicked,this,&BattleWidget::move_Click);
    connect(Action_Widget->Attack,&QPushButton::clicked,this,&BattleWidget::attack_Click);
    connect(Action_Widget->Cure,&QPushButton::clicked,this,&BattleWidget::cure_Click);
    connect(&UpdateTimer,&QTimer::timeout,this,&BattleWidget::updatescene);

    paintMap();
}


void BattleWidget::paintMap(){
    MyItem* temp;
    for(int i=0;i<=MyMap->Width;i++){
        QList<MyItem*> templist;
        for(int j=0;j<=MyMap->Height;j++){
            templist.append(temp);
        }
        Item.append(templist);
    }

    for(int i=0;i<=MyMap->Width;i++)
        for(int j=0;j<=MyMap->Height;j++){
            Item[i][j]=new MyItem(&MyMap->GameMap[i][j],Size);
            connect(&Item[i][j]->Press,&QPushButton::clicked,this,&BattleWidget::click);
            connect(&Item[i][j]->Timer,&QTimer::timeout,this,&BattleWidget::longPress);
            connect(&Item[i][j]->Timer,&QTimer::objectNameChanged,this,&BattleWidget::zero);

            Item[i][j]->PixmapState=QString::number(i%4+1);
            if(i%2==0)
                Item[i][j]->setPos(i*60*Size,j*70*Size);
            else
                Item[i][j]->setPos(i*60*Size,j*70*Size+35*Size);
            Scene.addItem(Item[i][j]);
        }

    Scene.setSceneRect(Scene.sceneRect()+QMargins(150*Size,150*Size,150*Size,150*Size));
    setView();
}

void BattleWidget::resetList(QPointF pos){
    MyUnitList->clear();
    EnemyUnitList->clear();
    MyUnitList_P.clear();
    EnemyUnitList_P.clear();

    for(int i=0;i<CurrentItem->MyGrid->NormalUnit.length();i++){
        if(CurrentItem->MyGrid->NormalUnit[i]->Player==System.Player_Turn->ID){

            MyListItem* temp=new MyListItem((CurrentItem->MyGrid->NormalUnit[i]->Name)+":"+QString::number(CurrentItem->MyGrid->NormalUnit[i]->Player));
            temp->setFixedSize(280,100);
            QListWidgetItem* item=new QListWidgetItem;
            item->setSizeHint(temp->size());
            MyUnitList->addItem(item);
            MyUnitList->setItemWidget(item,temp);

            MyUnitList_P.append(CurrentItem->MyGrid->NormalUnit[i]);
        }
        else{
            MyListItem* temp=new MyListItem((CurrentItem->MyGrid->NormalUnit[i]->Name)+":"+QString::number(CurrentItem->MyGrid->NormalUnit[i]->Player));
            temp->setFixedSize(280,100);
            QListWidgetItem* item=new QListWidgetItem;
            item->setSizeHint(temp->size());
            EnemyUnitList->addItem(item);
            EnemyUnitList->setItemWidget(item,temp);

            EnemyUnitList_P.append(CurrentItem->MyGrid->NormalUnit[i]);
        }
    }

    for(int i=0;i<CurrentItem->MyGrid->FlyUnit.length();i++){
        if(CurrentItem->MyGrid->FlyUnit[i]->Player==System.Player_Turn->ID){
            MyListItem* temp=new MyListItem((CurrentItem->MyGrid->FlyUnit[i]->Name)+":"+QString::number(CurrentItem->MyGrid->FlyUnit[i]->Player));
            temp->setFixedSize(280,100);
            QListWidgetItem* item=new QListWidgetItem;
            item->setSizeHint(temp->size());
            MyUnitList->addItem(item);
            MyUnitList->setItemWidget(item,temp);


            MyUnitList_P.append(CurrentItem->MyGrid->FlyUnit[i]);
        }
        else{
            MyListItem* temp=new MyListItem((CurrentItem->MyGrid->FlyUnit[i]->Name)+":"+QString::number(CurrentItem->MyGrid->FlyUnit[i]->Player));
            temp->setFixedSize(280,100);
            QListWidgetItem* item=new QListWidgetItem;
            item->setSizeHint(temp->size());
            EnemyUnitList->addItem(item);
            EnemyUnitList->setItemWidget(item,temp);

            EnemyUnitList_P.append(CurrentItem->MyGrid->FlyUnit[i]);
        }
    }

    setUpAnimation(pos);

    if(State!=ATTACK)
        if(MyUnitList_P.isEmpty()){
            Action_Widget->setVisible(false);
            MyUnitList->setVisible(false);
            Data_Widget->setVisible(false);

        }
        else{
            CurrentUnit=MyUnitList_P[0];
            Data_Widget->setData(CurrentUnit);
            Action_Widget->setData(CurrentUnit,System.Player_Turn->ID);
            Action_Widget->setVisible(true);
            Data_Widget->setVisible(true);
            MyUnitList->setVisible(true);
            ActionWShow->start();
            DataWShow->start();
            MyListShow->start();
        }

    if(EnemyUnitList_P.isEmpty()){
        EnemyUnitList->setVisible(false);
    }
    else{
        EnemyUnitList->setVisible(true);
        EnemyListShow->start();
        if(!Data_Widget->isVisible()){
            if(State!=ATTACK)
                CurrentUnit=EnemyUnitList_P[0];
            Data_Widget->setData(EnemyUnitList_P[0]);
            Data_Widget->setVisible(true);
            DataWShow->start();
        }
    }
}

void BattleWidget::click(){
    if(State==CHOOSEGRID){
        for(int i=0;i<=MyMap->Width;i++)
            for(int j=0;j<=MyMap->Height;j++)
                if(Item[i][j]->IsHover==true){
                    CurrentItem=Item[i][j];

                    if(Item[i][j]->IsSeen==0){
                        MyUnitList->setVisible(false);
                        EnemyUnitList->setVisible(false);
                        Data_Widget->setVisible(false);
                        Action_Widget->setVisible(false);
                        return;
                    }
                    resetList(CurrentItem->scenePos());

                }
    }

    if(State==MOVE){
        for(int i=0;i<=MyMap->Width;i++)
            for(int j=0;j<=MyMap->Height;j++)
                if(Item[i][j]->IsHover==true){
                    if(Item[i][j]->RangeMode==0)
                        return;
                    System.moveTo(i,j,CurrentUnit);
                    CurrentUnit->ActionPoint-=DataMap->GameMap[i][j].Data;
                    CurrentItem=Item[i][j];
                    resetList(CurrentItem->scenePos());

                    State=CHOOSEGRID;
                    for(int i=0;i<=MyMap->Width;i++)
                        for(int j=0;j<=MyMap->Height;j++){
                            Item[i][j]->RangeMode=0;
                            Item[i][j]->update();
                        }
                    setView();
                }
    }

    if(State==ATTACK){
        for(int i=0;i<=MyMap->Width;i++)
            for(int j=0;j<=MyMap->Height;j++)
                if(Item[i][j]->IsHover==true){
                    if(Item[i][j]->ATKMode==0)
                        return;
                    CurrentItem=Item[i][j];
                    resetList(CurrentItem->scenePos());
                }
    }
}

void BattleWidget::showBase_Click(){
    Base_Widget=new BaseWidget(System.Player_Turn);
    Scene.addWidget(Base_Widget)->setZValue(2);

    /*设置显示动画*/
    QPropertyAnimation* ActionWShow1 = new QPropertyAnimation(Base_Widget, "geometry");
    ActionWShow1->setDuration(500);
    ActionWShow1->setStartValue(QRect(this->width()/2,this->height(),0,0));
    ActionWShow1->setEndValue(QRect(View.mapToScene(0,0).x(),View.mapToScene(0,0).y(),this->width(),this->height()));
    ActionWShow1->start(QAbstractAnimation::DeleteWhenStopped);
    Base_Widget->exec();

    if(Base_Widget->HasNewUnit>=0){
        if(Base_Widget->HasNewUnit==0)
            System.GameMap.GameMap[Base_Widget->NewUnit.X][Base_Widget->NewUnit.Y].NormalUnit.append(&System.Player_Turn->UnitList[System.Player_Turn->UnitList.length()-1]);
        else{
            System.GameMap.GameMap[Base_Widget->NewUnit.X][Base_Widget->NewUnit.Y].FlyUnit.append(&System.Player_Turn->UnitList[System.Player_Turn->UnitList.length()-1]);
        }
    }

    if(Base_Widget->IsEnd){
        bool temp=0;
        int tempPlayer=System.Player_Turn->ID;

        //判断是否还有单位可以操作
        for(int i=0;i<System.Player_Turn->UnitList.length();i++)
            if(System.Player_Turn->UnitList[i].ActionPoint>0||System.Player_Turn->UnitList[i].canAttack()==1)
                temp=1;
        if(temp){
            if(QMessageBox::question(this,"你还有单位可以操作！","确定要结束回合吗？")==QMessageBox::Yes){
                System.turnout();
                Action_Widget->setData(NULL,System.Player_Turn->ID);
            }
        }
        else{
            System.turnout();
            Action_Widget->setData(NULL,System.Player_Turn->ID);
        }

        /*如果单位列表为空，则玩家死亡*/
        while(System.Player_Turn->UnitList.isEmpty()){
            QMessageBox::information(this,"提示","玩家"+QString::number(System.Player_Turn->ID)+"已被击败");
            System.Player_Turn->IsDead=true;

            for(int i=0;i<System.Player_Turn->BaseList.length();i++)//清除基地
                MyMap->GameMap[System.Player_Turn->BaseList[i].X][System.Player_Turn->BaseList[i].Y].Construction=NULL;

            System.turnout();
            if(tempPlayer==System.Player_Turn->ID){//如果下一个玩家还是自己，则玩家获得胜利
                QMessageBox::information(this,"提示","玩家"+QString::number(System.PlayerList[0].ID)+"获得胜利！！");
                this->close();
            }
        }
        setView();
    }
    Scene.update();
    resetState();
}

void BattleWidget::resetState(){
    State=CHOOSEGRID;
    Action_Widget->setVisible(false);
    MyUnitList->setVisible(false);
    Data_Widget->setVisible(false);
    EnemyUnitList->setVisible(false);
    for(int i=0;i<=MyMap->Width;i++)
        for(int j=0;j<=MyMap->Height;j++){
            Item[i][j]->ATKMode=0;
            Item[i][j]->RangeMode=0;
            Item[i][j]->update();
        }
}

void BattleWidget::myUnitList_Click(){
    CurrentUnit=MyUnitList_P[MyUnitList->currentRow()];
    Action_Widget->setData(CurrentUnit,System.Player_Turn->ID);
    Data_Widget->setData(CurrentUnit);
    Scene.update();
}

void BattleWidget::enemyUnitList_Click(){
    Action_Widget->setVisible(false);
    Data_Widget->setData(EnemyUnitList_P[EnemyUnitList->currentRow()]);

    if(State==ATTACK){
        if(QMessageBox::question(this,"提示","确定要攻击此目标吗？")==QMessageBox::Yes){
            System.attack(CurrentUnit,EnemyUnitList_P[EnemyUnitList->currentRow()],&System.PlayerList[CurrentUnit->Player-1],&System.PlayerList[EnemyUnitList_P[EnemyUnitList->currentRow()]->Player-1],DataMap->GameMap[EnemyUnitList_P[EnemyUnitList->currentRow()]->X][EnemyUnitList_P[EnemyUnitList->currentRow()]->Y].Data);
            resetState();
            setView();
            CurrentItem=NULL;
        }
    }
    Scene.update();
}

void BattleWidget::move_Click(){
    State=MOVE;
    DataMap=System.GameMap.findWay(CurrentUnit->X,CurrentUnit->Y);
    DataMap->GameMap[CurrentUnit->X][CurrentUnit->Y].Data=0;
    for(int i=0;i<=MyMap->Width;i++)
        for(int j=0;j<=MyMap->Height;j++){
            if(DataMap->GameMap[i][j].Data<=CurrentUnit->ActionPoint)
                Item[i][j]->RangeMode=1;
            Item[i][j]->update();
        }
    Action_Widget->setVisible(false);
    MyUnitList->setVisible(false);
    Data_Widget->setVisible(false);
    EnemyUnitList->setVisible(false);
    Scene.update();
}

void BattleWidget::attack_Click(){
    State=ATTACK;
    DataMap=System.GameMap.findViewOrATKRange(MyMap->Width+1,MyMap->Height+1,CurrentUnit->X,CurrentUnit->Y);
    DataMap->GameMap[CurrentUnit->X][CurrentUnit->Y].Data=0;

    for(int i=0;i<=MyMap->Width;i++)
        for(int j=0;j<=MyMap->Height;j++){
            if(DataMap->GameMap[i][j].Data<=CurrentUnit->ATKRange)
                Item[i][j]->ATKMode=1;
            Item[i][j]->update();
        }
    Action_Widget->setVisible(false);
    MyUnitList->setVisible(false);
    Data_Widget->setVisible(false);
    EnemyUnitList->setVisible(false);
    Scene.update();
}

void BattleWidget::cure_Click(){
    CurrentUnit->ActionPoint=0;
    CurrentUnit->IsATKed=1;
    CurrentUnit->IsCure=1;
    Action_Widget->setData(CurrentUnit,System.Player_Turn->ID);
    Scene.update();

}

void BattleWidget::setView(){
    for(int i=0;i<=MyMap->Width;i++)
        for(int j=0;j<=MyMap->Height;j++)
            Item[i][j]->IsSeen=0;

    for(int k=0;k<System.Player_Turn->UnitList.length();k++){
        Map* tempMap=Map::findViewOrATKRange(MyMap->Width+1,MyMap->Height+1,System.Player_Turn->UnitList[k].X,System.Player_Turn->UnitList[k].Y);
        for(int i=0;i<=MyMap->Width;i++)
            for(int j=0;j<=MyMap->Height;j++)
                if(tempMap->GameMap[i][j].Data<=System.Player_Turn->UnitList[k].ViewRange)
                    Item[i][j]->IsSeen=1;
        delete tempMap;
    }

    for(int k=0;k<System.Player_Turn->BaseList.length();k++){
        Map* tempMap=Map::findViewOrATKRange(MyMap->Width+1,MyMap->Height+1,System.Player_Turn->BaseList[k].X,System.Player_Turn->BaseList[k].Y);
        for(int i=0;i<=MyMap->Width;i++)
            for(int j=0;j<=MyMap->Height;j++)
                if(tempMap->GameMap[i][j].Data<=2)
                    Item[i][j]->IsSeen=1;
        delete tempMap;
    }

    for(int i=0;i<=MyMap->Width;i++)
        for(int j=0;j<=MyMap->Height;j++)
            Item[i][j]->update();
    Scene.update();
}

#endif // WIDGET_H

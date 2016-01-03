/*屏幕格子*/

#ifndef MYITEM_H
#define MYITEM_H
#include<QGraphicsItem>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QScrollBar>
#include<QPainter>
#include "../Framework/Grid.h"
#include <QMessageBox>
#include<QGraphicsSceneMouseEvent>
#include<QPushButton>
#include <QtOpenGL/QGLWidget>
#include <QTimer>

class MyItem:public QGraphicsItem{
public:
    MyItem(double a);
    MyItem(Grid* a, double b);

    Grid* MyGrid;//该格子所代表的棋格

    bool IsHover;//是否获得焦点
    bool RangeMode;//是在移动距离之内
    bool ATKMode;//是否在攻击距离之内
    bool IsSeen;//是否被看见

    double Size;

    //给屏幕传递信息用
    QPushButton Press;
    QTimer Timer;
    QPushButton DoublePress;
    bool IsMove;//判断是否移动了

    //拖动用
    bool IsPressed;
    int LY;
    int LX;

public:
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);

    void mousePressEvent(QGraphicsSceneMouseEvent *event){
        LY=event->scenePos().y();
        LX=event->scenePos().x();
        IsMove=0;
        IsPressed=true;
        Timer.start(100);
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
        LY=event->scenePos().y();
        LX=event->scenePos().x();
        IsPressed=false;
        if(!IsMove)
            Press.click();

        Timer.stop();//向上级传递信息用
        if(Timer.objectName()=="baba")
            Timer.setObjectName("baba1");
        else
            Timer.setObjectName("baba");

    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event){
        if(IsPressed){
            IsMove=1;
            QPoint a=event->scenePos().toPoint();
            int y=a.y()-LY;
            int x=a.x()-LX;
            this->scene()->views().first()->verticalScrollBar()->setValue(this->scene()->views().first()->verticalScrollBar()->value()-y);
            this->scene()->views().first()->horizontalScrollBar()->setValue(this->scene()->views().first()->horizontalScrollBar()->value()-x);
        }
    }

public:
    Qt::GlobalColor getPenColor(int id){
        switch (id) {
        case 1:
            return Qt::blue;
        case 2:
            return Qt::red;
        case 3:
            return Qt::yellow;
        case 4:
            return Qt::white;
        }
    }
};

MyItem::MyItem(double a=1):IsHover(0),RangeMode(0),ATKMode(0),IsSeen(0),Size(a){
    this->setAcceptHoverEvents(true);
}

MyItem::MyItem(Grid* a,double b=1):IsHover(0),RangeMode(0),ATKMode(0),IsSeen(0),Size(b),MyGrid(a){
    this->setAcceptHoverEvents(true);
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    /*绘制格子*/
    QBrush brush(Qt::green);
    if(this->IsSeen){
        if(this->MyGrid->Type==Grid::GRASS)
            brush.setColor(Qt::green);
        if(this->MyGrid->Type==Grid::SAND)
            brush.setColor(Qt::yellow);
        if(this->MyGrid->Type==Grid::FOREST)
            brush.setColor(Qt::cyan);
        if(this->MyGrid->Type==Grid::HILL)
            brush.setColor(Qt::lightGray);
    }
    else{

        if(this->MyGrid->Type==Grid::GRASS)
            brush.setColor(Qt::darkGreen);
        if(this->MyGrid->Type==Grid::SAND)
            brush.setColor(Qt::darkYellow);
        if(this->MyGrid->Type==Grid::FOREST)
            brush.setColor(Qt::darkCyan);
        if(this->MyGrid->Type==Grid::HILL)
            brush.setColor(Qt::darkGray);
    }
    QPolygon poly;
    poly<<QPoint(-20*Size,-35*Size)<<QPoint(20*Size,-35*Size)<<QPoint(40*Size,0)<<QPoint(20*Size,35*Size)<<QPoint(-20*Size,35*Size)<<QPoint(-40*Size,0);
    QPen pen(Qt::red);
    pen.setWidth(2*Size);
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawPolygon(poly);
    /*绘制格子结束*/


    /*通过各种状态，绘制焦点*/
    if(IsHover||RangeMode||ATKMode){
    QPolygon poly1;
    poly1<<QPoint(-15*Size,-30*Size)<<QPoint(15*Size,-30*Size)<<QPoint(33*Size,0)<<QPoint(15*Size,30*Size)<<QPoint(-15*Size,30*Size)<<QPoint(-33*Size,0);
    if(IsHover)
        pen.setColor(Qt::black);
    if(RangeMode)
        pen.setColor(Qt::blue);
    if(ATKMode)
        pen.setColor(Qt::red);
    pen.setWidth(1*Size);
    painter->setPen(pen);
    painter->drawPolygon(poly1);
    }
    /*绘制焦点结束*/


    /*绘制基地*/
    if(this->MyGrid->Construction!=NULL){
        QRectF rect(-10*Size,-10*Size,20*Size,20*Size);
        QPen rpen(getPenColor(this->MyGrid->Construction->Player));
        rpen.setWidth(2*Size);
        painter->setPen(rpen);
        painter->drawRect(rect);

    }
    /*绘制基地结束*/


    /*绘制单位*/
    if(IsSeen){
        if(this->MyGrid->NormalUnit.isEmpty()==false){
            for(int i=0;i<this->MyGrid->NormalUnit.length();i++)
                switch (this->MyGrid->NormalUnit[i]->ID) {
                case 1:{
                    QRectF rect(-5*Size,-5*Size,10*Size,10*Size);
                    QPen rpen;
                    rpen.setColor(getPenColor(this->MyGrid->NormalUnit[i]->Player));
                    rpen.setWidth(2*Size);
                    painter->setPen(rpen);
                    painter->drawRect(rect);
                    break;
                }

                case 2:{
                    QPolygon poly2;
                    poly2<<QPoint(-10*Size,0*Size)<<QPoint(10*Size,0*Size)<<QPoint(0*Size,20);
                    QPen rpen;
                    rpen.setColor(getPenColor(this->MyGrid->NormalUnit[i]->Player));
                    rpen.setWidth(2*Size);
                    painter->setPen(rpen);
                    painter->drawPolygon(poly2);
                    break;
                }
                case 3:{
                    QPolygon poly2;
                    poly2<<QPoint(-10*Size,0*Size)<<QPoint(0*Size,-30)<<QPoint(10*Size,0*Size)<<QPoint(0*Size,30);
                    QPen rpen;
                    rpen.setColor(getPenColor(this->MyGrid->NormalUnit[i]->Player));
                    rpen.setWidth(2*Size);
                    painter->setPen(rpen);
                    painter->drawPolygon(poly2);
                    break;
                }
                default:
                    break;
                }
        }

        if(this->MyGrid->FlyUnit.isEmpty()==false){
            for(int i=0;i<this->MyGrid->FlyUnit.length();i++)
                switch (this->MyGrid->FlyUnit[i]->ID) {
                case 4:{
                    QPolygon poly2;
                    poly2<<QPoint(-15*Size,0*Size)<<QPoint(15*Size,0*Size)<<QPoint(0*Size,-25);
                    QPen rpen;
                    rpen.setColor(getPenColor(this->MyGrid->FlyUnit[i]->Player));
                    rpen.setWidth(2*Size);
                    painter->setPen(rpen);
                    painter->drawPolygon(poly2);
                    break;
                }
                case 5:{
                    QPolygon poly2;
                    poly2<<QPoint(-10*Size,-5*Size)<<QPoint(5*Size,-30)<<QPoint(10*Size,-5*Size)<<QPoint(5*Size,30);
                    QPen rpen;
                    rpen.setColor(getPenColor(this->MyGrid->FlyUnit[i]->Player));
                    rpen.setWidth(2*Size);
                    painter->setPen(rpen);
                    painter->drawPolygon(poly2);
                    break;
                }
                }
        }
    }
    /*绘制单位结束*/
}

void MyItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    IsHover=1;
    update();
    this->scene()->update();
}

void MyItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){   
    IsHover=0;
    update();
    this->scene()->update();
}

QRectF MyItem::boundingRect() const{
    return QRectF(-32*Size,-38*Size,64*Size,76*Size);
}

#endif // MYITEM_H

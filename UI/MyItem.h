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
//#include<QImage>

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


    QString PixmapState;

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

    void changePixmapState(){
        static int i=1;
        i++;
        if(i==5)
            i=1;
        PixmapState=QString::number(i);
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
    QPixmap GridPixmap;

    if(this->IsSeen){
        if(this->MyGrid->Type==Grid::GRASS)
            GridPixmap.load(":/pixmap/grass/seen.png");
        if(this->MyGrid->Type==Grid::SAND)
            GridPixmap.load(":/pixmap/sand/seen.png");
        if(this->MyGrid->Type==Grid::FOREST)
            GridPixmap.load(":/pixmap/forest/seen.png");
        if(this->MyGrid->Type==Grid::HILL)
            GridPixmap.load(":/pixmap/hill/seen.png");

    }
    else{

        if(this->MyGrid->Type==Grid::GRASS)
            GridPixmap.load(":/pixmap/grass/unseen.png");
        if(this->MyGrid->Type==Grid::SAND)
            GridPixmap.load(":/pixmap/sand/unseen.png");
        if(this->MyGrid->Type==Grid::FOREST)
            GridPixmap.load(":/pixmap/forest/unseen.png");
        if(this->MyGrid->Type==Grid::HILL)
            GridPixmap.load(":/pixmap/hill/unseen.png");
    }
    painter->drawPixmap(-40*Size,-35*Size,GridPixmap);
    /*绘制格子结束*/




    /*通过各种状态，绘制焦点*/
    QPixmap StatePixmap;
    if(IsHover||RangeMode||ATKMode){
        if(IsHover)
            StatePixmap.load(":/pixmap/state/hover"+PixmapState+".png");
        if(RangeMode)
            StatePixmap.load(":/pixmap/state/range"+PixmapState+".png");
        if(ATKMode)
            StatePixmap.load(":/pixmap/state/attack"+PixmapState+".png");
    }
    painter->drawPixmap(-40*Size,-35*Size,StatePixmap);
    /*绘制焦点结束*/


    /*绘制基地*/
    QPixmap BasePixmap;
    if(this->MyGrid->Construction!=NULL)
        BasePixmap.load(":/pixmap/base/base"+QString::number(this->MyGrid->Construction->Player)+PixmapState+".png");

    painter->drawPixmap(-40*Size,-35*Size,BasePixmap);
    /*绘制基地结束*/


    /*绘制单位*/
    QPixmap NormalUnitPixmap;
    if(IsSeen){
        if(this->MyGrid->NormalUnit.isEmpty()==false)
            NormalUnitPixmap.load(":/pixmap/unit/"+QString::number(this->MyGrid->NormalUnit[0]->ID)+"_"+QString::number(this->MyGrid->NormalUnit[0]->Player)+"_"+PixmapState+".png");
        painter->drawPixmap(-38*Size,-34*Size,NormalUnitPixmap);

        QPixmap FlyUnitPixmap;
        if(this->MyGrid->FlyUnit.isEmpty()==false)
            FlyUnitPixmap.load(":/pixmap/unit/"+QString::number(this->MyGrid->FlyUnit[0]->ID)+"_"+QString::number(this->MyGrid->FlyUnit[0]->Player)+"_"+PixmapState+".png");
        painter->drawPixmap(-38*Size,-34*Size,FlyUnitPixmap);
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

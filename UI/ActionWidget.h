/*行为窗口*/

#ifndef ACTIONWIDGET
#define ACTIONWIDGET
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "../Framework/Unit.h"
#include <QtOpenGL/QGLWidget>

class ActionWidget:public QWidget{
public:
    QPushButton* Attack;
    QPushButton* Move;
    QPushButton* Cure;

public:
    ActionWidget(double Size);
    ~ActionWidget(){}
    void setData(Unit* unit, int playerid);

};

ActionWidget::ActionWidget(double Size){
    this->setStyleSheet("border-image:url(:/pixmap/solid.png);");
    Attack=new QPushButton("攻击",this);
    Attack->setStyleSheet("QPushButton{border-image:url(:/pixmap/button/button1.png);color:white;}QPushButton:pressed{border-image:url(:/pixmap/button/button2.png);color:white;}QPushButton:disabled{border-image:url(:/pixmap/button/button3.png);color:grey;}");
    Move=new QPushButton("移动",this);
    Move->setStyleSheet("QPushButton{border-image:url(:/pixmap/button/button1.png);color:white;}QPushButton:pressed{border-image:url(:/pixmap/button/button2.png);color:white;}QPushButton:disabled{border-image:url(:/pixmap/button/button3.png);color:grey;}");
    Cure=new QPushButton("治疗",this);
    Cure->setStyleSheet("QPushButton{border-image:url(:/pixmap/button/button1.png);color:white;}QPushButton:pressed{border-image:url(:/pixmap/button/button2.png);color:white;}QPushButton:disabled{border-image:url(:/pixmap/button/button3.png);color:grey;}");

    Attack->setGeometry(0,0,65*Size,90*Size/3);
    Move->setGeometry(0,90*Size/3,65*Size,90*Size/3);
    Cure->setGeometry(0,90*Size/3*2,65*Size,90*Size/3);

    Attack->setEnabled(false);
    Move->setEnabled(false);
    Cure->setEnabled(false);

}

void ActionWidget::setData(Unit *unit,int playerid){
    if(unit!=NULL&&unit->Player==playerid){
        if(unit->canAttack()==true)
            Attack->setEnabled(true);
        else
            Attack->setEnabled(false);

        if(unit->canMove()==true)
            Move->setEnabled(true);
        else
            Move->setEnabled(false);

        Cure->setEnabled(true);

        if(unit->ActionPoint!=unit->Ori_ActionPoint||unit->IsATKed==1)
            Cure->setEnabled(false);
    }
    else{
        Attack->setEnabled(false);
        Move->setEnabled(false);
        Cure->setEnabled(false);
    }
}

#endif // ACTIONWIDGET

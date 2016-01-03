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
    QPushButton* Skip;

public:
    ActionWidget(double Size);
    ~ActionWidget(){}
    void setData(Unit* unit, int playerid);

};

ActionWidget::ActionWidget(double Size){
    Attack=new QPushButton("攻击",this);
    Move=new QPushButton("移动",this);
    Skip=new QPushButton("跳过",this);

    Attack->setGeometry(0,0,40*Size,65*Size/3);
    Move->setGeometry(0,65*Size/3,40*Size,65*Size/3);
    Skip->setGeometry(0,65*Size/3*2,40*Size,65*Size/3);

    Attack->setEnabled(false);
    Move->setEnabled(false);
    Skip->setEnabled(false);

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
        Skip->setEnabled(true);

        if(unit->ActionPoint==0&&unit->IsATKed==1)
            Skip->setEnabled(false);
    }
    else{
        Attack->setEnabled(false);
        Move->setEnabled(false);
        Skip->setEnabled(false);
    }
}

#endif // ACTIONWIDGET

/*单位数据窗口*/

#ifndef DATAWIDGET
#define DATAWIDGET
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include "MyItem.h"

class DataWidget:public QWidget{
public:
    DataWidget(double Size);
    ~DataWidget(){}
    void setData(Unit* unit);

public:
    QLabel ATK;
    QLabel DEF;
    QLabel Life;
    QLabel ActionPoint;
};

DataWidget::DataWidget(double Size){
    ATK.setParent(this);
    DEF.setParent(this);
    Life.setParent(this);
    ActionPoint.setParent(this);

        ATK.setGeometry(0,0,50*Size,65*Size/4);
        DEF.setGeometry(0,65*Size/4,50*Size,65*Size/4);
        Life.setGeometry(0,65*Size/4*2,50*Size,65*Size/4);
        ActionPoint.setGeometry(0,65*Size/4*3,50*Size,65*Size/4);

    this->setStyleSheet("color: rgb(255, 255, 255);background-color: rgb(100, 75, 46);");

}

void DataWidget::setData(Unit *unit){
    if(unit!=NULL){
    ATK.setText("攻："+QString::number(unit->ATK_Grand)+"/"+QString::number(unit->ATK_Sky));
    DEF.setText("防："+QString::number(unit->DEF));
    Life.setText("生："+QString::number(unit->Life));
    ActionPoint.setText("行："+QString::number(unit->ActionPoint));
    }
    else
    {
        ATK.setText("攻：");
        DEF.setText("防：");
        Life.setText("生：");
        ActionPoint.setText("行：");
    }
}


#endif // DATAWIDGET




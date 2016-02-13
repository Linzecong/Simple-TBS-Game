/*开始界面*/

#ifndef BEGINWIDGET_H
#define BEGINWIDGET_H

#include <QWidget>
#include<QVBoxLayout>
#include<QApplication>
#include<QDesktopWidget>
#include<QPushButton>
#include"ChooseMapWidget.h"
#include"LoginWidget.h"

class BeginWidget : public QWidget{
public:
    QVBoxLayout* MainLayout;
    QPushButton SingleStart;
    QPushButton OnlineStart;
    QPushButton Setting;
    QPushButton End;
    ChooseWidget Choose;
    LoginWidget Login;
public:
    BeginWidget();

};

BeginWidget::BeginWidget(){
    this->setStyleSheet("background:transparent;border-image:url(:/pixmap/background/start.png);");
    MainLayout=new QVBoxLayout;
    SingleStart.setText("");
    OnlineStart.setText("");
    Setting.setText("");
    End.setText("");

    SingleStart.setFocusPolicy(Qt::NoFocus);
    OnlineStart.setFocusPolicy(Qt::NoFocus);
    Setting.setFocusPolicy(Qt::NoFocus);
    End.setFocusPolicy(Qt::NoFocus);

    int H=QApplication::desktop()->height();
    int W=QApplication::desktop()->width();

    SingleStart.setFixedSize(W/3,H/19);
    OnlineStart.setFixedSize(W/3,H/19);
    Setting.setFixedSize(W/3,H/19);
    End.setFixedSize(W/3,H/19);

    SingleStart.setStyleSheet("QPushButton{background: transparent;border-image:url(:/pixmap/button/singlebutton1.png);}QPushButton:hover{background: transparent;border-image:url(:/pixmap/button/singlebutton2.png);}");
    OnlineStart.setStyleSheet("QPushButton{background: transparent;border-image:url(:/pixmap/button/onlinebutton1.png);}QPushButton:hover{background: transparent;border-image:url(:/pixmap/button/onlinebutton2.png);}");
    Setting.setStyleSheet("QPushButton{background: transparent;border-image:url(:/pixmap/button/setting1.png);}QPushButton:hover{background: transparent;border-image:url(:/pixmap/button/setting2.png);}");
    End.setStyleSheet("QPushButton{background: transparent;border-image:url(:/pixmap/button/end1.png);}QPushButton:hover{background: transparent;border-image:url(:/pixmap/button/end2.png);}");

    MainLayout->addSpacing(H/4);
    MainLayout->addWidget(&SingleStart,0,Qt::AlignCenter);
    MainLayout->addWidget(&OnlineStart,0,Qt::AlignCenter);
    MainLayout->addWidget(&Setting,0,Qt::AlignCenter);
    MainLayout->addWidget(&End,0,Qt::AlignCenter);
    MainLayout->addSpacing(H/4);
    this->setLayout(MainLayout);
    connect(&End,&QPushButton::clicked,this,&QWidget::close);
    connect(&SingleStart,&QPushButton::clicked,&Choose,&QWidget::show);
    connect(&SingleStart,&QPushButton::clicked,this,&QWidget::close);
    connect(&OnlineStart,&QPushButton::clicked,&Login,&QWidget::show);
}

#endif // BEGINWIDGET_H

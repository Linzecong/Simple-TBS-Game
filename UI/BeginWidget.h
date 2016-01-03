/*开始界面*/

#ifndef BEGINWIDGET_H
#define BEGINWIDGET_H

#include <QWidget>
#include<QVBoxLayout>
#include<QPushButton>
#include"ChooseWidget.h"

class BeginWidget : public QWidget{
public:
    QVBoxLayout* MainLayout;
    QPushButton Start;
    QPushButton End;
    ChooseWidget Choose;
public:
    BeginWidget();

};

BeginWidget::BeginWidget(){
    MainLayout=new QVBoxLayout;
    Start.setText("开始");
    End.setText("结束");
    MainLayout->addWidget(&Start);
    MainLayout->addWidget(&End);
    this->setLayout(MainLayout);
    connect(&End,&QPushButton::clicked,this,&QWidget::close);
    connect(&Start,&QPushButton::clicked,&Choose,&QWidget::show);
    connect(&Start,&QPushButton::clicked,this,&QWidget::close);
}

#endif // BEGINWIDGET_H

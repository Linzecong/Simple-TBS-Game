#ifndef MYLISTWIDGET
#define MYLISTWIDGET

#include <QWidget>
#include<QLabel>
#include<QList>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QListWidgetItem>
#include<QMouseEvent>
#include<QMessageBox>
#include<QScrollArea>
#include<QScrollBar>

class MyListItem : public QWidget{
public:
    MyListItem(QString str);
    ~MyListItem();



    QLabel Msg;


    QHBoxLayout* MainLayout;

    void mousePressEvent(QMouseEvent* e){
        this->setStyleSheet("background-color:yellow");
    }
    void mouseReleaseEvent(QMouseEvent* e){
        this->setStyleSheet("background-color:blue");
    }


};

MyListItem::MyListItem(QString str){

    MainLayout=new QHBoxLayout;

    MainLayout->addWidget(&Msg);
    this->setLayout(MainLayout);

    Msg.setText(str);

    this->setStyleSheet("background-color:white");
}

MyListItem::~MyListItem(){

}


#endif // MYLISTWIDGET


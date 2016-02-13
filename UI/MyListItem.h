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

    void focusin(){
        this->setStyleSheet("border-image:url(:/pixmap/button/list1.png);");
        Msg.setStyleSheet("border-image:url(:/pixmap/solid.png);color:white;");

    }

    void focusout(){
        this->setStyleSheet("border-image:url(:/pixmap/button/list2.png);");
        Msg.setStyleSheet("border-image:url(:/pixmap/solid.png);color:white;");
    }

//    void focusInEvent(QFocusEvent *e){
//        this->setStyleSheet("border-image:url(:/pixmap/button/list2.png);");
//        Msg.setStyleSheet("border-image:url(:/pixmap/solid.png);color:white;");
//        e->ignore();
//    }

//    void focusOutEvent(QFocusEvent *e){
//        this->setStyleSheet("border-image:url(:/pixmap/button/list1.png);");
//        Msg.setStyleSheet("border-image:url(:/pixmap/solid.png);color:white;");
//        e->ignore();
//    }

//    void mousePressEvent(QMouseEvent* e){
//        this->setStyleSheet("border-image:url(:/pixmap/button/list2.png);");
//        Msg.setStyleSheet("border-image:url(:/pixmap/solid.png);color:white;");
//        e->ignore();
//    }
//    void mouseReleaseEvent(QMouseEvent* e){
//        this->setStyleSheet("border-image:url(:/pixmap/button/list1.png);");
//        Msg.setStyleSheet("border-image:url(:/pixmap/solid.png);color:white;");
//        e->ignore();
//    }


};

MyListItem::MyListItem(QString str){

    MainLayout=new QHBoxLayout;

    MainLayout->addWidget(&Msg);
    this->setLayout(MainLayout);

    this->setStyleSheet("border-image:url(:/pixmap/button/list2.png);");
    Msg.setText(str);
    Msg.setAlignment(Qt::AlignCenter);
    Msg.setStyleSheet("border-image:url(:/pixmap/solid.png);color:white;");


}

MyListItem::~MyListItem(){

}


#endif // MYLISTWIDGET


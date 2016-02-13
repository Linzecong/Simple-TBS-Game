#ifndef LOGINWIDGET
#define LOGINWIDGET

#include <QWidget>
#include<QLabel>
#include<QVBoxLayout>
#include<QPushButton>
#include<QLineEdit>
#include <QtNetwork/QtNetwork>
#include<QMessageBox>
#include<QRegExpValidator>

class LoginWidget : public QWidget{
public:
    QVBoxLayout* MainLayout;

    QLabel Username_L;
    QLabel Password_L;
    QLineEdit Username;
    QLineEdit Password;
    QPushButton Login;

    QLabel ConfirmPassword_L;
    QLineEdit ConfirmPassword;
    QLabel Name_L;
    QLineEdit Name;
    QPushButton Registe;

    QTcpSocket *tcpSocket;

public:
    LoginWidget();

    void LoginClick();
    void RegisteClick();

    void readMessage();
    void sendMessage();

};

LoginWidget::LoginWidget(){
    MainLayout=new QVBoxLayout;

    Username_L.setText("用户名：");
    Password_L.setText("密码：");

    ConfirmPassword_L.setText("确认密码：");

    Name_L.setText("昵称：");

    Login.setText("登录");
    Registe.setText("注册");

    QRegExp regx("[a-zA-Z0-9]+$");
    QValidator* validator=new QRegExpValidator(regx);
    Username.setValidator(validator);
    Password.setValidator(validator);
    Password.setEchoMode(QLineEdit::Password);
    ConfirmPassword.setValidator(validator);
    ConfirmPassword.setEchoMode(QLineEdit::Password);


    MainLayout->addWidget(&Username_L);
    MainLayout->addWidget(&Username);
    MainLayout->addWidget(&Password_L);
    MainLayout->addWidget(&Password);

    MainLayout->addWidget(&ConfirmPassword_L);
    MainLayout->addWidget(&ConfirmPassword);
    MainLayout->addWidget(&Name_L);
    MainLayout->addWidget(&Name);

    MainLayout->addWidget(&Login);
    MainLayout->addWidget(&Registe);

    ConfirmPassword_L.setVisible(false);
    ConfirmPassword.setVisible(false);
    Name_L.setVisible(false);
    Name.setVisible(false);
    connect(&Login,&QPushButton::clicked,this,&LoginWidget::LoginClick);
    connect(&Registe,&QPushButton::clicked,this,&LoginWidget::RegisteClick);


    this->setLayout(MainLayout);

}

void LoginWidget::LoginClick(){
    if(Login.text()=="注册"){

        if(Password.text()!=ConfirmPassword.text()){
            QMessageBox::information(this,"提示","两次密码不一致");
            return;
        }
        else{
        tcpSocket = new QTcpSocket(this);
        connect(tcpSocket,&QTcpSocket::readyRead,this,&LoginWidget::readMessage);
        tcpSocket->connectToHost("119.29.15.43",6666);
        QString out="zhuce|||"+Username.text()+"|||"+Password.text()+"|||"+Name.text();
        tcpSocket->write(out.toUtf8());
        }

    }
    else{
        tcpSocket = new QTcpSocket(this);
        connect(tcpSocket,&QTcpSocket::readyRead,this,&LoginWidget::readMessage);
        tcpSocket->connectToHost("119.29.15.43",6666);

        QString out="denglu|||"+Username.text()+"|||"+Password.text();
        tcpSocket->write(out.toUtf8());
    }
}

void LoginWidget::RegisteClick(){
    static bool state=0;
    if(state==0){
        ConfirmPassword_L.setVisible(true);
        ConfirmPassword.setVisible(true);
        Name_L.setVisible(true);
        Name.setVisible(true);
        Registe.setText("返回登录");
        Login.setText("注册");
        state=1;
    }
    else{
        ConfirmPassword_L.setVisible(false);
        ConfirmPassword.setVisible(false);
        Name_L.setVisible(false);
        Name.setVisible(false);
        Registe.setText("注册");
        Login.setText("登录");
        state=0;
    }
}

void LoginWidget::readMessage(){

    QString message =  QString::fromUtf8(tcpSocket->readAll());
    if(message=="zhuce|||chenggong"){
        QMessageBox::information(this,"提示","注册成功！");
        RegisteClick();
        return;
    }

    if(message=="denglu|||chenggong"){
        QMessageBox::information(this,"提示","登陆成功");
        return;
    }


}

#endif // LOGINWIDGET


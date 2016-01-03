/*研究科技窗口*/

#ifndef STUDYWIDGET_H
#define STUDYWIDGET_H
#include "ui_studywidget.h"
#include <QDialog>
#include "../Framework/Player.h"

namespace Ui {
class StudyWidget;
}

class StudyWidget : public QDialog{
public:
    Player* Me;
public:
    StudyWidget(Player* a);
    ~StudyWidget();
    void Studied_Click();
    void CanStudy_Click();
    void StudyButton_Click();
    int Choose;
    bool IsStudied;
private:
    Ui::StudyWidget *ui;
};

StudyWidget::StudyWidget(Player* a):ui(new Ui::StudyWidget){
    this->setWindowState(Qt::WindowMaximized);
    ui->setupUi(this);
    Me=a;
    IsStudied=false;

    for(int i=0;i<Me->StudiedList.length();i++)
        ui->StudiedList->addItem((Technology(Me->StudiedList[i]).Name));

    for(int i=0;i<Me->CanStudyList.length();i++)
        ui->CanStudyList->addItem((Technology(Me->CanStudyList[i]).Name));

    connect(ui->StudiedList,&QListWidget::clicked,this,&StudyWidget::Studied_Click);
    connect(ui->CanStudyList,&QListWidget::clicked,this,&StudyWidget::CanStudy_Click);
    connect(ui->StudyButton,&QPushButton::clicked,this,&StudyWidget::StudyButton_Click);
    ui->StudyButton->setEnabled(false);
}

void StudyWidget::Studied_Click(){
    for(int i=0;i<Me->StudiedList.length();i++){
        if(Technology(Me->StudiedList[i]).Name==ui->StudiedList->currentItem()->text())
            ui->Des->setText((Technology(Me->StudiedList[i]).Des));
    }
    ui->Cost->setText("已训练");
    ui->StudyButton->setEnabled(false);
}

void StudyWidget::CanStudy_Click(){
    for(int i=0;i<Me->CanStudyList.length();i++){
        if(Technology(Me->CanStudyList[i]).Name==ui->CanStudyList->currentItem()->text()){
            Choose=Me->CanStudyList[i];
            ui->Des->setText((Technology(Me->CanStudyList[i]).Des));
            if(Technology(Me->CanStudyList[i]).Cost>Me->Coin)
            ui->StudyButton->setEnabled(false);
            else
                ui->StudyButton->setEnabled(true);
            ui->Cost->setText(QString::number(Technology(Me->CanStudyList[i]).Cost)+"/"+QString::number(Me->Coin));
        }
    }
}

void StudyWidget::StudyButton_Click(){
     Me->study(Choose);
     IsStudied=true;
     this->close();
}

StudyWidget::~StudyWidget(){
    delete ui;
}

#endif // STUDYWIDGET_H

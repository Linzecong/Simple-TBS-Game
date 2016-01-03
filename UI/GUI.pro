#-------------------------------------------------
#
# Project created by QtCreator 2015-08-15T21:15:33
#
#-------------------------------------------------

QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app
QT+=opengl

SOURCES += main.cpp

HEADERS  += \
    MyItem.h \
    BattleWidget.h \
    BaseWidget.h \
    ChooseWidget.h \
    BeginWidget.h \
    TrainWidget.h \
    StudyWidget.h \
    DataWidget.h \
    ActionWidget.h \
    ../Framework/Base.h \
    ../Framework/Grid.h \
    ../Framework/Map.h \
    ../Framework/Player.h \
    ../Framework/System.h \
    ../Framework/Technology.h \
    ../Framework/Unit.h

FORMS += \
    basewidget.ui \
    choosewidget.ui \
    studywidget.ui \
    trainwidget.ui

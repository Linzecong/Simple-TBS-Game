#-------------------------------------------------
#
# Project created by QtCreator 2015-08-15T21:15:33
#
#-------------------------------------------------

QT       += core gui
CONFIG+=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app
QT+=opengl
QT +=network
SOURCES += main.cpp

HEADERS  += \
    MyItem.h \
    BattleWidget.h \
    BaseWidget.h \
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
    ../Framework/Unit.h \
    MyListItem.h \
    ChooseMapWidget.h \
    ChooseRaceWidget.h \
    LoginWidget.h

FORMS += \
    basewidget.ui \
    studywidget.ui \
    trainwidget.ui

RESOURCES += \
    image.qrc

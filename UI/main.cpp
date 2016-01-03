
#include "MyItem.h"
#include "BeginWidget.h"
#include <QApplication>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BeginWidget w;



    w.show();

    return a.exec();
}

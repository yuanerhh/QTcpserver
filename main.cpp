#include "widget.h"
#include "client.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setGeometry(500,  400, w.width(), w.height());
    w.show();

    client w2;
    w2.setGeometry(1100, 400, w2.width(), w2.height());
    w2.show();

    return a.exec();
}

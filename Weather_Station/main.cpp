#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.setWindowTitle("Weather Station");
    w.setFixedSize(400,224);
    w.show();

    return a.exec();
}

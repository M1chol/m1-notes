#include "notes.h"
#include "tabletcanvas.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TabletCanvas *canvas = new TabletCanvas;
    Notes w(canvas);
    w.resize(800, 600);
    w.show();
    return a.exec();
}

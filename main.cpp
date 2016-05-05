#include "mainwindow.h"
#include <QApplication>
#include <TApplication.h>
#include <TSystem.h>
#include <QThread>

#include "qmaincanvas.h"

int main(int argc, char *argv[])
{
    TApplication rootapp("Simple Qt ROOT Application", &argc, argv);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QObject::connect( qApp, SIGNAL(lastWindowClosed()), qApp, SLOT(quit()) );
    return a.exec();
}

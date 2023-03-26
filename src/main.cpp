#include <QtWidgets/QApplication>
#include <QSplashScreen>
#include <QTimer>
#include "MainWindow.h"
#include "Controller.h"
#include "Model.h"
#include "Chart.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/Icons/ChartApp.png"));

    QSplashScreen* splash = new QSplashScreen;
    splash->setPixmap(QPixmap("://Icons/EasyCharts.png"));

    Controller c;
    Model m;
    MainWindow w;

    splash->show();
    QTimer::singleShot(1500, splash, SLOT(close()));
    QTimer::singleShot(1500, &w, SLOT(showMaximized()));

    c.setModel(&m);
    c.setView(&w);
    w.setController(&c);
    return a.exec();
}

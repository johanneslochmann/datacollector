#include "mainwindow.hxx"
#include "datacollector.hxx"

int main(int argc, char *argv[])
{
    DataCollector a(argc, argv);
    MainWindow w;
    w.showMaximized();

    return a.exec();
}

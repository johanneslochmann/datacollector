#include "mainwindow.hxx"
#include "datacollector.hxx"

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("datacollector");
    QCoreApplication::setApplicationVersion("2.5");
    QCoreApplication::setOrganizationName("jolodev");
    QCoreApplication::setOrganizationDomain("johanneslochmann.blogspot.com");
    QApplication::setApplicationDisplayName(QObject::tr("%1 V. %2")
                                            .arg(QCoreApplication::applicationName())
                                            .arg(QCoreApplication::applicationVersion()));
    DataCollector a(argc, argv);
    MainWindow w;
    w.showMaximized();

    return a.exec();
}

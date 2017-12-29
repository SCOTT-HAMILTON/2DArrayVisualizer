#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(12, 12);
    w.show();
    
    std::cout << "distance : " << MainWindow::distance(QPoint(0, 0), QPoint(0, 10)) << std::endl;
    
    return a.exec();
}

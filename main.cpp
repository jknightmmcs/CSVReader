#include "csvreadermainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);    
    CSVReaderMainWindow w;
    w.show();    

    return a.exec();
}

#include <QApplication>
#include <QString>
#include "filemanager.h"
#include "texthandler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileManager w;

    w.Dialog();


    //w.show();
    
    return a.exec();
}

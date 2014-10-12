
#include <QApplication>
#include <QTime>
#include <QMainWindow>

#include "graphicWidget.h"
#include "node.h"
#include "mainWindow.h"
#include <iostream>

int main(int argc, char *argv[])
{  
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.setWindowTitle(" Hash Line Demo ");
    mainWindow.setFixedSize( 1000, 800 );
    mainWindow.show();
    return app.exec();
}

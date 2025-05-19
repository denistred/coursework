#include <iostream>
#include <QApplication>
#include "mainwindow.h"
#include "person.h"
#include <QString>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow main_window;
    Person person;
    person.setName(QString("Denis"));
    std::cout << person.getName().toStdString() << std::endl;
    main_window.show();
    return app.exec();
}
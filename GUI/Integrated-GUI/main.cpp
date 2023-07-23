#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include "preprocessing.h"
#include "customerdialog.h"
#include <QTextStream>
#include <QCoreApplication>
#include <QDebug>


// The file is global to be able to close it.
QFile file(CSS_FILE_PATH);

QString read_css_file()
{
    if( !file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        return "";
    }
    QTextStream in(&file);
    return in.readAll();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString css = read_css_file();
    if(!css.isEmpty())
    {
        a.setStyleSheet(css);
    }
    // Closing any opened file is a must.
    file.close();

    MainWindow w;
    w.show();

    return a.exec();
}

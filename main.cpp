#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>
#include <QDebug>
#include "connection.h"
#include <QtWidgets>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Set the app style sheet

  QFile styleSheetFile("C:/Users/cheri/Documents/ESPRIT/2eme/1- Projet C++/PROJET/Adaptic.qss");
  styleSheetFile.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(styleSheetFile.readAll());
  a.setStyleSheet(styleSheet);


    Connection c;
    bool test=c.createconnect();
    MainWindow w;

    if(test)
    {
        w.show();

        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    return a.exec();
}

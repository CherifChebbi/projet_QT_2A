#include "notification.h"
#include <QSystemTrayIcon>
#include<QString>

notification::notification()
{
    num=0;
}
notification::notification(QString titre,QString text)
{
  this->text=text;
  this->titre=titre;
}

void notification::afficher()
{

    QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
    notifyIcon->setIcon(QIcon("C:/Users/cheri/Documents/ESPRIT/2eme/1- Projet C++/reminder.png"));

     notifyIcon->show();
     notifyIcon->showMessage("VOUS  AVEZ UN EVENEMENT AUJOURD'HUI ",text,QSystemTrayIcon::Information,15000);
      notifyIcon->hide();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "evenement.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QDebug>
#include <QSqlQuery>
#include <QMainWindow>
#include <QDate>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Evenement E;

    ui->setupUi(this);
    ui->le_id->setValidator(new QIntValidator(0, 9999999, this));
    ui->tab_evenement->setModel(E.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{

    QString nom=ui->le_nom->text();
    int id=ui->le_id->text().toInt();
    QString type=ui->le_type->text();
    QString localisation=ui->la_localisation->text();
    QDate date=ui->la_date->date();
    int nbr_invites=ui->le_nbr_invites->text().toInt();

    Evenement E(nom,id,type,localisation,date,nbr_invites);

     bool test=E.ajouter();


     if (test)
     {
        QMessageBox::information(nullptr, QObject::tr("OK"),
              QObject::tr("Ajout avec succès.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_evenement->setModel(E.afficher());


     }
     else
         QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
               QObject::tr("Echec d'ajout.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pb_supprimer_clicked()
{
     Evenement E1;
     E1.setid(ui->le_id_supp->text().toInt());
     bool test=E1.supprimer(E1.getid());
         QMessageBox msgBox;

         if(test)
         {
             msgBox.setText("Suppression avec succès.");
              ui->tab_evenement->setModel(E1.afficher());

         }
         else

            msgBox.setText("Echec de suppression");
            msgBox.exec();

}

void MainWindow::on_pb_modifer_clicked()
{

    QString nom=ui->le_nom->text();
    int id=ui->le_id->text().toInt();
    QString type=ui->le_type->text();
    QString localisation=ui->la_localisation->text();
    QDate date=ui->la_date->date();
    int nbr_invites=ui->le_nbr_invites->text().toInt();

    Evenement E1(nom,id,type,localisation,date,nbr_invites);

     bool test2=E1.modifier();


     if (test2)
     {
        QMessageBox::information(nullptr, QObject::tr("OK"),
              QObject::tr("Modification avec succés\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_evenement->setModel(E1.afficher());


     }
     else
         QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
               QObject::tr("Echec de modification.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
}



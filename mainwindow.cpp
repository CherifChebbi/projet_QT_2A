#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "evenement.h"
#include "stati.h"
#include "notification.h"

#include <QFileDialog>
#include <QTextDocument>
#include <QTextStream>
#include <QPdfWriter>
#include <QVector>
#include <QPrinter>
#include <QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QPainter>
#include <QDateTime>
#include <QDate>
#include <QSortFilterProxyModel>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QMediaPlayer>
#include <QVideoWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Evenement E;

    ui->setupUi(this);
    ui->tab_evenement->setModel(E.afficher());

    QValidator *validator = new QIntValidator(1, 999999, this);

        ui->le_id->setValidator(validator);
        ui->le_id_supp->setValidator(validator);
        ui->le_nbr_invites->setValidator(validator);

        ui->le_nom->setValidator(validator);
        ui->le_type->setValidator(validator);
        ui->la_localisation->setValidator(validator);


        ui->la_localisation->setMaxLength(20);
        ui->le_nom->setMaxLength(20);
        ui->le_type->setMaxLength(20);

        ui->le_nom->setValidator(new QRegExpValidator(QRegExp("[A-Z][a-z]*")));
        ui->le_type->setValidator(new QRegExpValidator(QRegExp("[A-Z][a-z]*")));
        ui->la_localisation->setValidator(new QRegExpValidator(QRegExp("[A-Z][a-z]*")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
      QMessageBox msgBox;

     if (test)
     {
         ui->tab_evenement->setModel(E.afficher());
         QMessageBox::information(nullptr, QObject::tr("OK"),
              QObject::tr("Ajout avec succès.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
         ui->le_nom->clear();
         ui->le_id->clear();
         ui->le_type->clear();
         ui->la_localisation->clear();
         ui->la_date->clear();
         ui->le_nbr_invites->clear();

     }
     else
     {
         QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
               QObject::tr("Echec d'ajout.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
          ui->le_nom->clear();
          ui->le_id->clear();
          ui->le_type->clear();
          ui->la_localisation->clear();
          ui->la_date->clear();
          ui->le_nbr_invites->clear();
     }
}

void MainWindow::on_pb_supprimer_clicked()
{
     Evenement E;

     E.setid(ui->le_id_supp->text().toInt());
     bool test=E.supprimer(E.getid());
        QMessageBox msgBox;

         if(test)
         {

                msgBox.setText("Suppression avec succès.");
              ui->tab_evenement->setModel(E.afficher());

              ui->le_id_supp->clear();

         }
         else
         {
             msgBox.setText("Echec de suppression");
              ui->le_id_supp->clear();

         }
      msgBox.exec();
}




///////////////////////////////////////////

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

        ui->le_nom->clear();
        ui->le_id->clear();
        ui->le_type->clear();
        ui->la_localisation->clear();
        ui->la_date->clear();
        ui->le_nbr_invites->clear();



     }
     else
         QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
               QObject::tr("Echec de modification.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);

         ui->le_nom->clear();
         ui->le_id->clear();
         ui->le_type->clear();
         ui->la_localisation->clear();
         ui->la_date->clear();
         ui->le_nbr_invites->clear();

}

/////////////////////////////////////////////////////////////////////////////////////
//SELECT FROM TABLE
void MainWindow::on_tab_evenement_clicked(const QModelIndex &index)
{
     selected=ui->tab_evenement->model()->data(index).toInt();
     QString s = QString::number(selected);

     ui->le_id_supp->setText(s);
     ui->id_modif->setText(s);
     ui->le_id->setText(s);
}

////////////////////////////////////////////
void MainWindow::on_load_clicked()
{

    QSqlQueryModel *model= new QSqlQueryModel();

        QSqlQuery  *query= new QSqlQuery();

         query->prepare("SELECT ID from EVENEMENT ");
         query->exec();
         model->setQuery(*query);

         ui->comboBox_load->setModel(model);

         //eid = ui->comboBox_load->currentText();
}

void MainWindow::on_comboBox_load_currentIndexChanged(const QString &arg1)
{


    QSqlQueryModel *model= new QSqlQueryModel();
     QSqlQuery*query= new QSqlQuery();

     query->prepare("SELECT * FROM EVENEMENT WHERE ID='"+arg1+"' ");

     if(query->exec())
      {
          while (query->next())
          {
              ui->nom_modif->setText(query->value(0).toString());
              ui->id_modif->setText(query->value(1).toString());
              ui->type_modif->setText(query->value(2).toString());
              ui->localisation_modif->setText(query->value(3).toString());
              ui->date_modif->setDate(query->value(4).toDate());
              ui->invites_modif->setText(query->value(5).toString());
          }
      }
      model->setQuery(*query);
}

void MainWindow::on_buttonBox_accepted()
{
        Evenement E;

         E.setnom(ui->nom_modif->text());
         E.setid(ui->id_modif->text().toInt());
         E.settype(ui->type_modif->text());
         E.setdate(ui->date_modif->date());
         E.setlocalisation(ui->localisation_modif->text());
         E.setnbr_invites(ui->invites_modif->text().toInt());

        bool test=E.modifier();
       if(test)

       {
           E.modifier();
           QMessageBox::information(nullptr, QObject::tr("modifier avec succes"),
                                      QObject::tr("UPADTTE successful.\n"
                                                  "Click Cancel to exit."), QMessageBox::Cancel);
                  }
                      else
                          QMessageBox::critical(nullptr, QObject::tr("modifier errer"),
                                      QObject::tr("UPDATE failed.\n"
                                                  "Click Cancel to exit."), QMessageBox::Cancel);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

//RECHERCHE

void MainWindow::on_pb_rechercher_clicked()
{
    int id = ui->le_rechercher->text().toInt();
       bool test=E.RechercheParID(id);
        if(test)
        {

            QMessageBox::information(nullptr, QObject::tr("ID existe"),
                        QObject::tr("ID existe.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tab_rechercher->setModel( E.afficherID(id));//refresh

            ui->le_rechercher->clear();

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("ID n'existe pas"),
                        QObject::tr("ID n'existe pas !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            ui->le_rechercher->clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//TRI
void MainWindow::on_radioButton_id_clicked()
{
    Evenement *E = new Evenement();
     ui->tab_evenement->setModel(E->tri_ID());
}

void MainWindow::on_radioButton_nom_clicked()
{
    Evenement *E = new Evenement();
     ui->tab_evenement->setModel(E->tri_nom());
}

void MainWindow::on_radioButton_invites_clicked()
{
    Evenement *E = new Evenement();
     ui->tab_evenement->setModel(E->tri_nbr_invites());
}

void MainWindow::on_radioButton_date_clicked()
{
    Evenement *E = new Evenement();
     ui->tab_evenement->setModel(E->tri_date());
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pb_imprimer_clicked()
{
    QString strStream;
                QTextStream out(&strStream);
                const int rowCount = ui->tab_evenement->model()->rowCount();
                const int columnCount =ui->tab_evenement->model()->columnCount();

                out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("eleve")
                        <<  "</head>\n"
                        "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                            "<img src=':/new/prefix1/icon/logo.webp' width='100' height='100'>\n"
                            "<h1>Liste des abonnes</h1>"



                            "<table border=1 cellspacing=0 cellpadding=2>\n";


                // headers
                    out << "<thead><tr bgcolor=#f0f0f0>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->tab_evenement->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tab_evenement->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tab_evenement->isColumnHidden(column)) {
                                   QString data = ui->tab_evenement->model()->data(ui->tab_evenement->model()->index(row, column)).toString().simplified();
                                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                               }
                           }
                           out << "</tr>\n";
                       }
                       out <<  "</table>\n"
                           "</body>\n"
                           "</html>\n";

                       QTextDocument *document = new QTextDocument();
                       document->setHtml(strStream);

                       QPrinter printer;

                       QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                       if (dialog->exec() == QDialog::Accepted) {
                           document->print(&printer);}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pb_pdf_clicked()
{

        QPdfWriter pdf("C:/Users/cheri/Documents/ESPRIT/2eme/1- Projet C++/PROJET/pdf/Evenement.pdf");

       QPainter painter(&pdf);
       int i = 4000;
              painter.setPen(Qt::red);
              painter.setFont(QFont("Algerian", 30));
              painter.drawText(2000,1400,"LISTES DES EVENEMENTS ");

              painter.setPen(Qt::black);
              painter.setFont(QFont("Arial Black", 15));
              painter.drawRect(100,100,9400,2500);
              painter.drawRect(100,3000,9400,500);


              painter.setFont(QFont("Cambria", 10));
              painter.drawText(500,3300,"NOM");
              painter.drawText(2000,3300,"ID");
              painter.drawText(3000,3300,"TYPE");
              painter.drawText(4000,3300,"LOCALISATION");
              painter.drawText(6000,3300,"DATE");
              painter.drawText(8500,3300,"INVITES");

              painter.drawRect(100,3000,9400,9000);

              QSqlQuery query;
              query.prepare("select * from EVENEMENT");
              query.exec();
              while (query.next())
              {
                  painter.drawText(500,i,query.value(0).toString());
                  painter.drawText(2000,i,query.value(1).toString());
                  painter.drawText(3000,i,query.value(2).toString());
                  painter.drawText(4000,i,query.value(3).toString());
                  painter.drawText(6000,i,query.value(4).toString());
                  painter.drawText(8500,i,query.value(5).toString());

                 i = i + 350;
              }
              QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
              QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//EXCEL

void MainWindow::on_excel_clicked()
{
    QTableView *table;
   table = ui->tab_evenement;


   QString filters("CSV files (*.csv);;All files (*.*)");
   QString defaultFilter("CSV files (*.csv)");
   QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                      filters, &defaultFilter);
   QFile file(fileName);

   QAbstractItemModel *model =  table->model();
   if (file.open(QFile::WriteOnly | QFile::Truncate)) {
       QTextStream data(&file);
       QStringList strList;
       for (int i = 0; i < model->columnCount(); i++) {
           if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
               strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
           else
               strList.append("");
       }
       data << strList.join(";") << "\n";
       for (int i = 0; i < model->rowCount(); i++) {
           strList.clear();
           for (int j = 0; j < model->columnCount(); j++) {

               if (model->data(model->index(i, j)).toString().length() > 0)
                   strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
               else
                   strList.append("");
           }
           data << strList.join(";") + "\n";
       }
       file.close();
       QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
   }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//STATISTIQUE:
void MainWindow::on_statistique_clicked()
{
    stati s;
    s.exec();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CALENDRIER
/*
void MainWindow::on_calendarWidget_selectionChanged()
{
     notification N;
    //QString x=ui->calendarWidget->selectedDate().toString("dd-MM-yy");

     QDate x=ui->calendarWidget->selectedDate();
     QString xs=x.toString("dd-MM-yy");
   // ui->lineEdit_calendar_affichage->setText(x);
    ui->lineEdit_calendar_affichage->setText(xs);

    //ui->tableView_calendar->setModel(E.afficher_calendar(x));

    ui->tableView_calendar->setModel(E.afficher_calendar(xs));

    N.afficher();
}
*/
void MainWindow::on_calendarWidget_selectionChanged()
{
     notification N;
    QDate x=ui->calendarWidget->selectedDate();

    QString xs=x.toString("dd-MM-yy");
    ui->lineEdit_calendar_affichage->setText(xs);

    bool test=E.RechercheParDate(x);
        if(test)
        {
                    N.afficher();
            /*QMessageBox::information(nullptr, QObject::tr("VOUS AVEZ UN EVENEMENT AUJOURD'HUI"),
                        QObject::tr("VOUS AVEZ UN EVENEMENT AUJOURD'HUI\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);*/
             N.afficher();

           ui->tableView_calendar->setModel(E.afficher_calendar(xs));

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("VOUS N'AVEZ PAS D'EVENEMENT AUJOURD'HUI"),
                        QObject::tr("VOUS N' AVEZ PAS D'EVENEMENT AUJOURD'HUI !.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//VIDEO

void MainWindow::on_play_clicked()
{
    player= new QMediaPlayer;
    vw=new QVideoWidget;


    auto filename=QFileDialog::getOpenFileName(this,"import mp4 file","C:/Users/cheri/Documents/ESPRIT/2eme/1- Projet C++/PROJET/video/Eminem.mp4","Video Files(*.mp4)");

    player->setVideoOutput(vw);
    player->setMedia(QUrl::fromLocalFile(filename));
    vw->setGeometry(100,100,300,400);
    vw->show();
    player->play();

}

void MainWindow::on_stop_clicked()
{
    player->stop();
    vw->close();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
void MainWindow::update_label()
{
    QSqlQuery query;
     QByteArray data="";
   //QByteArray nom ,pwd,grade;
     QString nom="" ,pwd="",grade="";

    data=A.read_from_arduino();
     qDebug() <<  " data is " <<data;
     ch=ch+data;
     qDebug() <<  " ch is " <<ch;


    if(ch!="" && ch.length()==12)
       {
        if(ch==" 90 56 3C 22")
         {
         QString id="2222";
         query.prepare("SELECT * FROM EVENEMENT WHERE ID='"+id+"'  ");
         qDebug() << query.exec();
         while (query.next())
         {
           nom =query.value(1).toString();
         }
         qDebug() << nom;

         ui->le_nom->setText(nom);

         QString message ="Bienvenue "+ nom;
         QByteArray br = message.toUtf8();
         A.write_to_arduino(br);
         }


        else if(ch=="03 30 7B A7")
        {
        QString id="1111";
        query.prepare("SELECT * FROM EVENEMENT WHERE ID='"+id+"'");
        qDebug() << query.exec();
        while (query.next())
        {
        nom =query.value(1).toString();

        }
        qDebug() << nom;

        ui->le_nom->setText(nom);

        QString message ="Bienvenue "+ nom;
        QByteArray br = message.toUtf8();
        A.write_to_arduino(br);
        }

        else
        {
            QString message ="donne inaccessible";
            QByteArray br = message.toUtf8();
            A.write_to_arduino(br);
            QMessageBox::critical(nullptr,QObject::tr("login failed"),
                                    QObject::tr("FAILED TO connected ..........  \n"
                                                 "acces denied \n"

                                                "Click Cancel to exit."),QMessageBox::Cancel);
        }

       }

    if(ch.length()==12)
     {
      ch="";
     }
}*/
////////

void MainWindow::update_label()
{
    //data = a.read_from_arduino();
    if(data=="1"){
    ui->label->setText("etat verifie");
    ui->label_2->setText("ON");



    QMessageBox::critical(nullptr, QObject::tr("etat verifie"),

                QObject::tr("ETAT DETECTEE.\n"

                            "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else if(data=="0"){
        ui->label->setText("PAS DE DETECTION");
        ui->label_2->setText("OFF");



    }
    qDebug()<<"data"<<data;
}

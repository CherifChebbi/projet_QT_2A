#ifndef EVENEMENT_H
#define EVENEMENT_H

#include <QString>
#include <QSqlQueryModel>
#include <QDate>

class Evenement
{

private:

    QString nom;
    int id;
    QString type;
    QString localisation;
     QDate date;
    int nbr_invites;

public:
    //CONSTRUCTEURS
    Evenement();
    Evenement(QString,int,QString,QString,QDate,int);

    //GETTERS

    QString getnom();
    int getid();
    QString gettype();
    QString getlocalisation();
    QDate getdate();
    int getnbr_invites();


    //SETTERS

    void setnom(QString);
    void setid(int);
    void settype(QString);
    void setlocalisation(QString);
    void setdate( QDate);
    void setnbr_invites(int);

    //FONCTIONALITES DE BASE RELATIVES A L ENTITE EVENEMENT
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool  modifier();


    bool RechercheParID(int IDrecherche);

    QSqlQueryModel * tri_ID();
    QSqlQueryModel * tri_nom();
    QSqlQueryModel * tri_nbr_invites();
    QSqlQueryModel * tri_date();

   // QSqlQueryModel * afficher_calendar(QDate x);
    QSqlQueryModel * afficher_calendar(QString x);

    QSqlQueryModel * chercher(QString recherche);
    QSqlQueryModel * afficherID(int id);

    bool RechercheParDate(QDate DATEErech);

};

#endif // EVENEMENT_H

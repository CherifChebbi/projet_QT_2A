#ifndef EVENEMENT_H
#define EVENEMENT_H

#include <QString>
#include <QSqlQueryModel>
#include <QDate>

class Evenement
{
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


private:

    QString nom;
    int id;
    QString type;
    QString localisation;
     QDate date;
    int nbr_invites;

};

#endif // EVENEMENT_H

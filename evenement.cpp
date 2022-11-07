#include "evenement.h"
#include <QString>
#include <QSqlQuery>
#include<QSqlError>
#include <QDebug>
#include <QObject>
#include <QDate>

Evenement::Evenement()
{
     nom="";
     id=0;
     type="";
     localisation="";
     nbr_invites=0;
}

Evenement::Evenement(QString nom,int id,QString type,QString localisation,QDate date,int nbr_invites)
{

    this->nom=nom;
    this->id=id;
    this->type=type;
    this->localisation=localisation;
    this->date=date;
    this->nbr_invites=nbr_invites;
}



QString Evenement::getnom(){return nom;}
int Evenement::getid(){return id;}
QString Evenement::gettype(){return type;}
QString Evenement::getlocalisation(){return localisation;}
QDate Evenement::getdate(){return date;}
int Evenement::getnbr_invites(){return nbr_invites;}




void Evenement::setnom(QString nom){this->nom=nom;}
void Evenement::setid(int id){this->id=id;}
void Evenement::settype(QString type){this->type=type;}
void Evenement::setlocalisation(QString localisation){this->localisation=localisation;}
void Evenement::setdate(QDate date){this->date=date;}
void Evenement::setnbr_invites(int nbr_invites){this->nbr_invites=nbr_invites;}

bool Evenement::ajouter()
{
    bool test=true;
    QSqlQuery query;


        query.prepare("INSERT INTO EVENEMENT(NOM,ID,TYPE,LOCALISATION,DATEE,INVITES) "
                      "VALUES (:nom,:id,:type,:localisation,:date,:nbr_invites)");

        query.bindValue(":nom",nom);
        query.bindValue(":id",id);
        query.bindValue(":type",type);
        query.bindValue(":localisation",localisation);
        query.bindValue(":date",date);
        query.bindValue(":nbr_invites",nbr_invites);

        query.exec();

        qDebug() <<query.lastError();
            return  test;

}

QSqlQueryModel* Evenement::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

        model->setQuery("SELECT* FROM EVENEMENT");


    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("LOCALISATION"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATEE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("INVITES"));

    return  model;
}

bool Evenement::supprimer(int id)
{
    QSqlQuery query;

        query.prepare("Delete from EVENEMENT where ID=:id");
        query.bindValue(":id",id);

  return query.exec();
}

bool  Evenement::modifier()
{
    bool test2=true;
    QSqlQuery query;

    query.prepare("UPDATE EVENEMENT SET ID=:id, NOM=:nom,TYPE=:type,LOCALISATION=:localisation,DATEE=:date,INVITES=:nbr_invites WHERE ID=:id");

    query.bindValue(":nom",nom);
    query.bindValue(":id",id);
    query.bindValue(":type",type);
    query.bindValue(":localisation",localisation);
    query.bindValue(":date",date);
    query.bindValue(":nbr_invites",nbr_invites);

    query.exec();

    qDebug() <<query.lastError();
        return  test2;

}







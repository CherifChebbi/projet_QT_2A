#include "evenement.h"
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>

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

//////////////////////////////////////////////////////////////////////////////////////////
//CRUD
bool Evenement::ajouter()
{
    Evenement E;
    //bool test=true;
    QSqlQuery query;
    QString res= QString::number(id);


    if(E.RechercheParID(id)==false)
    {
        query.prepare("INSERT INTO EVENEMENT(NOM,ID,TYPE,LOCALISATION,DATEE,INVITES) "
                      "VALUES (:nom,:id,:type,:localisation,:date,:nbr_invites)");

        query.bindValue(":nom",nom);
        query.bindValue(":id",res);
        query.bindValue(":type",type);
        query.bindValue(":localisation",localisation);
        query.bindValue(":date",date);
        query.bindValue(":nbr_invites",nbr_invites);
    }

         return query.exec();

        qDebug() <<query.lastError();
            //return  test;
}

QSqlQueryModel* Evenement::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();

        model->setQuery("SELECT* FROM EVENEMENT ");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("LOCALISATION"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATEE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("INVITES"));

    return  model;
}

////////////////////////////////////////////////////
bool Evenement::supprimer(int id)
{
    QSqlQuery query;

        query.prepare("Delete from EVENEMENT where ID=:id");
        query.bindValue(":id",id);

      return query.exec();
}

///////////////////////////////////////////////////
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
///////////////////////


//////////////////////////////////////////////////////////////////////////////////////////
//RECHERCHE PAR ID
bool Evenement::RechercheParID(int IDrecherche)
{
    QSqlQuery query;
    //QSqlRecord rec = query.record();
    QString res= QString::number(IDrecherche);

    query.prepare("SELECT * FROM EVENEMENT WHERE ID=:IDrecherche");
    query.bindValue(":IDrecherche",res);
    query.exec();

    if (query.next())
    {
        return true;
         qDebug()<<"event existe";

    }
    else
    {
        qDebug()<<"event n'existe pas";
        return false;
    }
}


QSqlQueryModel *Evenement::afficherID(int id)
    {
    QSqlQueryModel * model= new QSqlQueryModel();

     QString res= QString::number(id);

    QSqlQuery *q = new QSqlQuery;
     q->prepare("SELECT * from EVENEMENT where ID LIKE '%"+res+"%'");
      q->addBindValue(res);
       q->exec();
         model->setQuery(*q);


        return model;
    }


//////////////////////////////////////////////////////////////////////////////////////////
//TRI
QSqlQueryModel * Evenement::tri_ID()
{
    QSqlQueryModel *model= new QSqlQueryModel;
    QSqlQuery *q=new QSqlQuery();
    q->prepare("select * from EVENEMENT order by ID  asc");
    q->exec();
    model->setQuery(*q);
    return  model;
}



QSqlQueryModel * Evenement::tri_nom()
{
    QSqlQueryModel *model= new QSqlQueryModel;
    QSqlQuery *q=new QSqlQuery();
    q->prepare("select * from EVENEMENT order by NOM  asc");
    q->exec();
    model->setQuery(*q);
    return  model;
}

QSqlQueryModel * Evenement::tri_nbr_invites()
{
    QSqlQueryModel *model= new QSqlQueryModel;
    QSqlQuery *q=new QSqlQuery();
    q->prepare("select * from EVENEMENT order by INVITES  asc");
    q->exec();
    model->setQuery(*q);
    return  model;
}

QSqlQueryModel * Evenement::tri_date()
{
    QSqlQueryModel *model= new QSqlQueryModel;
    QSqlQuery *q=new QSqlQuery();
    q->prepare("select * from EVENEMENT order by DATEE  asc");
    q->exec();
    model->setQuery(*q);
    return  model;
}

//////////////////////////////////////////////////////////////////////////////////////////
/*QSqlQueryModel * Evenement::afficher_calendar(QDate x)
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("SELECT * FROM EVENEMENT WHERE DATEE LIKE x ");

model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("LOCALISATION"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATEE"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("INVITES"));

    return model;
}*/
//////////////////////////
/*QSqlQueryModel * Evenement::afficher_calendar(QString x)
{
    QSqlQueryModel * model= new QSqlQueryModel();
     QSqlQuery  q;

    QDate strDate;

    strDate = QDate::fromString(x,"dd-MM-yy");


    //model->setQuery("SELECT * from EVENEMENT where DATEE =:strDate ");

    q.prepare("SELECT * from EVENEMENT where DATEE =:strDate ");
    q.bindValue(":strDate",strDate);
     model->setQuery(q);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("LOCALISATION"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATEE"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("INVITES"));

    return model;
}
*/
//////////////////////////
bool Evenement::RechercheParDate(QDate DATEErech)
{
    QSqlQuery query;
    //QSqlRecord rec = query.record();

    query.prepare("SELECT * FROM EVENEMENT WHERE DATEE=:DATEErech ");
    query.bindValue(":DATEErech",DATEErech);
    query.exec();

    if (query.next())
    {
        return true;
         qDebug()<<"VOUS AVEZ UN EVENEMENT AUJOURD'hui ";

    }
    else
    {
        qDebug()<<"VOUS N'AVEZ PAS D'EVENEMENT AUJOURD'hui";
        return false;
    }
}
//////////////////////////
QSqlQueryModel *Evenement::afficher_calendar(QString x)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    QDate strDate = QDate::fromString(x,"dd-MM-yy");

    QSqlQuery *q = new QSqlQuery;

    q->prepare("SELECT * from EVENEMENT where DATEE =:strDate ");
    q->addBindValue(strDate);
    q->exec();
     model->setQuery(*q);


    return model;
}
/////////////////////////////////////////////////////////////////////////////////

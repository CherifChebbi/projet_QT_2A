#include "connection.h"

Connection::Connection(){}

bool Connection::createconnect()
{
 QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
 bool test=false;

db.setDatabaseName("Projet");
db.setUserName("cherif_chebbi");//inserer nom de l'utilisateur
db.setPassword("cherif63");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;
    return  test;
}

void Connection::closeConnection(){db.close();}

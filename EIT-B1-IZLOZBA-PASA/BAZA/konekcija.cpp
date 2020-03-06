#include "konekcija.h"

Konekcija::Konekcija()
{

}

bool Konekcija::dbOpen()
{
    db.setDatabaseName(dbPutanja);

    if(db.open())
    {
        QSqlQuery upit;
        upit.exec("PRAGMA foreign_key = ON;");

        return true;
    }
    else
        return false;
}

void Konekcija::dbClose()
{
    db.close();
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}

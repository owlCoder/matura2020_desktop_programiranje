#ifndef KONEKCIJA_H
#define KONEKCIJA_H

#include <QtSql/QtSql>

class Konekcija
{
    public:
        Konekcija();
        bool dbOpen();
        void dbClose();

    private:
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        QString dbPutanja = "C:/Users/Danijel/Desktop/Baza.db";  // Obavezno podesiti adresu baze!!!
    };

#endif // KONEKCIJA_H

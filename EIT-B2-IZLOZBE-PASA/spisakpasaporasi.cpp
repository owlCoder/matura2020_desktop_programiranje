#include "spisakpasaporasi.h"
#include "ui_spisakpasaporasi.h"

#include <BAZA/konekcija.h>

#include <QMessageBox>

SpisakPasaPoRasi::SpisakPasaPoRasi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpisakPasaPoRasi)
{
    ui->setupUi(this);

    Konekcija baza;
    if(!baza.dbOpen())
    {
        QMessageBox::critical(this, "Kriticna greska!!!", "Ne mozemo da ostvarimo ispravnu komunikaciju sa bazom podataka!!!");
    }
    else
    {
        QSqlQuery upit;
        upit.prepare("SELECT IzlozbaID FROM Izlozba ORDER BY IzlozbaID;");
        if(!upit.exec())
            QMessageBox::critical(this, "Kriticna greska!!!", "SQL naredba nije izvrsena!!!");
        else
        {
            QSqlQueryModel *model;
            model = new QSqlQueryModel();
            model->setQuery(upit);
            ui->izlozba->setModel(model);
        }
        upit.prepare("SELECT NazivRase FROM Rasa ORDER BY NazivRase;");
        if(!upit.exec())
            QMessageBox::critical(this, "Kriticna greska!!!", "SQL naredba nije izvrsena!!!");
        else
        {
            QSqlQueryModel *model;
            model = new QSqlQueryModel();
            model->setQuery(upit);
            ui->rasa->setModel(model);
        }
        baza.dbClose();
    }

}

SpisakPasaPoRasi::~SpisakPasaPoRasi()
{
    delete ui;
}

void SpisakPasaPoRasi::on_prikazi_clicked()
{
    Konekcija baza;
    if(!baza.dbOpen())
    {
        QMessageBox::critical(this, "Kriticna greska!!!", "Ne mozemo da ostvarimo ispravnu komunikaciju sa bazom podataka!!!");
    }
    else
    {
        QString izlozbaID = ui->izlozba->currentText();
        QString nazivRase = ui->rasa->currentText();
        QSqlQuery upit;
        upit.prepare("SELECT COUNT (*) FROM Rezultat WHERE IzlozbaID = :Izlozba AND Rezultat IS NOT NULL;");
        upit.bindValue(":Izlozba", izlozbaID);
        if(!upit.exec())
            QMessageBox::critical(this, "Kriticna greska!!!", "SQL naredba nije izvrsena!!!");
        else
        {
            QString brojPrijavljenih;
            upit.next();
            brojPrijavljenih = upit.value(0).toString();
            ui->brPrijavljenih->setText(brojPrijavljenih);
        }
        upit.prepare("SELECT COUNT (*) FROM Rezultat INNER JOIN Pas ON Rezultat.PasID = Pas.PasID "
                     "INNER JOIN Rasa ON Pas.RasaID = Rasa.RasaID WHERE Rezultat.IzlozbaID = :Izlozba "
                     "AND Rasa.NazivRase = :NazivRase AND Rezultat.Rezultat IS NOT NULL;");
        upit.bindValue(":Izlozba", izlozbaID);
        upit.bindValue(":NazivRase", nazivRase);
        if(!upit.exec())
            QMessageBox::critical(this, "Kriticna greska!!!", "SQL naredba nije izvrsena!!!");
        else
        {
            QString brojPasaTrazeneRase;
            upit.next();
            brojPasaTrazeneRase = upit.value(0).toString();
            ui->brTakmicara->setText(brojPasaTrazeneRase);
        }
        upit.prepare("SELECT Pas.Ime AS [Ime psa] FROM Pas INNER JOIN Rezultat ON Rezultat.PasID = Pas.PasID INNER JOIN Rasa ON Pas.RasaID = Rasa.RasaID WHERE "
                     "Rezultat.IzlozbaID = :Izlozba AND Rasa.NazivRase = :NazivRase AND Rezultat.Rezultat "
                     "IS NOT NULL GROUP BY Rezultat.KategorijaID;");
        upit.bindValue(":Izlozba", izlozbaID);
        upit.bindValue(":NazivRase", nazivRase);
        if(!upit.exec())
            QMessageBox::critical(this, "Kriticna greska!!!", "SQL naredba nije izvrsena!!!");
        else
        {
            QSqlQueryModel *model = new QSqlQueryModel();
            model->setQuery(upit);
            ui->prikaz->setModel(model);
        }
        baza.dbClose();
    }

}

void SpisakPasaPoRasi::on_izlaz_clicked()
{
    this -> close();
}

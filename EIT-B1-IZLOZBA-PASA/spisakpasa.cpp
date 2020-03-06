#include "spisakpasa.h"
#include "ui_spisakpasa.h"

#include "BAZA/konekcija.h"

#include <QMessageBox>

SpisakPasa::SpisakPasa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpisakPasa)
{
    ui->setupUi(this);

    Konekcija baza;

    if(!baza.dbOpen())
        QMessageBox::critical(this, "Greška!", "Konekcija sa bazom nije moguća!");
    else
    {
        QSqlQuery upit;

        upit.prepare("SELECT IzlozbaID FROM Izlozba ORDER BY IzlozbaID ASC");

        if(!upit.exec())
        {
            QMessageBox::critical(this, "Greška!", "Upit nije izvršen!");
        }
        else
        {
            QSqlQueryModel *model = new QSqlQueryModel();
            model -> setQuery(upit);
            ui -> izlozba -> setModel(model);
        }
    }
    baza.dbClose();
}

SpisakPasa::~SpisakPasa()
{
    delete ui;
}

void SpisakPasa::on_prikazi_clicked()
{
    Konekcija baza;

    if(!baza.dbOpen())
        QMessageBox::critical(this, "Greška!", "Konekcija sa bazom nije moguća!");
    else
    {
        QSqlQuery upit;
        QString izlozbaID = ui -> izlozba -> currentText();

        upit.prepare("SELECT COUNT (*) FROM Rezultat WHERE IzlozbaID = :izlozbaID;");
        upit.bindValue(":izlozbaID", izlozbaID);

        if(!upit.exec())
        {
            QMessageBox::critical(this, "Greška!", "Upit nije izvršen!");
        }
        else
        {
            QString brojPrijavljenih;
            upit.next();

            brojPrijavljenih = upit.value(0).toString();
            ui -> brPrijavljenih -> setText(brojPrijavljenih);
        }

        upit.prepare("SELECT COUNT (*) FROM Rezultat WHERE IzlozbaID = :izlozbaID AND Rezultat IS NOT NULL;");
        upit.bindValue(":izlozbaID", izlozbaID);

        if(!upit.exec())
        {
            QMessageBox::critical(this, "Greška!", "Upit nije izvršen!");
        }
        else
        {
            QString brojTakmicara;
            upit.next();

            brojTakmicara = upit.value(0).toString();
            ui -> brTakmicara -> setText(brojTakmicara);
        }

        upit.prepare("SELECT Rezultat.KategorijaID AS Sifra, Kategorija.Naziv AS [Naziv kategorije], COUNT (Rezultat.KategorijaID) AS [Broj pasa] FROM Rezultat, Kategorija;");
        upit.bindValue(":izlozbaID", izlozbaID);

        if(!upit.exec())
        {
            QMessageBox::critical(this, "Greška!", "Upit nije izvršen!");
        }
        else
        {
           QSqlQueryModel *model = new QSqlQueryModel();
           model -> setQuery(upit);
           ui -> prikaz -> setModel(model);
        }
    }
    baza.dbClose();
}

void SpisakPasa::on_izlaz_clicked()
{
    this -> close();
}

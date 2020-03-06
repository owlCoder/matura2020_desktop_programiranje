#include "prijavapasa.h"
#include "ui_prijavapasa.h"

#include "BAZA/konekcija.h"

#include <QMessageBox>

PrijavaPasa::PrijavaPasa(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrijavaPasa)
{
    ui->setupUi(this);

    Konekcija baza;

    if(!baza.dbOpen())
        QMessageBox::critical(this, "Greška!", "Konekcija sa bazom nije moguća!");
    else
    {
        QSqlQuery upit;

        upit.prepare("SELECT PasID, Ime FROM Pas ORDER BY PasID ASC;");

        if(!upit.exec())
        {
            QMessageBox::critical(this, "Greška!", "Upit nije izvršen!");
        }
        else
        {
            QStringList listaPas;

            while(upit.next())
                listaPas.append(upit.value(0).toString() + " - " + upit.value(1).toString());

            QStringListModel *modelPas;

            modelPas = new QStringListModel();
            modelPas -> setStringList(listaPas);

            ui -> pas -> setModel(modelPas);
        }

        upit.prepare("SELECT IzlozbaID, Mesto FROM Izlozba ORDER BY IzlozbaID ASC;");

        if(!upit.exec())
        {
            QMessageBox::critical(this, "Greška!", "Upit nije izvršen!");
        }
        else
        {
            QStringList listaIzlozba;

            while(upit.next())
                listaIzlozba.append(upit.value(0).toString() + " - " + upit.value(1).toString());

            QStringListModel *modelIzlozba;

            modelIzlozba = new QStringListModel();
            modelIzlozba -> setStringList(listaIzlozba);

            ui -> izlozba -> setModel(modelIzlozba);
        }

        upit.prepare("SELECT KategorijaID, Naziv FROM Kategorija ORDER BY KategorijaID ASC;");

        if(!upit.exec())
        {
            QMessageBox::critical(this, "Greška!", "Upit nije izvršen!");
        }
        else
        {
            QStringList lista;

            while(upit.next())
                lista.append(upit.value(0).toString() + " - " + upit.value(1).toString());

            QStringListModel *model;

            model = new QStringListModel();
            model -> setStringList(lista);

            ui -> kategorija -> setModel(model);
        }
    }
    baza.dbClose();
}

PrijavaPasa::~PrijavaPasa()
{
    delete ui;
}

void PrijavaPasa::on_upisi_clicked()
{
    QString pasID = ui ->  pas -> currentText();
    pasID.truncate(pasID.indexOf(" - "));

    QString izlozbaID = ui ->  izlozba -> currentText();
    izlozbaID.truncate(izlozbaID.indexOf(" - "));

    QString kategorijaID = ui ->  kategorija -> currentText();
    kategorijaID.truncate(kategorijaID.indexOf(" - "));

    Konekcija baza;

    if(!baza.dbOpen())
        QMessageBox::critical(this, "Greška!", "Konekcija sa bazom nije moguća!");
    else
    {
        QSqlQuery upit;

        upit.prepare("INSERT INTO Rezultat (IzlozbaID, KategorijaID, PasID) VALUES (:izlozbaID, :katID, :pasID);");
        upit.bindValue(":izlozbaID", izlozbaID);
        upit.bindValue(":katID", kategorijaID);
        upit.bindValue(":pasID", pasID);

        if(!upit.exec())
        {
            QMessageBox::critical(this, "Greška!", "Upit nije izvršen!");
        }
        else
        {
            QMessageBox::information(this, "Informacija!", "Uspešno ste prijavili psa za izložbu!");
        }
    }
    baza.dbClose();
}

void PrijavaPasa::on_upis_clicked()
{
    ui -> izlozba -> setEnabled(true);
    ui -> kategorija -> setEnabled(true);
    ui -> upisi -> setEnabled(true);
    ui -> obrisi -> setEnabled(false);
}

void PrijavaPasa::on_brisanje_clicked()
{
    ui -> izlozba -> setEnabled(false);
    ui -> kategorija -> setEnabled(false);
    ui -> upisi -> setEnabled(false);
    ui -> obrisi -> setEnabled(true);
}

void PrijavaPasa::on_izlaz_clicked()
{
    this -> close();
}

void PrijavaPasa::on_obrisi_clicked()
{
    QString pasID = ui ->  pas -> currentText();
    pasID.truncate(pasID.indexOf(" - "));

    Konekcija baza;

    if(!baza.dbOpen())
        QMessageBox::critical(this, "Greška!", "Konekcija sa bazom nije moguća!");
    else
    {
        QSqlQuery upit;

        upit.prepare("DELETE FROM Rezultat WHERE PasID =  (:pasID);");
        upit.bindValue(":pasID", pasID);

        if(!upit.exec())
        {
            QMessageBox::critical(this, "Greška!", "Upit nije izvršen!");
        }
        else
        {
            QMessageBox::information(this, "Informacija!", "Obrisali ste sve prijave za psa za sve izložbe!");
        }
    }
    baza.dbClose();
}

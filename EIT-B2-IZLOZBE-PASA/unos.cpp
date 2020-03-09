#include "unos.h"
#include "ui_unos.h"

#include <QMessageBox>

#include <BAZA/konekcija.h>

Unos::Unos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Unos)
{
    ui->setupUi(this);
}

Unos::~Unos()
{
    delete ui;
}

void Unos::on_upisi_clicked()
{
    QString sifraIzlozbe = ui->lineEditSifra->text();
    if(sifraIzlozbe.size() == 9)
    {
        Konekcija upis;
        if(!upis.dbOpen())
        {
            QMessageBox::critical(this, "Kriticna greska!!!", "Ne mozemo da ostvarimo ispravnu komunikaciju sa bazom podataka!!!");
        }
        else
        {
            QString mesto = ui->lineEditMesto->text();
            QString datum = ui->dateEdit->date().toString(Qt::TextDate);
            QSqlQuery upit;
            upit.prepare("INSERT INTO Izlozba (IzlozbaID, Mesto, Datum) VALUES (:IzlozbaID, :Mesto, :Datum);");
            upit.bindValue(":IzlozbaID", sifraIzlozbe);
            upit.bindValue(":Mesto", mesto);
            upit.bindValue(":Datum", datum);
            if(!upit.exec())
                QMessageBox::critical(this, "Kriticna greska!!!", "SQL naredba nije izvrsena!!!");
            else
            {
                QMessageBox::information(this, "Informacija!!!", "Uspesno ste upisali u bazu podatke o izlozbi!");
                ui->lineEditMesto->clear();
                ui->lineEditSifra->clear();
                ui->lineEditMesto->setFocus();
            }
            upis.dbClose();
        }
    }
    else
        QMessageBox::critical(this, "Kriticna greska!!!", "Neispravna sifra izlozbe!!!");

}

void Unos::on_upis_clicked()
{
    ui->lineEditSifra->clear();
    ui->lineEditSifra->setEnabled(false);
    ui->lineEditMesto->setEnabled(true);
    ui->dateEdit->setEnabled(true);
    ui->upisi->setEnabled(true);
    ui->obrisi->setEnabled(false);
}

void Unos::on_brisanje_clicked()
{
    ui->lineEditSifra->setEnabled(true);
    ui->lineEditMesto->setEnabled(false);
    ui->dateEdit->setEnabled(false);
    ui->upisi->setEnabled(false);
    ui->obrisi->setEnabled(true);
}

void Unos::on_obrisi_clicked()
{
    QString sifraIzlozbe = ui->lineEditSifra->text();
    if(sifraIzlozbe.size() == 9)
    {
        Konekcija upis;
        if(!upis.dbOpen())
        {
            QMessageBox::critical(this, "Kriticna greska!!!", "Ne mozemo da ostvarimo ispravnu komunikaciju sa bazom podataka!!!");
        }
        else
        {
            QSqlQuery upit;
            upit.prepare("DELETE FROM Izlozba WHERE IzlozbaID = (:IzlozbaID);");
            upit.bindValue(":IzlozbaID", sifraIzlozbe);
            if(!upit.exec())
                QMessageBox::critical(this, "Kriticna greska!!!", "SQL naredba nije izvrsena!!!");
            else
            {
                QMessageBox::information(this, "Informacija!!!", "Obrisali ste podatke o odabranoj izlozbi!!!");
                ui->lineEditMesto->clear();
                ui->lineEditSifra->clear();
                ui->lineEditSifra->setFocus();
            }
            upis.dbClose();
        }
    }
    else
        QMessageBox::critical(this, "Kriticna greska!!!", "Neispravna sifra izlozbe!!!");
}

void Unos::on_dateEdit_userDateChanged(const QDate &date)
{
    QString imeGrada = ui->lineEditMesto->text();
    imeGrada.truncate(3);
    if(imeGrada.size() == 2)
        imeGrada += " ";
    else if(imeGrada.size() == 1)
        imeGrada += " ";
    int mesec = date.month();
    QString mesecPrvaCifra = "";
    if(mesec < 10)
        mesecPrvaCifra = "0";
    int godina = date.year();
    QString sifraIzlozbe = "" + imeGrada.toUpper() + mesecPrvaCifra +
                           QString::number(mesec,10) + QString::number(godina);
    ui->lineEditSifra->setText(sifraIzlozbe);

}

void Unos::on_lineEditMesto_textChanged(const QString &arg1)
{
    QString imeGrada = arg1;
    imeGrada.truncate(3);
    if(imeGrada.size() == 2)
        imeGrada += " ";
    else if(imeGrada.size() == 1)
        imeGrada += " ";
    QDate datum = ui->dateEdit->date();
    QString mesec = datum.toString("MM");
    QString godina = datum.toString("yyyy");
    QString sifraIzlozbe = imeGrada.toUpper() + mesec + godina;
    ui->lineEditSifra->setText(sifraIzlozbe);
}

void Unos::on_izlaz_clicked()
{
    this -> close();
}

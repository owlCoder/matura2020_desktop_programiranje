#include "glavniprozor.h"
#include "ui_glavniprozor.h"

#include "prijavapasa.h"
#include "spisakpasa.h"

GlavniProzor::GlavniProzor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GlavniProzor)
{
    ui->setupUi(this);
}

GlavniProzor::~GlavniProzor()
{
    delete ui;
}

void GlavniProzor::on_actionPrijava_pasa_triggered()
{
    PrijavaPasa *pp = new PrijavaPasa(this);
    pp -> setModal(true);
    pp -> show();
}

void GlavniProzor::on_actionSpisak_pasa_triggered()
{
    SpisakPasa *sp = new SpisakPasa(this);
    sp -> setModal(true);
    sp -> show();
}

void GlavniProzor::on_actionIzlaz_triggered()
{
    this -> close();
}

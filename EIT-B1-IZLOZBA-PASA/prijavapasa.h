#ifndef PRIJAVAPASA_H
#define PRIJAVAPASA_H

#include <QDialog>

namespace Ui {
class PrijavaPasa;
}

class PrijavaPasa : public QDialog
{
    Q_OBJECT

public:
    explicit PrijavaPasa(QWidget *parent = nullptr);
    ~PrijavaPasa();

private slots:
    void on_upisi_clicked();
    void on_upis_clicked();
    void on_brisanje_clicked();
    void on_izlaz_clicked();
    void on_obrisi_clicked();

private:
    Ui::PrijavaPasa *ui;
};

#endif // PRIJAVAPASA_H

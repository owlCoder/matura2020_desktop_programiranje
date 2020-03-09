#ifndef UNOS_H
#define UNOS_H

#include <QDialog>

namespace Ui {
class Unos;
}

class Unos : public QDialog
{
    Q_OBJECT

public:
    explicit Unos(QWidget *parent = nullptr);
    ~Unos();

private slots:
    void on_upisi_clicked();

    void on_upis_clicked();

    void on_brisanje_clicked();

    void on_obrisi_clicked();

    void on_dateEdit_userDateChanged(const QDate &date);

    void on_lineEditMesto_textChanged(const QString &arg1);

    void on_izlaz_clicked();

private:
    Ui::Unos *ui;
};

#endif // UNOS_H

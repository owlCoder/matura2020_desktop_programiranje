#ifndef SPISAKPASAPORASI_H
#define SPISAKPASAPORASI_H

#include <QDialog>

namespace Ui {
class SpisakPasaPoRasi;
}

class SpisakPasaPoRasi : public QDialog
{
    Q_OBJECT

public:
    explicit SpisakPasaPoRasi(QWidget *parent = nullptr);
    ~SpisakPasaPoRasi();

private slots:
    void on_prikazi_clicked();

    void on_izlaz_clicked();

private:
    Ui::SpisakPasaPoRasi *ui;
};

#endif // SPISAKPASAPORASI_H

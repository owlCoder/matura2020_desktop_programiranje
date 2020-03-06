#ifndef SPISAKPASA_H
#define SPISAKPASA_H

#include <QDialog>

namespace Ui {
class SpisakPasa;
}

class SpisakPasa : public QDialog
{
    Q_OBJECT

public:
    explicit SpisakPasa(QWidget *parent = nullptr);
    ~SpisakPasa();

private slots:
    void on_prikazi_clicked();

    void on_izlaz_clicked();

private:
    Ui::SpisakPasa *ui;
};

#endif // SPISAKPASA_H

#ifndef GLAVNIPROZOR_H
#define GLAVNIPROZOR_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class GlavniProzor; }
QT_END_NAMESPACE

class GlavniProzor : public QMainWindow
{
    Q_OBJECT

public:
    GlavniProzor(QWidget *parent = nullptr);
    ~GlavniProzor();

private slots:
    void on_actionUnos_triggered();
    void on_actionSpisak_pasa_po_rasi_triggered();
    void on_actionIzlaz_triggered();

private:
    Ui::GlavniProzor *ui;
};
#endif // GLAVNIPROZOR_H

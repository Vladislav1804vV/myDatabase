#ifndef SELECTTABLE_H
#define SELECTTABLE_H

#include "table.h"

#include <QDialog>

namespace Ui {
class SelectTable;
}

class SelectTable : public QDialog
{
    Q_OBJECT

public:
    explicit SelectTable(QWidget *parent = nullptr);
    ~SelectTable();

signals:
    void selectTableWindow();

private slots:
    void on_airportsButton_clicked();
    void on_baggagesButton_clicked();
    void on_citiesButton_clicked();
    void on_clientsButton_clicked();
    void on_countriesButton_clicked();
    void on_discountsButton_clicked();
    void on_flightsButton_clicked();
    void on_gatesButton_clicked();
    void on_planesButton_clicked();
    void on_sitsButton_clicked();
    void on_ticketsButton_clicked();

private:
    Ui::SelectTable *ui;
    void closeEvent(QCloseEvent *event);
    Table* table;
};

#endif // SELECTTABLE_H

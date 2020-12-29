#ifndef TABLE_H
#define TABLE_H

#include "database.h"
#include "citieseditform.h"
#include "countrieseditform.h"
#include "baggageseditform.h"
#include "clientseditform.h"
#include "discountseditform.h"
#include "flightseditform.h"
#include "gateseditform.h"
#include "planeseditform.h"
#include "sitseditform.h"
#include "ticketseditform.h"
#include "airportseditform.h"

#include <QDialog>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>

namespace Ui {
class Table;
}

class Table : public QDialog
{
    Q_OBJECT

public:
    explicit Table(QString table, QWidget *parent = nullptr);
    ~Table();
    void setTable(QString table);

signals:
    void tableWindow();

private slots:
    void on_saveButton_clicked();
    void on_revertButton_clicked();
    void on_tableView_doubleClicked(const QModelIndex &index);
    void on_addButton_clicked();
    void on_deleteButton_clicked();

private:
    Ui::Table *ui;
    void closeEvent(QCloseEvent* event);
    QString table;
    QSqlRelationalTableModel* model;
    Database* DB;
    CitiesEditForm* citiesForm;
    CountriesEditForm* countriesForm;
    BaggagesEditForm* baggagesForm;
    ClientsEditForm* clientsForm;
    DiscountsEditForm* discountsForm;
    FlightsEditForm* flightsForm;
    GatesEditForm* gatesForm;
    PlanesEditForm* planesForm;
    SitsEditForm* sitsForm;
    TicketsEditForm* ticketsForm;
    AirportsEditForm* airportsForm;
};

#endif // TABLE_H

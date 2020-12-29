#ifndef SELECTEDFLIGHT_H
#define SELECTEDFLIGHT_H

#include "database.h"
#include "buyticket.h"

#include <QDialog>
#include <QSqlRecord>

namespace Ui {
class SelectedFlight;
}

class SelectedFlight : public QDialog
{
    Q_OBJECT

public:
    explicit SelectedFlight(QWidget *parent = nullptr);
    ~SelectedFlight();
    void setClient(QSqlRecord client);
    void setFlight(QSqlRecord flight);

signals:
    void selectedFlightWindow();

private slots:
    void on_cancelButton_clicked();
    void on_moreDetailsButton_clicked();
    void on_nextButton_clicked();

private:
    Ui::SelectedFlight *ui;
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);
    Database* DB;
    QSqlRecord client;
    QSqlRecord flight;
    BuyTicket* ticket;
};

#endif // SELECTEDFLIGHT_H

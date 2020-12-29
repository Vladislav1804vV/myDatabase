#ifndef BUYTICKET_H
#define BUYTICKET_H

#include "database.h"

#include <QDialog>
#include <QSqlRecord>
#include <QSqlRelationalTableModel>
#include <QMessageBox>

namespace Ui {
class BuyTicket;
}

class BuyTicket : public QDialog
{
    Q_OBJECT

public:
    explicit BuyTicket(QWidget *parent = nullptr);
    ~BuyTicket();
    void setFlight(QSqlRecord flight);
    void setClient(QSqlRecord client);

signals:
    void buyTicketWindow();

private slots:
    void on_buyButton_clicked();
    void on_cancelButton_clicked();
    void on_sitComboBox_currentIndexChanged(const QString &arg1);
    void on_amountComboBox_currentIndexChanged(const QString &arg1);
    void on_calculateButton_clicked();

private:
    Ui::BuyTicket *ui;
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);
    Database* DB;
    QSqlRelationalTableModel* modelSit;
    QSqlRelationalTableModel* modelDiscount;
    QSqlRecord flight;
    QSqlRecord client;
    int cost;
};

#endif // BUYTICKET_H

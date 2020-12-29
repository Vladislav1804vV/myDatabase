#include "cabinet.h"
#include "ui_cabinet.h"

Cabinet::Cabinet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Cabinet)
{
    ui->setupUi(this);

    this->setWindowTitle("Личный кабинет");
    this->setWindowFlags (Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);
}

Cabinet::~Cabinet()
{
    delete ui;
}

void Cabinet::setClient(QSqlRecord client)
{
    this->client = client;
}

void Cabinet::on_cancelButton_clicked()
{
    this->close();
}

void Cabinet::closeEvent(QCloseEvent *event)
{
    this->close();
    emit cabinetWindow();

    for(int i = ui->flightsTableWidget->rowCount(); i >= 0; i--) {
        ui->flightsTableWidget->removeRow(i);
    }
    for(int i = ui->baggagesTableWidget->rowCount(); i >= 0; i--) {
        ui->baggagesTableWidget->removeRow(i);
    }
    for(int i = ui->discountsTableWidget->rowCount(); i >= 0; i--) {
        ui->discountsTableWidget->removeRow(i);
    }
}

void Cabinet::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);

    ui->FIOLabel->setText(client.value(1).toString());

    DB = new Database();

    QStringList flights = DB->getFlightsByClient(client.value(1).toString());

    for (int i = 0; i < flights.size(); i++) {
        ui->flightsTableWidget->insertRow(i);
    }

    QTableWidgetItem *item;
    for (int i = 0; i < flights.size(); i++) {
        item = new QTableWidgetItem(DB->getCityByFlight(flights[i], true));
        ui->flightsTableWidget->setItem(i, 0, item);
        item = new QTableWidgetItem(DB->getCityByFlight(flights[i], false));
        ui->flightsTableWidget->setItem(i, 1, item);
        item = new QTableWidgetItem(DB->getPlaneByFlight(flights[i]));
        ui->flightsTableWidget->setItem(i, 2, item);
        item = new QTableWidgetItem(DB->getFlightByNumber(flights[i]).value(4).toDateTime().toString());
        ui->flightsTableWidget->setItem(i, 3, item);
        item = new QTableWidgetItem(DB->getFlightByNumber(flights[i]).value(5).toDateTime().toString());
        ui->flightsTableWidget->setItem(i, 4, item);
    }

    QList<QSqlRecord> baggages = DB->getBaggagesByClient(client.value(1).toString());

    for (int i = 0; i < baggages.size(); i++) {
        ui->baggagesTableWidget->insertRow(i);
    }

    for (int i = 0; i < baggages.size(); i++) {
        item = new QTableWidgetItem(baggages[i].value(0).toString());
        ui->baggagesTableWidget->setItem(i, 0, item);
        item = new QTableWidgetItem(baggages[i].value(1).toString());
        ui->baggagesTableWidget->setItem(i, 1, item);
        item = new QTableWidgetItem(baggages[i].value(2).toString());
        ui->baggagesTableWidget->setItem(i, 2, item);
    }

    QList<QSqlRecord> discounts = DB->getDiscountsByClient(client.value(1).toString());

    for (int i = 0; i < discounts.size(); i++) {
        ui->discountsTableWidget->insertRow(i);
    }

    for (int i = 0; i < discounts.size(); i++) {
        item = new QTableWidgetItem(discounts[i].value(0).toString());
        ui->discountsTableWidget->setItem(i, 0, item);
        item = new QTableWidgetItem(discounts[i].value(1).toString());
        ui->discountsTableWidget->setItem(i, 1, item);
    }

    int cost = 0;
    QStringList costs = DB->getCostTicketsByClient(client.value(1).toString());
    for (int i = 0; i < costs.size(); i++) {
        cost += costs[i].toInt();
    }
    ui->moneyLabel->setText("Потрачено денег: " + QString::number(cost));

    int distance = 0;
    for (int i = 0; i < flights.size(); i++) {
        distance += DB->getFlightByNumber(flights[i]).value(6).toInt();
    }
    ui->distanceLabel->setText("Пройдено расстояние: " + QString::number(distance));
}

#include "selectedflight.h"
#include "ui_selectedflight.h"

SelectedFlight::SelectedFlight(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectedFlight)
{
    ui->setupUi(this);

    this->setWindowTitle("Рейс");
    this->setWindowFlags (Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    ui->kindFlight->setVisible(false);
    ui->typeFlight->setVisible(false);
    ui->statusFlight->setVisible(false);

    ticket = new BuyTicket();
    connect(ticket, &BuyTicket::buyTicketWindow, this, &SelectedFlight::show);
}

SelectedFlight::~SelectedFlight()
{
    delete ui;
}

void SelectedFlight::setClient(QSqlRecord client)
{
    this->client = client;
}

void SelectedFlight::setFlight(QSqlRecord flight)
{
    this->flight = flight;
}

void SelectedFlight::on_cancelButton_clicked()
{
    this->close();
}

void SelectedFlight::on_moreDetailsButton_clicked()
{
    if (ui->kindFlight->isVisible()) {
        ui->kindFlight->setVisible(false);
        ui->typeFlight->setVisible(false);
        ui->statusFlight->setVisible(false);
    } else {
        ui->kindFlight->setVisible(true);
        ui->typeFlight->setVisible(true);
        ui->statusFlight->setVisible(true);
    }
}

void SelectedFlight::on_nextButton_clicked()
{
    hide();
    ticket->setFlight(flight);
    ticket->setClient(client);
    ticket->show();
}

void SelectedFlight::closeEvent(QCloseEvent *event)
{
    this->close();
    emit selectedFlightWindow();

    ui->kindFlight->setVisible(false);
    ui->typeFlight->setVisible(false);
    ui->statusFlight->setVisible(false);
}

void SelectedFlight::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);

    DB = new Database();
    ui->numberFlight->setText(flight.value(0).toString());
    ui->fromLabel->setText("Откуда: " + DB->getCityByFlight(flight.value(0).toString(), true));
    ui->toLabel->setText("Куда: " + DB->getCityByFlight(flight.value(0).toString(), false));
    ui->fromDateLabel->setText("Время отправления: " + flight.value(4).toDateTime().toString());
    ui->toDateLabel->setText("Время прибытия: " + flight.value(5).toDateTime().toString());
    ui->plane->setText("Самолет: " + DB->getPlaneByFlight(flight.value(0).toString()));
    ui->kindFlight->setText("Вид рейса: " + flight.value(1).toString());
    ui->typeFlight->setText("Тип рейса: " + flight.value(2).toString());
    ui->statusFlight->setText("Статус рейса: " + flight.value(3).toString());
}

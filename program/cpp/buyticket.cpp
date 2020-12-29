#include "buyticket.h"
#include "ui_buyticket.h"

BuyTicket::BuyTicket(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BuyTicket)
{
    ui->setupUi(this);

    this->setWindowTitle("Билет");
    this->setWindowFlags (Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    ui->costLabel->setVisible(false);
    ui->buyButton->setVisible(false);
}

BuyTicket::~BuyTicket()
{
    delete ui;
}

void BuyTicket::setFlight(QSqlRecord flight)
{
    this->flight = flight;
}

void BuyTicket::setClient(QSqlRecord client)
{
    this->client = client;
}

void BuyTicket::closeEvent(QCloseEvent *event)
{
    this->close();
    emit buyTicketWindow();
    ui->costLabel->setVisible(false);
    ui->buyButton->setVisible(false);
}

void BuyTicket::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);

    DB = new Database();

    ui->sitComboBox->clear();
    ui->sitComboBox->addItems(DB->getSitsByPlane(DB->getPlaneByFlight(flight.value(0).toString())));

    ui->amountComboBox->clear();
    ui->amountComboBox->addItems(DB->getDiscountsAmount());

    ui->plane->setText(DB->getPlaneByFlight(flight.value(0).toString()));
}

void BuyTicket::on_buyButton_clicked()
{
    on_calculateButton_clicked();
    int baggage_id = DB->createBaggage(ui->weightSpinBox->text(), ui->volumeSpinBox->text(), ui->typeComboBox->currentText());
    int sit_id = DB->getSitIdByNumberAndPlaneId(ui->sitComboBox->currentText(), QString::number(DB->getPlaneIdByModel(DB->getPlaneByFlight(flight.value(0).toString()))));
    int discount_id = DB->getDiscountIdByDescriptionAndAmount(ui->descriptionEdit->text(), ui->amountComboBox->currentText());
    DB->createTicket(QDate::currentDate(), sit_id, discount_id, baggage_id, client.value(0).toInt(), ui->costLabel->text().split(' ')[1].toInt());
    QMessageBox::information(this, "Ура...", "Билет успешно куплен");
    this->close();
}

void BuyTicket::on_cancelButton_clicked()
{
    this->close();
}

void BuyTicket::on_sitComboBox_currentIndexChanged(const QString &arg1)
{
    QSqlRecord sit = DB->getSitByNumber(ui->sitComboBox->currentText());
    ui->classLabel->setText("Класс: " + sit.value(2).toString());
    ui->rowLabel->setText("Ряд: " + sit.value(3).toString());
    ui->costRatioLabel->setText("Коэффициент: " + sit.value(4).toString());
}

void BuyTicket::on_amountComboBox_currentIndexChanged(const QString &arg1)
{
    ui->descriptionEdit->setText(DB->getDescriptionByAmount(ui->amountComboBox->currentText()));
}

void BuyTicket::on_calculateButton_clicked()
{
    cost = 0;

    QString resetStyle("QLineEdit { border: 1px solid black; }");
    QString warningStyle("QLineEdit { border: 2px solid red; }");

    ui->weightSpinBox->setStyleSheet(resetStyle);
    ui->volumeSpinBox->setStyleSheet(resetStyle);

    if (ui->weightSpinBox->text().toInt() <= 0) {
        QMessageBox::warning(this, "Ой...", "Вес должен быть больше 0");
        ui->weightSpinBox->setStyleSheet(warningStyle);
        return;
    }

    if (ui->volumeSpinBox->text().toInt() <= 0) {
        QMessageBox::warning(this, "Ой...", "Объем должен быть больше 0");
        ui->volumeSpinBox->setStyleSheet(warningStyle);
        return;
    }

    ui->buyButton->setVisible(true);

    cost += flight.value(6).toInt() * 3;
    cost *= DB->getSitByNumber(ui->sitComboBox->currentText()).value(4).toDouble();

    cost += 1000;
    if (ui->weightSpinBox->text().toInt() > 20) {
        cost += 500;
    }
    if (ui->volumeSpinBox->text().toInt() > 20000) {
        cost += 2000;
    }

    cost -= cost * ui->amountComboBox->currentText().toDouble() / 100;

    ui->costLabel->setVisible(true);
    ui->costLabel->setText("Стоимость: " + QString::number(cost));
}

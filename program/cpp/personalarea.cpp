#include "personalarea.h"
#include "ui_personalarea.h"

PersonalArea::PersonalArea(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PersonalArea)
{
    ui->setupUi(this);

    this->setWindowTitle("Поиск билета");
    this->setWindowFlags (Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    ui->thereDateEdit->setMinimumDate(QDate::currentDate());
    ui->label->setVisible(false);
    ui->comboBox->setVisible(false);
    ui->chooseButton->setVisible(false);

    selectedFlight = new SelectedFlight();
    connect(selectedFlight, &SelectedFlight::selectedFlightWindow, this, &PersonalArea::show);

    cabinet = new Cabinet();
    connect(cabinet, &Cabinet::cabinetWindow, this, &PersonalArea::show);

}

PersonalArea::~PersonalArea()
{
    delete ui;
}

void PersonalArea::setRecord(QSqlRecord record)
{
    this->record = record;
}

void PersonalArea::closeEvent(QCloseEvent *event)
{
    this->close();
    emit personalAreaWindow();
}

void PersonalArea::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);
    ui->FIOlabel->setText(record.value(1).toString());

    DB = new Database();
    model = new QSqlRelationalTableModel(this, DB->getDB());
    model->setTable("cities");
    model->select();
    ui->fromEdit->setModel(model);
    ui->fromEdit->setModelColumn(1);
    ui->toEdit->setModel(model);
    ui->toEdit->setModelColumn(1);
}

void PersonalArea::on_findTicketButton_clicked()
{
    if (ui->fromEdit->currentText() == ui->toEdit->currentText()) {
        QMessageBox::warning(this, "Ой...", "Выберите разные города");
        return;
    }

    flights.clear();

    QStringList listFlights = DB->getFlightsByCity(ui->toEdit->currentText(), false);
    for (int i = 0; i < listFlights.size(); i++) {
        QStringList listCities = DB->getCitiesByFlight(listFlights[i], true);
        if (listCities.contains(ui->fromEdit->currentText())) {
            flights.append(listFlights[i]);
        }
    }

    for (int i = 0; i < flights.size(); i++) {
        if (!DB->isDateNotLessThan(flights[i], ui->thereDateEdit->date())) {
            flights.removeAt(i);
        }
    }

    ui->comboBox->clear();

    ui->label->setText("Найдено: " + QString::number(flights.size()));
    for (int i = 0; i < flights.size(); i++) {
        ui->comboBox->addItem(QString::number(i + 1));
    }

    ui->label->setVisible(true);
    if (flights.size()) {
        ui->comboBox->setVisible(true);
        ui->chooseButton->setVisible(true);
    } else {
        ui->comboBox->setVisible(false);
        ui->chooseButton->setVisible(false);
    }

}

void PersonalArea::on_chooseButton_clicked()
{
    hide();
    selectedFlight->setClient(record);
    selectedFlight->setFlight(DB->getFlightByNumber(flights[ui->comboBox->currentIndex()]));
    selectedFlight->show();
    ui->label->setVisible(false);
    ui->comboBox->setVisible(false);
    ui->chooseButton->setVisible(false);
}

void PersonalArea::on_cabinetButton_clicked()
{
    hide();
    cabinet->setClient(record);
    cabinet->show();
}

#include "airportseditform.h"
#include "ui_airportseditform.h"

AirportsEditForm::AirportsEditForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AirportsEditForm)
{
    ui->setupUi(this);

    this->setWindowTitle("Запись");
    this->setWindowFlags (Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

AirportsEditForm::~AirportsEditForm()
{
    delete ui;
}

void AirportsEditForm::setModel(QAbstractItemModel *model)
{
    mapper->setModel(model);
    mapper->addMapping(ui->code, 0);
    mapper->addMapping(ui->name, 1);
    mapper->addMapping(ui->type, 2);
    mapper->addMapping(ui->cityName, 3);
}

void AirportsEditForm::setMapCities(QMap<QString, QString> mapCities)
{
    this->mapCities = mapCities;
    QString indexText = ui->cityName->currentText();
    ui->cityName->clear();
    ui->cityName->addItems(mapCities.values());
    ui->cityName->setCurrentText(indexText);
}

void AirportsEditForm::on_acceptButton_clicked()
{
    for (int i = 0; i < ui->cityName->count(); i++) {
        ui->cityName->setItemText(i, mapCities.key(ui->cityName->itemText(i)));
    }
    mapper->submit();
    for (int i = 0; i < ui->cityName->count(); i++) {
        ui->cityName->setItemText(i, mapCities.value(ui->cityName->itemText(i)));
    }
    this->close();
}

void AirportsEditForm::on_cancelButton_clicked()
{
    this->close();
}

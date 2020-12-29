#include "citieseditform.h"
#include "ui_citieseditform.h"

CitiesEditForm::CitiesEditForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CitiesEditForm)
{
    ui->setupUi(this);

    this->setWindowTitle("Запись");
    this->setWindowFlags (Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

CitiesEditForm::~CitiesEditForm()
{
    delete ui;
}

void CitiesEditForm::setModel(QAbstractItemModel *model)
{
    mapper->setModel(model);
    mapper->addMapping(ui->name, 1);
    mapper->addMapping(ui->countryName, 2);
}

void CitiesEditForm::setMapCountries(QMap<QString, QString> mapCountries)
{
    this->mapCountries = mapCountries;
    QString indexText = ui->countryName->currentText();
    ui->countryName->clear();
    ui->countryName->addItems(mapCountries.values());
    ui->countryName->setCurrentText(indexText);
}

void CitiesEditForm::on_acceptButton_clicked()
{
    for (int i = 0; i < ui->countryName->count(); i++) {
        ui->countryName->setItemText(i, mapCountries.key(ui->countryName->itemText(i)));
    }
    mapper->submit();
    for (int i = 0; i < ui->countryName->count(); i++) {
        ui->countryName->setItemText(i, mapCountries.value(ui->countryName->itemText(i)));
    }
    this->close();
}

void CitiesEditForm::on_cancelButton_clicked()
{
    this->close();
}

#include "gateseditform.h"
#include "ui_gateseditform.h"

GatesEditForm::GatesEditForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GatesEditForm)
{
    ui->setupUi(this);

    this->setWindowTitle("Запись");
    this->setWindowFlags (Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

GatesEditForm::~GatesEditForm()
{
    delete ui;
}

void GatesEditForm::setModel(QAbstractItemModel *model)
{
    mapper->setModel(model);
    mapper->addMapping(ui->number, 1);
    mapper->addMapping(ui->type, 2);
    mapper->addMapping(ui->airportName, 3);
}

void GatesEditForm::setMapAirports(QMap<QString, QString> mapAirports)
{
    this->mapAirports = mapAirports;
    QString indexText = ui->airportName->currentText();
    ui->airportName->clear();
    ui->airportName->addItems(mapAirports.values());
    ui->airportName->setCurrentText(indexText);
}

void GatesEditForm::on_acceptButton_clicked()
{
    for (int i = 0; i < ui->airportName->count(); i++) {
        ui->airportName->setItemText(i, mapAirports.key(ui->airportName->itemText(i)));
    }
    mapper->submit();
    for (int i = 0; i < ui->airportName->count(); i++) {
        ui->airportName->setItemText(i, mapAirports.value(ui->airportName->itemText(i)));
    }
    this->close();
}

void GatesEditForm::on_cancelButton_clicked()
{
    this->close();
}

#include "flightseditform.h"
#include "ui_flightseditform.h"

FlightsEditForm::FlightsEditForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FlightsEditForm)
{
    ui->setupUi(this);

    this->setWindowTitle("Запись");
    this->setWindowFlags (Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

FlightsEditForm::~FlightsEditForm()
{
    delete ui;
}

void FlightsEditForm::setModel(QAbstractItemModel *model)
{
    mapper->setModel(model);
    mapper->addMapping(ui->number, 0);
    mapper->addMapping(ui->kind, 1);
    mapper->addMapping(ui->type, 2);
    mapper->addMapping(ui->status, 3);
    mapper->addMapping(ui->arrivalDate, 4);
    mapper->addMapping(ui->departureDate, 5);
    mapper->addMapping(ui->distance, 6);
    mapper->addMapping(ui->gateInNumber, 7);
    mapper->addMapping(ui->gateOutNumber, 8);
    mapper->addMapping(ui->planeModel, 9);
}

void FlightsEditForm::setMapGatesIn(QMap<QString, QString> mapGatesIn)
{
    this->mapGatesIn = mapGatesIn;
    QString indexText = ui->gateInNumber->currentText();
    ui->gateInNumber->clear();
    ui->gateInNumber->addItems(mapGatesIn.values());
    ui->gateInNumber->setCurrentText(indexText);
}

void FlightsEditForm::setMapGatesOut(QMap<QString, QString> mapGatesOut)
{
    this->mapGatesOut = mapGatesOut;
    QString indexText = ui->gateOutNumber->currentText();
    ui->gateOutNumber->clear();
    ui->gateOutNumber->addItems(mapGatesOut.values());
    ui->gateOutNumber->setCurrentText(indexText);
}

void FlightsEditForm::setMapPlanes(QMap<QString, QString> mapPlanes)
{
    this->mapPlanes = mapPlanes;
    QString indexText = ui->planeModel->currentText();
    ui->planeModel->clear();
    ui->planeModel->addItems(mapPlanes.values());
    ui->planeModel->setCurrentText(indexText);
}

void FlightsEditForm::on_acceptButton_clicked()
{
    for (int i = 0; i < ui->gateInNumber->count(); i++) {
        ui->gateInNumber->setItemText(i, mapGatesIn.key(ui->gateInNumber->itemText(i)));
    }
    for (int i = 0; i < ui->gateOutNumber->count(); i++) {
        ui->gateOutNumber->setItemText(i, mapGatesOut.key(ui->gateOutNumber->itemText(i)));
    }
    for (int i = 0; i < ui->planeModel->count(); i++) {
        ui->planeModel->setItemText(i, mapPlanes.key(ui->planeModel->itemText(i)));
    }
    mapper->submit();
    for (int i = 0; i < ui->gateInNumber->count(); i++) {
        ui->gateInNumber->setItemText(i, mapGatesIn.value(ui->gateInNumber->itemText(i)));
    }
    for (int i = 0; i < ui->gateOutNumber->count(); i++) {
        ui->gateOutNumber->setItemText(i, mapGatesOut.value(ui->gateOutNumber->itemText(i)));
    }
    for (int i = 0; i < ui->planeModel->count(); i++) {
        ui->planeModel->setItemText(i, mapPlanes.value(ui->planeModel->itemText(i)));
    }
    this->close();
}

void FlightsEditForm::on_cancelButton_clicked()
{
    this->close();
}

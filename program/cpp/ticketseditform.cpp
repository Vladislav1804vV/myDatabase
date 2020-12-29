#include "ticketseditform.h"
#include "ui_ticketseditform.h"

TicketsEditForm::TicketsEditForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TicketsEditForm)
{
    ui->setupUi(this);

    this->setWindowTitle("Запись");
    this->setWindowFlags (Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

TicketsEditForm::~TicketsEditForm()
{
    delete ui;
}

void TicketsEditForm::setModel(QAbstractItemModel *model)
{
    mapper->setModel(model);
    mapper->addMapping(ui->purchaseDate, 1);
    mapper->addMapping(ui->sitNumber, 2);
    mapper->addMapping(ui->salesName, 3);
    mapper->addMapping(ui->baggageWeight, 4);
    mapper->addMapping(ui->clientFIO, 5);
    mapper->addMapping(ui-> cost, 6);
}

void TicketsEditForm::setMapSits(QMap<QString, QString> mapSits)
{
    this->mapSits = mapSits;
    QString indexText = ui->sitNumber->currentText();
    ui->sitNumber->clear();
    ui->sitNumber->addItems(mapSits.values());
    ui->sitNumber->setCurrentText(indexText);
}

void TicketsEditForm::setMapDiscounts(QMap<QString, QString> mapDiscounts)
{
    this->mapDiscounts = mapDiscounts;
    QString indexText = ui->salesName->currentText();
    ui->salesName->clear();
    ui->salesName->addItems(mapDiscounts.values());
    ui->salesName->setCurrentText(indexText);
}

void TicketsEditForm::setMapBaggages(QMap<QString, QString> mapBaggages)
{
    this->mapBaggages = mapBaggages;
    QString indexText = ui->baggageWeight->currentText();
    ui->baggageWeight->clear();
    ui->baggageWeight->addItems(mapBaggages.values());
    ui->baggageWeight->setCurrentText(indexText);
}

void TicketsEditForm::setMapClients(QMap<QString, QString> mapClients)
{
    this->mapClients = mapClients;
    QString indexText = ui->clientFIO->currentText();
    ui->clientFIO->clear();
    ui->clientFIO->addItems(mapClients.values());
    ui->clientFIO->setCurrentText(indexText);
}

void TicketsEditForm::on_acceptButton_clicked()
{
    for (int i = 0; i < ui->sitNumber->count(); i++) {
        ui->sitNumber->setItemText(i, mapSits.key(ui->sitNumber->itemText(i)));
    }
    for (int i = 0; i < ui->salesName->count(); i++) {
        ui->salesName->setItemText(i, mapDiscounts.key(ui->salesName->itemText(i)));
    }
    for (int i = 0; i < ui->baggageWeight->count(); i++) {
        ui->baggageWeight->setItemText(i, mapBaggages.key(ui->baggageWeight->itemText(i)));
    }
    for (int i = 0; i < ui->clientFIO->count(); i++) {
        ui->clientFIO->setItemText(i, mapClients.key(ui->clientFIO->itemText(i)));
    }
    mapper->submit();
    for (int i = 0; i < ui->sitNumber->count(); i++) {
        ui->sitNumber->setItemText(i, mapSits.value(ui->sitNumber->itemText(i)));
    }
    for (int i = 0; i < ui->salesName->count(); i++) {
        ui->salesName->setItemText(i, mapDiscounts.value(ui->salesName->itemText(i)));
    }
    for (int i = 0; i < ui->baggageWeight->count(); i++) {
        ui->baggageWeight->setItemText(i, mapBaggages.value(ui->baggageWeight->itemText(i)));
    }
    for (int i = 0; i < ui->clientFIO->count(); i++) {
        ui->clientFIO->setItemText(i, mapClients.value(ui->clientFIO->itemText(i)));
    }
    this->close();
}

void TicketsEditForm::on_cancelButton_clicked()
{
    this->close();
}

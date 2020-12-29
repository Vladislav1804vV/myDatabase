#include "clientseditform.h"
#include "ui_clientseditform.h"

ClientsEditForm::ClientsEditForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientsEditForm)
{
    ui->setupUi(this);

    this->setWindowTitle("Запись");
    this->setWindowFlags (Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

ClientsEditForm::~ClientsEditForm()
{
    delete ui;
}

void ClientsEditForm::setModel(QAbstractItemModel *model)
{
    mapper->setModel(model);
    mapper->addMapping(ui->FIO, 1);
    mapper->addMapping(ui->passportData, 2);
    mapper->addMapping(ui->age, 3);
    mapper->addMapping(ui->gender, 4);
    mapper->addMapping(ui->account, 5);
}

void ClientsEditForm::on_acceptButton_clicked()
{
    mapper->submit();
    this->close();
}

void ClientsEditForm::on_cancelButton_clicked()
{
    this->close();
}

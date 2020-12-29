#include "baggageseditform.h"
#include "ui_baggageseditform.h"

BaggagesEditForm::BaggagesEditForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BaggagesEditForm)
{
    ui->setupUi(this);

    this->setWindowTitle("Запись");
    this->setWindowFlags (Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

BaggagesEditForm::~BaggagesEditForm()
{
    delete ui;
}

void BaggagesEditForm::setModel(QAbstractItemModel *model)
{
    mapper->setModel(model);
    mapper->addMapping(ui->weight, 1);
    mapper->addMapping(ui->volume, 2);
    mapper->addMapping(ui->type, 3);
}

void BaggagesEditForm::on_acceptButton_clicked()
{
    mapper->submit();
    this->close();
}

void BaggagesEditForm::on_cancelButton_clicked()
{
   this->close();
}

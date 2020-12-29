#include "countrieseditform.h"
#include "ui_countrieseditform.h"

CountriesEditForm::CountriesEditForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CountriesEditForm)
{
    ui->setupUi(this);

    this->setWindowTitle("Запись");
    this->setWindowFlags (Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

CountriesEditForm::~CountriesEditForm()
{
    delete ui;
}

void CountriesEditForm::setModel(QAbstractItemModel *model)
{
    mapper->setModel(model);
    mapper->addMapping(ui->name, 1);
}

void CountriesEditForm::on_acceptButton_clicked()
{
    mapper->submit();
    this->close();
}

void CountriesEditForm::on_cancelButton_clicked()
{
    this->close();
}

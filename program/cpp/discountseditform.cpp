#include "discountseditform.h"
#include "ui_discountseditform.h"

DiscountsEditForm::DiscountsEditForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DiscountsEditForm)
{
    ui->setupUi(this);

    this->setWindowTitle("Запись");
    this->setWindowFlags (Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

DiscountsEditForm::~DiscountsEditForm()
{
    delete ui;
}

void DiscountsEditForm::setModel(QAbstractItemModel *model)
{
    mapper->setModel(model);
    mapper->addMapping(ui->discountCode, 0);
    mapper->addMapping(ui->name, 1);
    mapper->addMapping(ui->discription, 2);
    mapper->addMapping(ui->amount, 3);
}

void DiscountsEditForm::on_acceptButton_clicked()
{
    mapper->submit();
    this->close();
}

void DiscountsEditForm::on_cancelButton_clicked()
{
    this->close();
}

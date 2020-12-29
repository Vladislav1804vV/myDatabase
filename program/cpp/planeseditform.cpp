#include "planeseditform.h"
#include "ui_planeseditform.h"

PlanesEditForm::PlanesEditForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlanesEditForm)
{
    ui->setupUi(this);

    this->setWindowTitle("Запись");
    this->setWindowFlags (Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

PlanesEditForm::~PlanesEditForm()
{
    delete ui;
}

void PlanesEditForm::setModel(QAbstractItemModel *model)
{
    mapper->setModel(model);
    mapper->addMapping(ui->model, 1);
    mapper->addMapping(ui->tailNumber, 2);
}

void PlanesEditForm::on_acceptButton_clicked()
{
    mapper->submit();
    this->close();
}

void PlanesEditForm::on_cancelButton_clicked()
{
    this->close();
}

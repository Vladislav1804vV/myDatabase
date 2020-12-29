#include "sitseditform.h"
#include "ui_sitseditform.h"

SitsEditForm::SitsEditForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SitsEditForm)
{
    ui->setupUi(this);

    this->setWindowTitle("Запись");
    this->setWindowFlags (Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
}

SitsEditForm::~SitsEditForm()
{
    delete ui;
}

void SitsEditForm::setModel(QAbstractItemModel *model)
{
    mapper->setModel(model);
    mapper->addMapping(ui->number, 1);
    mapper->addMapping(ui->class_2, 2);
    mapper->addMapping(ui->row, 3);
    mapper->addMapping(ui->costRatio, 4);
    mapper->addMapping(ui->planeModel, 5);
}

void SitsEditForm::setMapPlanes(QMap<QString, QString> mapPlanes)
{
    this->mapPlanes = mapPlanes;
    QString indexText = ui->planeModel->currentText();
    ui->planeModel->clear();
    ui->planeModel->addItems(mapPlanes.values());
    ui->planeModel->setCurrentText(indexText);
}

void SitsEditForm::on_acceptButton_clicked()
{
    for (int i = 0; i < ui->planeModel->count(); i++) {
        ui->planeModel->setItemText(i, mapPlanes.key(ui->planeModel->itemText(i)));
    }
    mapper->submit();
    for (int i = 0; i < ui->planeModel->count(); i++) {
        ui->planeModel->setItemText(i, mapPlanes.value(ui->planeModel->itemText(i)));
    }
    this->close();
}

void SitsEditForm::on_cancelButton_clicked()
{
    this->close();
}

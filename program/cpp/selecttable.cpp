#include "selecttable.h"
#include "ui_selecttable.h"

SelectTable::SelectTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectTable)
{
    ui->setupUi(this);

    this->setWindowTitle("Выбрать таблицу");
    this->setWindowFlags (Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

}

SelectTable::~SelectTable()
{
    delete ui;
}

void SelectTable::closeEvent(QCloseEvent *event)
{
    this->close();
    emit selectTableWindow();
}

void SelectTable::on_airportsButton_clicked()
{
    hide();
    table = new Table("airports");
    connect(table, &Table::tableWindow, this, &SelectTable::show);
    table->show();
}

void SelectTable::on_baggagesButton_clicked()
{
    hide();
    table = new Table("baggages");
    connect(table, &Table::tableWindow, this, &SelectTable::show);
    table->show();
}

void SelectTable::on_citiesButton_clicked()
{
    hide();
    table = new Table("cities");
    connect(table, &Table::tableWindow, this, &SelectTable::show);
    table->show();
}

void SelectTable::on_clientsButton_clicked()
{
    hide();
    table = new Table("clients");
    connect(table, &Table::tableWindow, this, &SelectTable::show);
    table->show();
}

void SelectTable::on_countriesButton_clicked()
{
    hide();
    table = new Table("countries");
    connect(table, &Table::tableWindow, this, &SelectTable::show);
    table->show();
}

void SelectTable::on_discountsButton_clicked()
{
    hide();
    table = new Table("discounts");
    connect(table, &Table::tableWindow, this, &SelectTable::show);
    table->show();
}

void SelectTable::on_flightsButton_clicked()
{
    hide();
    table = new Table("flights");
    connect(table, &Table::tableWindow, this, &SelectTable::show);
    table->show();
}

void SelectTable::on_gatesButton_clicked()
{
    hide();
    table = new Table("gates");
    connect(table, &Table::tableWindow, this, &SelectTable::show);
    table->show();
}

void SelectTable::on_planesButton_clicked()
{
    hide();
    table = new Table("planes");
    connect(table, &Table::tableWindow, this, &SelectTable::show);
    table->show();
}

void SelectTable::on_sitsButton_clicked()
{
    hide();
    table = new Table("sits");
    connect(table, &Table::tableWindow, this, &SelectTable::show);
    table->show();
}

void SelectTable::on_ticketsButton_clicked()
{
    hide();
    table = new Table("tickets");
    connect(table, &Table::tableWindow, this, &SelectTable::show);
    table->show();
}

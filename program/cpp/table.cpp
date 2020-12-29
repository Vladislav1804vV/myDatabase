#include "table.h"
#include "ui_table.h"

Table::Table(QString table, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Table)
{
    ui->setupUi(this);

    this->setWindowTitle("Таблица " + table);
    this->setWindowFlags (Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    this->table = table;

    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    DB = new Database();
    model = new QSqlRelationalTableModel(this, DB->getDB());
    model->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
    model->setTable(table);

    if (table == "airports") {
        model->setRelation(model->fieldIndex("city_id"), QSqlRelation("cities", "id", "name"));
        model->setHeaderData(model->fieldIndex("city_id"), Qt::Horizontal, "city_name (FK)");
    }
    if (table == "cities") {
        model->setRelation(model->fieldIndex("country_id"), QSqlRelation("countries", "id", "name"));
        model->setHeaderData(model->fieldIndex("country_id"), Qt::Horizontal, "country_name (FK)");
    }
    if (table == "flights") {
        model->setRelation(model->fieldIndex("gate_id_in"), QSqlRelation("gates", "id", "number"));
        model->setHeaderData(model->fieldIndex("gate_id_in"), Qt::Horizontal, "gate_in_number (FK)");
        model->setRelation(model->fieldIndex("gate_id_out"), QSqlRelation("gates", "id", "number"));
        model->setHeaderData(model->fieldIndex("gate_id_out"), Qt::Horizontal, "gate_in_number (FK)");
        model->setRelation(model->fieldIndex("plane_id"), QSqlRelation("planes", "id", "model"));
        model->setHeaderData(model->fieldIndex("plane_id"), Qt::Horizontal, "plane_model (FK)");
    }
    if (table == "gates") {
        model->setRelation(model->fieldIndex("airport_code"), QSqlRelation("airports", "code", "name"));
        model->setHeaderData(model->fieldIndex("airport_code"), Qt::Horizontal, "airport_name (FK)");
    }
    if (table == "planes") {
        model->setRelation(model->fieldIndex("city_id"), QSqlRelation("cities", "id", "name"));
        model->setHeaderData(model->fieldIndex("city_id"), Qt::Horizontal, "city_name (FK)");
    }
    if (table == "sits") {
        model->setRelation(model->fieldIndex("plane_id"), QSqlRelation("planes", "id", "model"));
        model->setHeaderData(model->fieldIndex("plane_id"), Qt::Horizontal, "plane_model (FK)");
    }
    if (table == "tickets") {
        model->setRelation(model->fieldIndex("sit_id"), QSqlRelation("sits", "id", "number"));
        model->setHeaderData(model->fieldIndex("sit_id"), Qt::Horizontal, "sit_number (FK)");
        model->setRelation(model->fieldIndex("sales_discountCode"), QSqlRelation("discounts", "discountCode", "name"));
        model->setHeaderData(model->fieldIndex("sales_discountCode"), Qt::Horizontal, "sales_name (FK)");
        model->setRelation(model->fieldIndex("baggage_id"), QSqlRelation("baggages", "id", "weight"));
        model->setHeaderData(model->fieldIndex("baggage_id"), Qt::Horizontal, "baggage_weight (FK)");
        model->setRelation(model->fieldIndex("client_id"), QSqlRelation("clients", "id", "FIO"));
        model->setHeaderData(model->fieldIndex("client_id"), Qt::Horizontal, "client_FIO (FK)");
    }

    model->select();
    ui->tableView->setModel(model);

    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));

    citiesForm = new CitiesEditForm(this);
    citiesForm->setModel(model);

    countriesForm = new CountriesEditForm(this);
    countriesForm->setModel(model);

    baggagesForm = new BaggagesEditForm(this);
    baggagesForm->setModel(model);

    clientsForm = new ClientsEditForm(this);
    clientsForm->setModel(model);

    discountsForm = new DiscountsEditForm(this);
    discountsForm->setModel(model);

    flightsForm = new FlightsEditForm(this);
    flightsForm->setModel(model);

    gatesForm = new GatesEditForm(this);
    gatesForm->setModel(model);

    planesForm = new PlanesEditForm(this);
    planesForm->setModel(model);

    sitsForm = new SitsEditForm(this);
    sitsForm->setModel(model);

    ticketsForm = new TicketsEditForm(this);
    ticketsForm->setModel(model);

    airportsForm = new AirportsEditForm(this);
    airportsForm->setModel(model);
}

Table::~Table()
{
    delete ui;
}

void Table::setTable(QString table)
{
    this->table = table;
}

void Table::closeEvent(QCloseEvent *event)
{
    this->close();
    emit tableWindow();
}

void Table::on_saveButton_clicked()
{
    model->submitAll();
}

void Table::on_revertButton_clicked()
{
    model->revertAll();
    model->select();
}

void Table::on_tableView_doubleClicked(const QModelIndex &index)
{
    if (table == "cities") {
        QMap<QString, QString> mapCountries = DB->getTableFromColumns("countries", "id", "name");
        citiesForm->setMapCountries(mapCountries);
        citiesForm->mapper->setCurrentModelIndex(index);
        citiesForm->show();
    }
    if (table == "countries") {
        countriesForm->mapper->setCurrentModelIndex(index);
        countriesForm->show();
    }
    if (table == "baggages") {
        baggagesForm->mapper->setCurrentModelIndex(index);
        baggagesForm->show();
    }
    if (table == "clients") {
        clientsForm->mapper->setCurrentModelIndex(index);
        clientsForm->show();
    }
    if (table == "discounts") {
        discountsForm->mapper->setCurrentModelIndex(index);
        discountsForm->show();
    }
    if (table == "flights") {
        QMap<QString, QString> mapGatesIn = DB->getTableFromColumns("gates", "id", "number");
        flightsForm->setMapGatesIn(mapGatesIn);
        QMap<QString, QString> mapGatesOut = DB->getTableFromColumns("gates", "id", "number");
        flightsForm->setMapGatesOut(mapGatesOut);
        QMap<QString, QString> mapPlanes = DB->getTableFromColumns("planes", "id", "model");
        flightsForm->setMapPlanes(mapPlanes);
        flightsForm->mapper->setCurrentModelIndex(index);
        flightsForm->show();
    }
    if (table == "gates") {
        QMap<QString, QString> mapAirports = DB->getTableFromColumns("airports", "code", "name");
        gatesForm->setMapAirports(mapAirports);
        gatesForm->mapper->setCurrentModelIndex(index);
        gatesForm->show();
    }
    if (table == "planes") {
        planesForm->mapper->setCurrentModelIndex(index);
        planesForm->show();
    }
    if (table == "sits") {
        QMap<QString, QString> mapPlanes = DB->getTableFromColumns("planes", "id", "model");
        sitsForm->setMapPlanes(mapPlanes);
        sitsForm->mapper->setCurrentModelIndex(index);
        sitsForm->show();
    }
    if (table == "tickets") {
        QMap<QString, QString> mapSits = DB->getTableFromColumns("sits", "id", "number");
        ticketsForm->setMapSits(mapSits);
        QMap<QString, QString> mapDiscounts = DB->getTableFromColumns("discounts", "discountCode", "name");
        ticketsForm->setMapDiscounts(mapDiscounts);
        QMap<QString, QString> mapBaggages = DB->getTableFromColumns("baggages", "id", "weight");
        ticketsForm->setMapBaggages(mapBaggages);
        QMap<QString, QString> mapClients = DB->getTableFromColumns("clients", "id", "FIO");
        ticketsForm->setMapClients(mapClients);
        ticketsForm->mapper->setCurrentModelIndex(index);
        ticketsForm->show();
    }
    if (table == "airports") {
        QMap<QString, QString> mapCities = DB->getTableFromColumns("cities", "id", "name");
        airportsForm->setMapCities(mapCities);
        airportsForm->mapper->setCurrentModelIndex(index);
        airportsForm->show();
    }
}

void Table::on_addButton_clicked()
{
    model->insertRow(model->rowCount());
}

void Table::on_deleteButton_clicked()
{
    int selectedRow = ui->tableView->currentIndex().row();
    if (selectedRow >= 0) {
        model->removeRow(selectedRow);
    }
}

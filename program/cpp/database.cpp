#include "database.h"

Database::Database()
{
    DB = QSqlDatabase::addDatabase("QMYSQL");
    DB.setHostName("127.0.0.1");
    DB.setDatabaseName("myairport");
    DB.setUserName("root");
    DB.setPassword("admin");
    if (!DB.open()) {
        qDebug() << DB.lastError().text();
        return;
    } else {
        qDebug() << "Database connected";
    }


//    if (!query.exec("select * from airports")) {
//        qDebug() << query.lastError().databaseText();
//        return;
//    }

//    while (query.next()) {
//        qDebug() << query.record();
//    }
//    model = new QSqlTableModel(this, db);
//    model->setTable("airports");
    //    model->select();
}

QSqlRecord Database::getClient(QString FIO, QString password)
{
    QSqlQuery query = QSqlQuery(DB);
    query.prepare("select * from clients where FIO = :FIO AND account = :password");
    query.bindValue(":FIO", FIO);
    query.bindValue(":password", password);
    query.exec();

    if (!query.isActive()) {
        qDebug() << query.lastError().text();
        return QSqlRecord();
    }

    query.next();
    return query.record();

}

QString Database::getPassword(QString FIO)
{
    QSqlQuery query = QSqlQuery(DB);
    query.prepare("select account from clients where FIO = :FIO");
    query.bindValue(":FIO", FIO);
    query.exec();

    if (!query.isActive()) {
        qDebug() << query.lastError().text();
        return QString();
    }

    query.next();
    return query.record().value(0).toString();
}

bool Database::setClient(Client client)
{
    bool isOk = true;

    QSqlQuery query = QSqlQuery(DB);
    query.prepare("insert into clients (FIO, passportData, age, gender, account) values (:FIO, :passportData, :age, :gender, :account)");
    query.bindValue(":FIO", client.FIO);
    query.bindValue(":passportData", client.passportData);
    query.bindValue(":age", client.age);
    query.bindValue(":gender", QString(client.gender));
    query.bindValue(":account", client.password);
    query.exec();

    if (!query.isActive()) {
        qDebug() << query.lastError().text();
        isOk = false;
    }

    return isOk;
}

QSqlDatabase Database::getDB()
{
    return DB;
}

QMap<QString, QString> Database::getTableFromColumns(QString table, QString column1, QString column2)
{
    QSqlQuery query = QSqlQuery(DB);
    query.exec("select " + column1 + ", " + column2 + " from " + table);

    QMap<QString, QString> map;
    while (query.next()) {
        map.insert(query.value(0).toString(), query.value(1).toString());
    }

    return map;
}

QStringList Database::getFlightsByCity(QString city, bool flag)
{
    QSqlQuery query = QSqlQuery(DB);
    QString gate = "gate_id_out";
    if (flag) {
        gate = "gate_id_in";
    }
    query.prepare("SELECT `flights`.number FROM `cities` INNER JOIN `airports` ON `airports`.city_id = `cities`.id INNER JOIN `gates` ON `gates`.airport_code = `airports`.code INNER JOIN `flights` ON `flights`." + gate + " = `gates`.id WHERE  `cities`.name = :city ;");
    query.bindValue(":city", city);
    query.exec();
    QStringList flights;
    while (query.next()) {
        flights.append(query.value(0).toString());
    }
    return flights;
}

QStringList Database::getCitiesByFlight(QString flight, bool flag)
{
    QSqlQuery query = QSqlQuery(DB);
    QString gate = "gate_id_out";
    if (flag) {
        gate = "gate_id_in";
    }
    query.prepare("SELECT `cities`.name FROM `cities` INNER JOIN `airports` ON `airports`.city_id = `cities`.id INNER JOIN `gates` ON `gates`.airport_code = `airports`.code INNER JOIN `flights` ON `flights`." + gate + " = `gates`.id WHERE `flights`.number = :flight ;");
    query.bindValue(":flight", flight);
    query.exec();
    QStringList cities;
    while (query.next()) {
        cities.append(query.value(0).toString());
    }
    return cities;
}

bool Database::isDateNotLessThan(QString flight, QDate date)
{
    bool isOK = true;

    QString dateString = QString::number(date.year()) + '-' + QString::number(date.month()) + '-' + QString::number(date.day());
    QSqlQuery query = QSqlQuery(DB);
    query.prepare("select * from flights where number = :flight and arrivalDate > :dateStart and arrivalDate < :dateEnd");
    query.bindValue(":flight", flight);
    query.bindValue(":dateStart", dateString + "-0-0");
    query.bindValue(":dateEnd", dateString + "-23-59");
    query.exec();

    query.next();
    if (query.value(0).toString().isEmpty()) {
        isOK = false;
    }

    return isOK;
}

QSqlRecord Database::getFlightByNumber(QString number)
{
    QSqlQuery query = QSqlQuery(DB);
    query.prepare("select * from flights where number = :number");
    query.bindValue(":number", number);
    query.exec();

    query.next();
    return query.record();
}

QString Database::getCityByFlight(QString flight, bool flag)
{
    QSqlQuery query = QSqlQuery(DB);
    QString gate = "gate_id_out";
    if (flag) {
        gate = "gate_id_in";
    }
    query.prepare("SELECT `cities`.name FROM `cities` INNER JOIN `airports` ON `airports`.city_id = `cities`.id INNER JOIN `gates` ON `gates`.airport_code = `airports`.code INNER JOIN `flights` ON `flights`." + gate + " = `gates`.id WHERE `flights`.number = :flight");
    query.bindValue(":flight", flight);
    query.exec();

    query.next();
    return query.value(0).toString();
}

QString Database::getPlaneByFlight(QString flight)
{
    QSqlQuery query = QSqlQuery(DB);
    query.prepare("SELECT `planes`.model FROM `planes` INNER JOIN `flights` ON `flights`.plane_id = `planes`.id WHERE `flights`.number = :flight");
    query.bindValue(":flight", flight);
    query.exec();

    query.next();
    return query.value(0).toString();
}

QStringList Database::getSitsByPlane(QString plane)
{
    QSqlQuery query = QSqlQuery(DB);
    query.prepare("SELECT `sits`.number FROM `sits` INNER JOIN `planes` ON `planes`.id = `sits`.plane_id WHERE `planes`.model = :plane");
    query.bindValue(":plane", plane);
    query.exec();
    QStringList sits;
    while (query.next()) {
        sits.append(query.value(0).toString());
    }
    return sits;
}

QSqlRecord Database::getSitByNumber(QString number)
{
    QSqlQuery query = QSqlQuery(DB);
    query.prepare("select * from sits where number = :number");
    query.bindValue(":number", number);
    query.exec();

    query.next();
    return query.record();
}

QString Database::getDescriptionByAmount(QString amount)
{
    QSqlQuery query = QSqlQuery(DB);
    query.prepare("SELECT `discounts`.description FROM `discounts` WHERE amount = :amount");
    query.bindValue(":amount", amount);
    query.exec();

    query.next();
    return query.value(0).toString();
}

QStringList Database::getDiscountsAmount()
{
    QSqlQuery query = QSqlQuery(DB);
    query.exec("SELECT `discounts`.amount FROM `discounts`");
    QStringList discounts;
    while (query.next()) {
        if (!discounts.contains(query.value(0).toString())) {
            discounts.append(query.value(0).toString());
        }
    }
    return discounts;
}

QStringList Database::getFlightsByClient(QString FIO)
{
    QSqlQuery query = QSqlQuery(DB);
    query.prepare("SELECT `flights`.number FROM `clients` INNER JOIN `tickets` ON `tickets`.client_id = `clients`.id INNER JOIN `sits` ON `sits`.id = `tickets`.sit_id INNER JOIN `planes` ON `planes`.id = `sits`.plane_id INNER JOIN `flights` ON `flights`.plane_id = `planes`.id WHERE `clients`.FIO = :FIO");
    query.bindValue(":FIO", FIO);
    query.exec();

    QStringList flights;
    while (query.next()) {
        flights.append(query.value(0).toString());
    }
    return flights;
}

QList<QSqlRecord> Database::getBaggagesByClient(QString FIO)
{
    QSqlQuery query = QSqlQuery(DB);
    query.prepare("SELECT `baggages`.weight, `baggages`.volume, `baggages`.type FROM `clients` INNER JOIN `tickets` ON `tickets`.client_id = `clients`.id INNER JOIN `baggages` ON `baggages`.id = `tickets`.baggage_id WHERE `clients`.FIO = :FIO");
    query.bindValue(":FIO", FIO);
    query.exec();

    QList<QSqlRecord> baggages;
    while (query.next()) {
        baggages.append(query.record());
    }
    return baggages;
}

QList<QSqlRecord> Database::getDiscountsByClient(QString FIO)
{
    QSqlQuery query = QSqlQuery(DB);
    query.prepare("SELECT `discounts`.name, `discounts`.description FROM `clients` INNER JOIN `tickets` ON `tickets`.client_id = `clients`.id INNER JOIN `discounts` ON `discounts`.discountCode = `tickets`.sales_discountCode WHERE `clients`.FIO = :FIO");
    query.bindValue(":FIO", FIO);
    query.exec();

    QList<QSqlRecord> discounts;
    while (query.next()) {
        discounts.append(query.record());
    }
    return discounts;
}

QStringList Database::getCostTicketsByClient(QString FIO)
{
    QSqlQuery query = QSqlQuery(DB);
    query.prepare("SELECT `tickets`.cost FROM `clients` INNER JOIN `tickets` ON `tickets`.client_id = `clients`.id WHERE `clients`.FIO = :FIO");
    query.bindValue(":FIO", FIO);
    query.exec();

    QStringList costs;
    while (query.next()) {
        costs.append(query.value(0).toString());
    }
    return costs;
}

int Database::createBaggage(QString weight, QString volume, QString type)
{
    QSqlQuery query = QSqlQuery(DB);
    query.prepare("INSERT INTO `myairport`.`baggages` (`weight`, `volume`, `type`) VALUES (:weight, :volume, :type)");
    query.bindValue(":weight", weight);
    query.bindValue(":volume", volume);
    query.bindValue(":type", type);
    query.exec();

    return query.lastInsertId().toInt();
}

int Database::getDiscountIdByDescriptionAndAmount(QString description, QString amount)
{
    QSqlQuery query = QSqlQuery(DB);
    query.prepare("SELECT `discounts`.discountCode FROM `discounts` WHERE `discounts`.description = :description and `discounts`.amount = :amount");
    query.bindValue(":description", description);
    query.bindValue(":amount", amount);
    query.exec();

    query.next();
    return query.value(0).toInt();
}

int Database::getSitIdByNumberAndPlaneId(QString number, QString planeId)
{
    QSqlQuery query = QSqlQuery(DB);
    query.prepare("SELECT `sits`.id FROM `sits` WHERE `sits`.number = :number and `sits`.plane_id = :planeId");
    query.bindValue(":number", number);
    query.bindValue(":planeId", planeId);
    query.exec();

    query.next();
    return query.value(0).toInt();
}

int Database::getPlaneIdByModel(QString model)
{
    QSqlQuery query = QSqlQuery(DB);
    query.prepare("SELECT `planes`.id FROM `planes` WHERE `planes`.model = :model");
    query.bindValue(":model", model);
    query.exec();

    query.next();
    return query.value(0).toInt();
}

void Database::createTicket(QDate purchaseDate, int sit_id, int sales_discountCode, int baggage_id, int client_id, int cost)
{
    QSqlQuery query = QSqlQuery(DB);
    query.prepare("INSERT INTO `myairport`.`tickets` (`purchaseDate`, `sit_id`, `sales_discountCode`, `baggage_id`, `client_id`, `cost`) VALUES (:purchaseDate, :sit_id, :sales_discountCode, :baggage_id, :client_id, :cost);");
    query.bindValue(":purchaseDate", purchaseDate);
    query.bindValue(":sit_id", sit_id);
    query.bindValue(":sales_discountCode", sales_discountCode);
    query.bindValue(":baggage_id", baggage_id);
    query.bindValue(":client_id", client_id);
    query.bindValue(":cost", cost);
    query.exec();
}

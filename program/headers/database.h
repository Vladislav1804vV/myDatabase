#ifndef DATABASE_H
#define DATABASE_H

#include "Client.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QMap>
#include <QDate>
#include <QList>

class Database
{
public:
    Database();
    QSqlRecord getClient(QString FIO, QString password);
    QString getPassword(QString FIO);
    bool setClient(Client client);
    QSqlDatabase getDB();
    QMap<QString, QString> getTableFromColumns(QString table, QString column1, QString column2);
    QStringList getFlightsByCity(QString city, bool flag);
    QStringList getCitiesByFlight(QString flight, bool flag);
    bool isDateNotLessThan(QString flight, QDate date);
    QSqlRecord getFlightByNumber(QString number);
    QString getCityByFlight(QString flight, bool flag);
    QString getPlaneByFlight(QString flight);
    QStringList getSitsByPlane(QString plane);
    QSqlRecord getSitByNumber(QString number);
    QString getDescriptionByAmount(QString amount);
    QStringList getDiscountsAmount();
    QStringList getFlightsByClient(QString FIO);
    QList<QSqlRecord> getBaggagesByClient(QString FIO);
    QList<QSqlRecord> getDiscountsByClient(QString FIO);
    QStringList getCostTicketsByClient(QString FIO);
    int createBaggage(QString weight, QString volume, QString type);
    int getDiscountIdByDescriptionAndAmount(QString description, QString amount);
    int getSitIdByNumberAndPlaneId(QString number, QString planeId);
    int getPlaneIdByModel(QString model);
    void createTicket(QDate purchaseDate, int sit_id, int sales_discountCode, int baggage_id, int client_id, int cost);

private:
    QSqlDatabase DB;
};

#endif // DATABASE_H

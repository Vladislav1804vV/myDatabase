#ifndef CLIENT_H
#define CLIENT_H

#include <QString>

struct Client {
    QString FIO;
    QString passportData;
    int age;
    QChar gender;
    QString password;
};

#endif // CLIENT_H

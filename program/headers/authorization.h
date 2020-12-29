#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include "database.h"
#include "personalarea.h"
#include "getpassword.h"
#include "registration.h"

#include <QDialog>
#include <QMessageBox>
#include <QDataWidgetMapper>
#include <QSqlQuery>
#include <QSqlField>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

namespace Ui {
class Authorization;
}

class GetPassword;
class Authorization : public QDialog
{
    Q_OBJECT

public:
    explicit Authorization(QWidget *parent = nullptr);
    ~Authorization();

signals:
    void authorizationWindow();

private slots:
    void on_entryButton_clicked();
    void on_forgotButton_clicked();
    void on_registrationButton_clicked();

private:
    Ui::Authorization *ui;
    void closeEvent(QCloseEvent *event);
    PersonalArea* personalArea;
    GetPassword* password;
    Registration* registration;

};

#endif // AUTHORIZATION_H

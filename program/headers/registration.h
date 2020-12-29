#ifndef REGISTRATION_H
#define REGISTRATION_H

#include "Client.h"
#include "database.h"

#include <QDialog>
#include <QMessageBox>
#include <QList>

namespace Ui {
class Registration;
}

class Registration : public QDialog
{
    Q_OBJECT

public:
    explicit Registration(QString login, QWidget *parent = nullptr);
    ~Registration();
    QString getLogin();
    QString getPassword();
    void setLogin(QString login);

signals:
    void registrationWindow();

private slots:
    void on_isPatronymicCheckBox_stateChanged();
    void on_acceptButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::Registration *ui;
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent* event);
    QString login;
    QString password;
};

#endif // REGISTRATION_H

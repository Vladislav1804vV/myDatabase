#ifndef GETPASSWORD_H
#define GETPASSWORD_H

#include "database.h"
#include "authorization.h"

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class GetPassword;
}

class GetPassword : public QDialog
{
    Q_OBJECT

public:
    explicit GetPassword(QString login, QWidget *parent = nullptr);
    ~GetPassword();
    QString getLogin();
    QString getPassword();
    void setLogin(QString login);

signals:
    void passwordWindow();

private slots:
    void on_getPasswordButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::GetPassword *ui;
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);
    QString login;
    QString password;
};

#endif // GETPASSWORD_H

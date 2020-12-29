#ifndef AUTHORIZATIONDB_H
#define AUTHORIZATIONDB_H

#include "selecttable.h"

#include <QDialog>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QMessageBox>

namespace Ui {
class AuthorizationDB;
}

class AuthorizationDB : public QDialog
{
    Q_OBJECT

public:
    explicit AuthorizationDB(QWidget *parent = nullptr);
    ~AuthorizationDB();

signals:
    void authorizationDBWindow();

private slots:
    void on_entryButton_clicked();

private:
    Ui::AuthorizationDB *ui;
    void closeEvent(QCloseEvent *event);
    SelectTable* selectTable;
};

#endif // AUTHORIZATIONDB_H

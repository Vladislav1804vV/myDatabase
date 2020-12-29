#ifndef CABINET_H
#define CABINET_H

#include "database.h"

#include <QDialog>
#include <QSqlRecord>
#include <QTableWidgetItem>
#include <QList>

namespace Ui {
class Cabinet;
}

class Cabinet : public QDialog
{
    Q_OBJECT

public:
    explicit Cabinet(QWidget *parent = nullptr);
    ~Cabinet();
    void setClient(QSqlRecord client);

signals:
    void cabinetWindow();

private slots:
    void on_cancelButton_clicked();

private:
    Ui::Cabinet *ui;
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);
    Database* DB;
    QSqlRecord client;
};

#endif // CABINET_H

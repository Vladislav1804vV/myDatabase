#ifndef PERSONALAREA_H
#define PERSONALAREA_H

#include "database.h"
#include "selectedflight.h"
#include "cabinet.h"

#include <QDialog>
#include <QSqlRecord>
#include <QDate>
#include <QMessageBox>
#include <QSqlRelationalTableModel>
#include <QMap>

namespace Ui {
class PersonalArea;
}

class PersonalArea : public QDialog
{
    Q_OBJECT

public:
    explicit PersonalArea(QWidget *parent = nullptr);
    ~PersonalArea();
    void setRecord(QSqlRecord record);

signals:
    void personalAreaWindow();

private slots:
    void on_findTicketButton_clicked();
    void on_chooseButton_clicked();

    void on_cabinetButton_clicked();

private:
    Ui::PersonalArea *ui;
    void closeEvent(QCloseEvent *event);
    void showEvent(QShowEvent *event);
    QSqlRecord record;
    Database* DB;
    QSqlRelationalTableModel* model;
    QStringList flights;
    SelectedFlight* selectedFlight;
    Cabinet* cabinet;

};

#endif // PERSONALAREA_H

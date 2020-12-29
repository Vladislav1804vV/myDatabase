#ifndef CITIESEDITFORM_H
#define CITIESEDITFORM_H

#include "database.h"

#include <QDialog>
#include <QDataWidgetMapper>
#include <QMap>

namespace Ui {
class CitiesEditForm;
}

class CitiesEditForm : public QDialog
{
    Q_OBJECT

public:
    explicit CitiesEditForm(QWidget *parent = nullptr);
    ~CitiesEditForm();
    void setModel(QAbstractItemModel* model);
    QDataWidgetMapper* mapper;
    void setMapCountries(QMap<QString, QString> mapCountries);

private slots:
    void on_acceptButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::CitiesEditForm *ui;
    QMap<QString, QString> mapCountries;
};

#endif // CITIESEDITFORM_H

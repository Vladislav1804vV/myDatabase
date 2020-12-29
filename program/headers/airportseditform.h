#ifndef AIRPORTSEDITFORM_H
#define AIRPORTSEDITFORM_H

#include <QDialog>
#include <QDataWidgetMapper>
#include <QMap>

namespace Ui {
class AirportsEditForm;
}

class AirportsEditForm : public QDialog
{
    Q_OBJECT

public:
    explicit AirportsEditForm(QWidget *parent = nullptr);
    ~AirportsEditForm();
    void setModel(QAbstractItemModel* model);
    QDataWidgetMapper* mapper;
    void setMapCities(QMap<QString, QString> mapCities);

private slots:
    void on_acceptButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::AirportsEditForm *ui;
    QMap<QString, QString> mapCities;
};

#endif // AIRPORTSEDITFORM_H

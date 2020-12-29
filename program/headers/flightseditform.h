#ifndef FLIGHTSEDITFORM_H
#define FLIGHTSEDITFORM_H

#include <QDialog>
#include <QDataWidgetMapper>
#include <QMap>

namespace Ui {
class FlightsEditForm;
}

class FlightsEditForm : public QDialog
{
    Q_OBJECT

public:
    explicit FlightsEditForm(QWidget *parent = nullptr);
    ~FlightsEditForm();
    void setModel(QAbstractItemModel* model);
    QDataWidgetMapper* mapper;
    void setMapGatesIn(QMap<QString, QString> mapGatesIn);
    void setMapGatesOut(QMap<QString, QString> mapGatesOut);
    void setMapPlanes(QMap<QString, QString> mapPlanes);

private slots:
    void on_acceptButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::FlightsEditForm *ui;
    QMap<QString, QString> mapGatesIn;
    QMap<QString, QString> mapGatesOut;
    QMap<QString, QString> mapPlanes;
};

#endif // FLIGHTSEDITFORM_H

#ifndef GATESEDITFORM_H
#define GATESEDITFORM_H

#include <QDialog>
#include <QDataWidgetMapper>
#include <QMap>

namespace Ui {
class GatesEditForm;
}

class GatesEditForm : public QDialog
{
    Q_OBJECT

public:
    explicit GatesEditForm(QWidget *parent = nullptr);
    ~GatesEditForm();
    void setModel(QAbstractItemModel* model);
    QDataWidgetMapper* mapper;
    void setMapAirports(QMap<QString, QString> mapAirports);

private slots:
    void on_acceptButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::GatesEditForm *ui;
    QMap<QString, QString> mapAirports;
};

#endif // GATESEDITFORM_H

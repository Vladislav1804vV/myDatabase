#ifndef TICKETSEDITFORM_H
#define TICKETSEDITFORM_H

#include <QDialog>
#include <QDataWidgetMapper>
#include <QMap>

namespace Ui {
class TicketsEditForm;
}

class TicketsEditForm : public QDialog
{
    Q_OBJECT

public:
    explicit TicketsEditForm(QWidget *parent = nullptr);
    ~TicketsEditForm();
    void setModel(QAbstractItemModel* model);
    QDataWidgetMapper* mapper;
    void setMapSits(QMap<QString, QString> mapSits);
    void setMapDiscounts(QMap<QString, QString> mapDiscounts);
    void setMapBaggages(QMap<QString, QString> mapBaggages);
    void setMapClients(QMap<QString, QString> mapClients);

private slots:
    void on_acceptButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::TicketsEditForm *ui;
    QMap<QString, QString> mapSits;
    QMap<QString, QString> mapDiscounts;
    QMap<QString, QString> mapBaggages;
    QMap<QString, QString> mapClients;
};

#endif // TICKETSEDITFORM_H

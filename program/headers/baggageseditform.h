#ifndef BAGGAGESEDITFORM_H
#define BAGGAGESEDITFORM_H

#include <QDialog>
#include <QDataWidgetMapper>

namespace Ui {
class BaggagesEditForm;
}

class BaggagesEditForm : public QDialog
{
    Q_OBJECT

public:
    explicit BaggagesEditForm(QWidget *parent = nullptr);
    ~BaggagesEditForm();
    void setModel(QAbstractItemModel* model);
    QDataWidgetMapper* mapper;

private slots:
    void on_acceptButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::BaggagesEditForm *ui;
};

#endif // BAGGAGESEDITFORM_H

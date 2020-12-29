#ifndef DISCOUNTSEDITFORM_H
#define DISCOUNTSEDITFORM_H

#include <QDialog>
#include <QDataWidgetMapper>

namespace Ui {
class DiscountsEditForm;
}

class DiscountsEditForm : public QDialog
{
    Q_OBJECT

public:
    explicit DiscountsEditForm(QWidget *parent = nullptr);
    ~DiscountsEditForm();
    void setModel(QAbstractItemModel* model);
    QDataWidgetMapper* mapper;

private slots:
    void on_acceptButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::DiscountsEditForm *ui;
};

#endif // DISCOUNTSEDITFORM_H

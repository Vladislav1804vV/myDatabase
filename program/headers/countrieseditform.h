#ifndef COUNTRIESEDITFORM_H
#define COUNTRIESEDITFORM_H

#include <QDialog>
#include <QDataWidgetMapper>

namespace Ui {
class CountriesEditForm;
}

class CountriesEditForm : public QDialog
{
    Q_OBJECT

public:
    explicit CountriesEditForm(QWidget *parent = nullptr);
    ~CountriesEditForm();
    void setModel(QAbstractItemModel* model);
    QDataWidgetMapper* mapper;

private slots:
    void on_acceptButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::CountriesEditForm *ui;
};

#endif // COUNTRIESEDITFORM_H

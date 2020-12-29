#ifndef PLANESEDITFORM_H
#define PLANESEDITFORM_H

#include <QDialog>
#include <QDataWidgetMapper>

namespace Ui {
class PlanesEditForm;
}

class PlanesEditForm : public QDialog
{
    Q_OBJECT

public:
    explicit PlanesEditForm(QWidget *parent = nullptr);
    ~PlanesEditForm();
    void setModel(QAbstractItemModel* model);
    QDataWidgetMapper* mapper;

private slots:
    void on_acceptButton_clicked();
    void on_cancelButton_clicked();

private:
    Ui::PlanesEditForm *ui;
};

#endif // PLANESEDITFORM_H

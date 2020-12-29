#ifndef SITSEDITFORM_H
#define SITSEDITFORM_H

#include <QDialog>
#include <QDataWidgetMapper>
#include <QMap>

namespace Ui {
class SitsEditForm;
}

class SitsEditForm : public QDialog
{
    Q_OBJECT

public:
    explicit SitsEditForm(QWidget *parent = nullptr);
    ~SitsEditForm();
    void setModel(QAbstractItemModel* model);
    QDataWidgetMapper* mapper;
    void setMapPlanes(QMap<QString, QString> mapPlanes);

private slots:
    void on_acceptButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::SitsEditForm *ui;
    QMap<QString, QString> mapPlanes;
};

#endif // SITSEDITFORM_H

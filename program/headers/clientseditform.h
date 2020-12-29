#ifndef CLIENTSEDITFORM_H
#define CLIENTSEDITFORM_H

#include <QDialog>
#include <QDataWidgetMapper>

namespace Ui {
class ClientsEditForm;
}

class ClientsEditForm : public QDialog
{
    Q_OBJECT

public:
    explicit ClientsEditForm(QWidget *parent = nullptr);
    ~ClientsEditForm();
    void setModel(QAbstractItemModel* model);
    QDataWidgetMapper* mapper;

private slots:
    void on_acceptButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::ClientsEditForm *ui;
};

#endif // CLIENTSEDITFORM_H

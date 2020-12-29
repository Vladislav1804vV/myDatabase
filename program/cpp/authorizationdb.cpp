#include "authorizationdb.h"
#include "ui_authorizationdb.h"

AuthorizationDB::AuthorizationDB(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthorizationDB)
{
    ui->setupUi(this);

    this->setWindowTitle("Администратор");
    this->setWindowFlags (Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    selectTable = new SelectTable();
    connect(selectTable, &SelectTable::selectTableWindow, this, &AuthorizationDB::show);

}

AuthorizationDB::~AuthorizationDB()
{
    delete ui;
}

void AuthorizationDB::on_entryButton_clicked()
{
    QString login = ui->loginEdit->text();
    QString password = ui->passwordEdit->text();

    if (login == "root" && password == "admin") {
        hide();
        QMessageBox::information(this, "Ура", "Вы успешно авторизовались");
        selectTable->show();
    } else {
        QMessageBox::warning(this, "Упс...", "Что-то пошло не так");
    }
}

void AuthorizationDB::closeEvent(QCloseEvent *event)
{
    this->close();
    emit authorizationDBWindow();
}

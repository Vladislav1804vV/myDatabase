#include "getpassword.h"
#include "ui_getpassword.h"

GetPassword::GetPassword(QString login, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetPassword)
{
    ui->setupUi(this);

    this->setWindowTitle("Пароль");
    this->setWindowFlags (Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

//    QRegularExpression string("([А-Я][а-я]*\\s[А-Я][а-я]*\\s[А-Я][а-я]*)|([A-Z][a-z]*\\s[A-Z][a-z]*\\s[A-Z][a-z]*)");
//    QValidator *validator = new QRegularExpressionValidator(string, this);
//    ui->loginEdit->setValidator(validator);
}

GetPassword::~GetPassword()
{
    delete ui;
}

QString GetPassword::getLogin()
{
    return login;
}

void GetPassword::on_getPasswordButton_clicked()
{
    login = ui->loginEdit->text();

    Database DB;
    QString password = DB.getPassword(login);

    if (!password.isEmpty()) {
        close();
        QMessageBox::information(this, "Пароль", "Больше не забывай)");
        this->password = password;
    } else {
        QMessageBox::warning(this, "Упс...", "Пользователь отсутствует");
    }
}

QString GetPassword::getPassword()
{
    return password;
}

void GetPassword::setLogin(QString login)
{
    this->login = login;
}

void GetPassword::on_cancelButton_clicked()
{
    close();
}

void GetPassword::closeEvent(QCloseEvent *event)
{
    this->close();
    emit passwordWindow();
}

void GetPassword::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);
    ui->loginEdit->clear();
    ui->loginEdit->insert(login);
}

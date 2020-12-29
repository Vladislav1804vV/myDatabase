#include "authorization.h"
#include "ui_authorization.h"

Authorization::Authorization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Authorization)
{
    ui->setupUi(this);

    this->setWindowTitle("Авторизация");
    this->setWindowFlags (Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

//    QRegularExpression string("([А-Я][а-я]*\\s[А-Я][а-я]*\\s[А-Я][а-я]*)|([A-Z][a-z]*\\s[A-Z][a-z]*\\s[A-Z][a-z]*)");
//    QValidator *validator = new QRegularExpressionValidator(string, this);
//    ui->loginEdit->setValidator(validator);

    registration = new Registration("");
    connect(registration, &Registration::registrationWindow, this, &Authorization::show);

    password = new GetPassword("");
    connect(password, &GetPassword::passwordWindow, this, &Authorization::show);

    personalArea = new PersonalArea();
    connect(personalArea, &PersonalArea::personalAreaWindow, this, &Authorization::show);
}

Authorization::~Authorization()
{
    delete ui;
}

void Authorization::on_entryButton_clicked()
{

    QString login = ui->loginEdit->text();
    QString password = ui->passwordEdit->text();

    Database DB;
    QSqlRecord record = DB.getClient(login, password);

    if (!record.value(1).toString().isEmpty()) {
        hide();
        QMessageBox::information(this, "Ура", "Вы успешно авторизовались");
        personalArea->setRecord(record);
        personalArea->show();
    } else {
        QMessageBox::warning(this, "Упс...", "Что-то пошло не так");
    }
}

void Authorization::on_forgotButton_clicked()
{
    hide();
    password->setLogin(ui->loginEdit->text());
    password->exec();
    ui->loginEdit->clear();
    ui->loginEdit->insert(password->getLogin());
    ui->passwordEdit->clear();
    ui->passwordEdit->insert(password->getPassword());
}

void Authorization::on_registrationButton_clicked()
{
    hide();
    registration->setLogin(ui->loginEdit->text());
    registration->exec();
    ui->loginEdit->insert(registration->getLogin());
    ui->passwordEdit->insert(registration->getPassword());
}

void Authorization::closeEvent(QCloseEvent *event)
{
    this->close();
    emit authorizationWindow();
}

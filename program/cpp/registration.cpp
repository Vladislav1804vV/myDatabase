#include "registration.h"
#include "ui_registration.h"

Registration::Registration(QString login, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);

    this->setWindowTitle("Регистрация");
    this->setWindowFlags (Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

//    QRegularExpression string;

//    if (ui->surnameEdit->text().contains(QRegularExpression("[А-Я][а-я]*"))) {
//        string = QRegularExpression("[А-Я][а-я]*");
//    } else if (ui->surnameEdit->text().contains(QRegularExpression("[A-Z][a-z]*"))) {
//        string = QRegularExpression("[A-Z][a-z]*");
//    }

//    QValidator *validator = new QRegularExpressionValidator(string, this);
//    ui->nameEdit->setValidator(validator);
//    ui->surnameEdit->setValidator(validator);
//    ui->patronymicEdit->setValidator(validator);

//    QRegularExpression string2("[0-9]*");
//    QValidator *validator2 = new QRegularExpressionValidator(string2, this);
//    ui->passportDataEdit->setValidator(validator2);

}

Registration::~Registration()
{
    delete ui;
}

QString Registration::getLogin()
{
    return login;
}

QString Registration::getPassword()
{
    return password;
}

void Registration::setLogin(QString login)
{
    this->login = login;
}

void Registration::on_isPatronymicCheckBox_stateChanged()
{
    if (ui->patronymicEdit->isEnabled()) {
        ui->patronymicEdit->setEnabled(false);
        ui->patronymicEdit->clear();
    } else {
        ui->patronymicEdit->setEnabled(true);
    }
}

void Registration::on_acceptButton_clicked()
{
    QString resetStyle("QLineEdit { border: 1px solid black; }");
    QString warningStyle("QLineEdit { border: 2px solid red; }");
    QChar gender;

    ui->nameEdit->setStyleSheet(resetStyle);
    ui->surnameEdit->setStyleSheet(resetStyle);
    ui->patronymicEdit->setStyleSheet(resetStyle);
    ui->passportDataEdit->setStyleSheet(resetStyle);
    ui->ageSpinBox->setStyleSheet(resetStyle);
    ui->passwordEdit->setStyleSheet(resetStyle);
    ui->passwordRepeatEdit->setStyleSheet(resetStyle);

    if (ui->nameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ой...", "Вы забыли ввести имя");
        ui->nameEdit->setStyleSheet(warningStyle);
        return;
    }

    if (ui->surnameEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ой...", "Вы забыли ввести фамилию");
        ui->surnameEdit->setStyleSheet(warningStyle);
        return;
    }

    if (ui->patronymicEdit->text().isEmpty() && ui->isPatronymicCheckBox->isChecked()) {
        QMessageBox::warning(this, "Ой...", "Вы забыли ввести отчество");
        ui->patronymicEdit->setStyleSheet(warningStyle);
        return;
    }

    if (ui->passportDataEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ой...", "Вы забыли ввести паспортные данные");
        ui->passportDataEdit->setStyleSheet(warningStyle);
        return;
    }

    if (ui->ageSpinBox->value() <= 0) {
        QMessageBox::warning(this, "Ой...", "Введите корректный возраст");
        ui->ageSpinBox->setStyleSheet(warningStyle);
        return;
    }

    if (ui->maleRadioButton->isChecked()) {
        gender = 'M';
    } else {
        gender = 'F';
    }

    if (ui->passwordEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ой...", "Вы забыли ввести пароль");
        ui->passwordEdit->setStyleSheet(warningStyle);
        return;
    }

    if (ui->passwordRepeatEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Ой...", "Вы забыли повторить пароль");
        ui->passwordRepeatEdit->setStyleSheet(warningStyle);
        return;
    }

    if (ui->passwordEdit->text() != ui->passwordRepeatEdit->text()) {
        QMessageBox::warning(this, "Ой...", "Пароль не совпадает");
        ui->passwordRepeatEdit->setStyleSheet(warningStyle);
        return;
    }

    QString FIO(ui->surnameEdit->text() + ' ' + ui->nameEdit->text() + ' ' + ui->patronymicEdit->text());
    FIO = FIO.trimmed();

    QString password = ui->passwordEdit->text();

    Client client = {
        FIO,
        ui->passportDataEdit->text(),
        ui->ageSpinBox->value(),
        gender,
        password
    };

    Database DB;
    bool isOK;
    isOK = DB.setClient(client);

    if (isOK) {
        close();
        QMessageBox::information(this, "Аккаунт создан", QString("Данные для входа:\n") + QString("Логин:" + FIO + "\n") + QString("Пароль: ") + password + "\n");
        this->login = FIO;
        this->password = password;
    } else {
        QMessageBox::warning(this, "Упс...", "Пользователь невозможно создать");
    }
}

void Registration::on_cancelButton_clicked()
{
    this->close();
}

void Registration::closeEvent(QCloseEvent *event)
{
    this->close();
    emit registrationWindow();
}

void Registration::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);
    QList<QString> listFIO = login.split(' ', Qt::SkipEmptyParts);
    if (listFIO.size() > 0) {
        ui->surnameEdit->insert(listFIO[0]);
    }
    if (listFIO.size() > 1) {
        ui->nameEdit->insert(listFIO[1]);
    }
    if (listFIO.size() > 2) {
        ui->patronymicEdit->insert(listFIO[2]);
        ui->isPatronymicCheckBox->setChecked(true);
    }
}

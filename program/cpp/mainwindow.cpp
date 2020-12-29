#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Главное меню");
    this->setWindowFlags (Qt::Window | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint);

    authorization = new Authorization();
    connect(authorization, &Authorization::authorizationWindow, this, &MainWindow::show);

    authorizationDB = new AuthorizationDB();
    connect(authorizationDB, &AuthorizationDB::authorizationDBWindow, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_personalAreaButton_clicked()
{
    hide();
    authorization->show();
}

void MainWindow::on_DBButton_clicked()
{
    hide();
    authorizationDB->show();
}

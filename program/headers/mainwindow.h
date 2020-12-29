#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "authorization.h"
#include "authorizationdb.h"

#include <QDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_personalAreaButton_clicked();
    void on_DBButton_clicked();

private:
    Ui::MainWindow *ui;
    Authorization* authorization;
    AuthorizationDB* authorizationDB;
};

#endif // MAINWINDOW_H

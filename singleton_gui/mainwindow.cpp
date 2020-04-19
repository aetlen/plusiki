#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "singleton.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    globalStorage *glob = globalStorage::getInstance();
    ui->plainTextEdit->setPlainText(QString::fromStdString(glob->toString()));
    glob->save("A","Pressed");
}

void MainWindow::on_pushButton_2_clicked()
{
    globalStorage *glob = globalStorage::getInstance();
    ui->plainTextEdit->setPlainText(QString::fromStdString(glob->toString()));
    glob->save("B","Pressed");
}

void MainWindow::on_pushButton_3_clicked()
{
    globalStorage *glob = globalStorage::getInstance();
    ui->plainTextEdit->setPlainText(QString::fromStdString(glob->toString()));
    glob->save("C","Pressed");
}

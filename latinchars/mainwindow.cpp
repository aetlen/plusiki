#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tuv.h"
#include <QDebug>

#define ABC_LENGTH 26

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    vec = new Vector<char>(ABC_LENGTH);
    for (size_t i = 0; i<ABC_LENGTH; i++){
        (*vec)[i] = 'a'+i;
    }
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_backButton_clicked()
{
    ui->output->clear();
    int i = vec->size();
    for (auto c = i; c>=0; c--)
        ui->output->insert(QString::fromLocal8Bit(&(*vec)[c], 1));
}

void MainWindow::on_fwdButton_clicked()
{
    ui->output->clear();
    int i = vec->size();
    Vector_itor<char> abc(*vec);
    abc.first();
    for (auto c = 0; c<i; c++)
        ui->output->insert(QString::fromLocal8Bit(abc.next(), 1));
}

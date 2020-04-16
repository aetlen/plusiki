#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FactoryMethod.h"
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


void MainWindow::on_addButton_clicked()
{
    QWidget *el;
    switch (ui->wSelector->currentIndex()) {
    case 0:{
        auto cf = new ComboFactory();
        el = cf->createWidget();
        break;
    }
    case 1:{
        auto tf = new TextFactory();
        el = tf->createWidget();
        break;
    }
    case 2:{
        auto lf = new LCDFactory();
        el = lf->createWidget();
        break;
    }
    default:
        return;
    }
    ui->verticalLayout->addWidget(el);
}

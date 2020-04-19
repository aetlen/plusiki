#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDataWidgetMapper>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dataFrame->hide();
    model->setColumnCount(10);  //Too much for today
    mapper->setModel(model);
    mapper->addMapping(ui->fnameEdit, 0);
    mapper->addMapping(ui->lnameEdit, 1);
    mapper->addMapping(ui->countryEdit, 2);
    mapper->addMapping(ui->cityEdit, 3);
    mapper->addMapping(ui->numlistWidget, 4);
    mapper->addMapping(ui->emailEdit, 5);
    mapper->toFirst();
    ui->contactlist->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addButton_clicked()
{
    auto row = new QStandardItem();
    row->setText("Contact");
    model->appendRow(row);
    if (ui->dataFrame->isHidden())
        mapper->setCurrentIndex(0);
        ui->contactlist->setCurrentIndex(model->index(0,0));
        ui->dataFrame->show();
}

void MainWindow::on_contactlist_clicked(const QModelIndex &index)
{
    mapper->setCurrentIndex(index.row());
}

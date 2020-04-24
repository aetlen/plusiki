#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDataWidgetMapper>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QList>
#include <QDomDocument>
#include <QDomElement>

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

void MainWindow::storeXML(QString path){
    QDomDocument doc("contacts");
    auto root = doc.createElement("contacts");
    for (auto i = 0; i < model->rowCount(); i++){
        QString firstname = model->data(model->index(i, 0)).toString();
        QString lastname = model->data(model->index(i, 1)).toString();
        QString country = model->data(model->index(i, 2)).toString();
        QString city = model->data(model->index(i, 3)).toString();

        QDomElement el = doc.createElement("contact");
        QDomElement Identiefer = doc.createElement("Identiefer");
        Identiefer.setAttribute("firstname", firstname);
        Identiefer.setAttribute("lastname", lastname);
        QDomElement Address = doc.createElement("Address");
        Address.setAttribute("country", country);
        Address.setAttribute("city", city);
        el.appendChild(Address);
        el.appendChild(Identiefer);
        root.appendChild(el);
    }
    doc.appendChild(root);
    QFile file(path);
    if(file.open(QIODevice::WriteOnly)) {
        QString text_xml = doc.toString();
        qDebug() << text_xml;
        QTextStream(&file) << text_xml;
        file.close();
    }
}

void MainWindow::on_saveButton_clicked()
{
    storeXML("adressbook.xml");
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../latinchars/tuv.h"
#include <string>
#include <QTextStream>
#include <QString>
#include <algorithm>
using std::string;

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

void MainWindow::on_sortButton_clicked()
{
    // Amount of lines
    int sz = ui->plainTextEdit->blockCount();
    // Vector exactly of its size
    auto vec = new Vector<string>(sz);
    QString text = ui->plainTextEdit->toPlainText();
    QTextStream * stream = new QTextStream(&text , QIODevice::ReadOnly);
    // Double condition in case the text has been changed
    for (int n=0; !stream->atEnd() && n < sz; n++)
    {
        //crashes the program. sometimes. XD
        (*vec)[n] = stream->readLine().toStdString();
    }
    delete(stream);
    string temp;
    // Сортировка массива пузырьком
       for (int i = 0; i < sz - 1; i++) {
           for (int j = 0; j < sz - i - 1; j++) {
               if ((*vec)[j] > (*vec)[j + 1]) {
                   // меняем элементы местами
                   temp = (*vec)[j];
                   (*vec)[j] = (*vec)[j + 1];
                   (*vec)[j + 1] = temp;
               }
           }
       }
    ui->plainTextEdit->setStyleSheet("color:red;");
    ui->plainTextEdit->clear();
    for (auto n = 0; n < sz; n++)
        ui->plainTextEdit->appendPlainText(QString::fromStdString((*vec)[n]));
    delete(vec);
}

void MainWindow::on_clearButton_clicked()
{
    QStringList citrus = {"orange", "lemon"};
    // Amount of lines
    int sz = ui->plainTextEdit->blockCount();
    // Vector exactly of its size
    auto vec = new Vector<string>(sz);
    QString text = ui->plainTextEdit->toPlainText();
    QTextStream * stream = new QTextStream(&text , QIODevice::ReadOnly);
    // Double condition in case the text has been changed
    for (int n=0; !stream->atEnd() && n < sz; n++)
    {
        (*vec)[n] = stream->readLine().toStdString();
    }
    ui->plainTextEdit->setStyleSheet("");
    ui->plainTextEdit->clear();
    for (auto n = 0; n < sz; n++){
        auto str = QString::fromStdString((*vec)[n]);
        if (!citrus.contains(str)) ui->plainTextEdit->appendPlainText(str);
    }
    delete(vec);
    delete(stream);
}

void MainWindow::on_aButton_clicked()
{
    // Amount of lines
    int sz = ui->plainTextEdit->blockCount();
    // Vector exactly of its size
    auto vec = new Vector<string>(sz);
    QString text = ui->plainTextEdit->toPlainText();
    QTextStream * stream = new QTextStream(&text , QIODevice::ReadOnly);
    // Double condition in case the text has been changed
    for (int n=0; !stream->atEnd() && n < sz; n++)
    {
        (*vec)[n] = stream->readLine().toStdString();
    }
    ui->plainTextEdit->setStyleSheet("color:green;");
    ui->plainTextEdit->clear();
    for (auto n = 0; n < sz; n++){
        auto str = QString::fromStdString((*vec)[n]);
        if (str.startsWith("a")) ui->plainTextEdit->appendPlainText(str);
    }
    delete(vec);
    delete(stream);
}

bool cmp_date_gt(string a, string b){
    string yeara = a.substr(3,2);
    string yearb = b.substr(3,2);
    if (yeara != yearb)
        return yeara > yearb;
    auto mountha = QString::fromStdString(a.substr(0,3));
    auto mounthb = QString::fromStdString(b.substr(0,3));
    QStringList mounths = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        return mounths.indexOf(mountha) > mounths.indexOf(mounthb);
}

void MainWindow::on_pushButton_clicked()
{
    // Amount of lines
    int sz = ui->plainTextEdit->blockCount();
    // Vector exactly of its size
    auto vec = new Vector<string>(sz);
    QString text = ui->plainTextEdit->toPlainText();
    QTextStream * stream = new QTextStream(&text , QIODevice::ReadOnly);
    // Double condition in case the text has been changed
    for (int n=0; !stream->atEnd() && n < sz; n++)
    {
        //crashes the program. sometimes. XD
        (*vec)[n] = stream->readLine().toStdString();
    }
    delete(stream);
    string temp;
    // Сортировка массива пузырьком
       for (int i = 0; i < sz - 1; i++) {
           for (int j = 0; j < sz - i - 1; j++) {
               if (cmp_date_gt((*vec)[j] , (*vec)[j + 1])) {
                   // меняем элементы местами
                   temp = (*vec)[j];
                   (*vec)[j] = (*vec)[j + 1];
                   (*vec)[j + 1] = temp;
               }
           }
       }
    ui->plainTextEdit->setStyleSheet("color:red;");
    ui->plainTextEdit->clear();
    for (auto n = 0; n < sz; n++)
        ui->plainTextEdit->appendPlainText(QString::fromStdString((*vec)[n]));
    delete(vec);
}

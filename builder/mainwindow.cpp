#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfontbuilder.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QFont font = QFontBuilder()
            .size(12)
            .bold()
            .italic()
            .font("Times New Roman")
            .build();
    ui->setupUi(this);
    ui->label->setFont(font);
}

MainWindow::~MainWindow()
{
    delete ui;
}


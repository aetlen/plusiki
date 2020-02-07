#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "tuv.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_backButton_clicked();

    void on_fwdButton_clicked();

private:
    Ui::MainWindow *ui;
    Vector<char> *vec;
};
#endif // MAINWINDOW_H

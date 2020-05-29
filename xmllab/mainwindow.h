#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QDataWidgetMapper>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QStandardItemModel* model = new QStandardItemModel();
    QDataWidgetMapper *mapper = new QDataWidgetMapper();
    void storeXML(QString path);

private slots:
    void on_addButton_clicked();

    void on_contactlist_clicked(const QModelIndex &index);

    void on_saveButton_clicked();

    void on_deleteButton_clicked();

    void on_atrkitButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

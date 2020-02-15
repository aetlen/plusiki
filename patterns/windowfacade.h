#ifndef WINDOWFACADE_H
#define WINDOWFACADE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QDateEdit>

class WindowFacade : public QWidget
{
    Q_OBJECT
public:
    explicit WindowFacade(QWidget *parent = nullptr, const QString label = "Default");
    QStringList exec();
signals:

private:
    QLabel txt_lbl;
    QLabel digits_lbl;
    QLabel dt_lbl;
    QLineEdit le;
    QSpinBox sb;
    QDateEdit de;
    QPushButton btn;
};

#endif // WINDOWFACADE_H

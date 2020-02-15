#include "windowfacade.h"
#include <QStringList>
#include <QEventLoop>
#include <QGridLayout>
#include <QLayout>


WindowFacade::WindowFacade(QWidget *parent, const QString label) : QWidget(parent)
{
    setWindowTitle(label);
    auto lay = new QGridLayout(this);
    setLayout(lay);
    sb.setRange(-10000,10000);
    lay->addWidget(&txt_lbl,0,0);
    lay->addWidget(&digits_lbl,1,0);
    lay->addWidget(&dt_lbl,2,0);
    lay->addWidget(&btn,3,1);
    lay->addWidget(&le,0,1);
    lay->addWidget(&sb,1,1);
    lay->addWidget(&de,2,1);
    btn.setText("OK");
    txt_lbl.setText("Text");
    digits_lbl.setText("Digits");
    dt_lbl.setText("Date");
    show();
}


QStringList WindowFacade::exec(){
    QStringList res;
    QEventLoop loop;
    connect(&btn, SIGNAL(clicked()), & loop, SLOT(quit()));
    loop.exec();
    res.append(QString("Text: %1").arg(le.text()));
    res.append(QString("Digit: %1").arg(sb.text()));
    res.append(QString("Date: %1").arg(de.text()));
    close();
    return res;
}

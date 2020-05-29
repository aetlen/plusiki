#include "otchislyator.h"

Otchislyator::Otchislyator(QObject *parent) : QObject(parent)
{

}

void Otchislyator::someSlot(){
    static int call = 0;
    QString *str = new QString("Expelled ");
    str->append(QString::number(++call));
    emit expell(str);
}

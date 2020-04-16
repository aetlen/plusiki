#ifndef FACTORYMETHOD_H
#define FACTORYMETHOD_H

#endif // FACTORYMETHOD_H
#include <QWidget>
#include <QComboBox>
#include <QTextEdit>
#include <QLCDNumber>

class FactoryMethod {
public:
    virtual QWidget* createWidget() = 0;
};

class ComboFactory : public FactoryMethod{
public:
    QWidget* createWidget(){
        QComboBox * ptr = new QComboBox();
        ptr->setToolTip("Select your chair");
        ptr->insertItem(0, "Chair one");
        ptr->insertItem(1, "Chair two");
        return ptr;
    }
};
class TextFactory : public FactoryMethod{
public:
    QWidget* createWidget(){
        QTextEdit * ptr = new QTextEdit();
        ptr->setToolTip("Enter your text here");
        return ptr;
    }
};
class LCDFactory : public FactoryMethod{
public:
    QWidget* createWidget(){
        QLCDNumber * ptr = new QLCDNumber();
        ptr->setToolTip("NUMER AAAA");
        ptr->setHexMode();
        ptr->display(0x3f);
        return ptr;
    }
};

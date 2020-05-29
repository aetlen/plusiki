#include "krasnayaknopka.h"

Krasnayaknopka::Krasnayaknopka() : QPushButton()
{
    setStyleSheet("background-color:red;");
    connect(this, SIGNAL (released()),this, SIGNAL (panic())); //Можно соединить два сигнала, но не два слота
    show();
}
void Krasnayaknopka::changeText(QString *str){
    setText(*str);
}

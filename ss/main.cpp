#include <QApplication> // Для создания EventLoop
#include <QObject>  // Для вызова connect напрямую (он статический)
#include "krasnayaknopka.h"
#include "otchislyator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Krasnayaknopka obj1;
    Otchislyator obj2;
    QObject::connect(&obj1, SIGNAL(panic()), &obj2, SLOT(someSlot()));
    obj2.connect(&obj1, &Krasnayaknopka::panic, &obj2, &Otchislyator::someSlot);  //Вызывется дважды
    QObject::connect(&obj2, SIGNAL(expell(QString*)), &obj1, SLOT(changeText(QString*)));
    return a.exec();
}

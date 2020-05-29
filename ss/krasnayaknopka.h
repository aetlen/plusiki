#ifndef KRASNAYAKNOPKA_H
#define KRASNAYAKNOPKA_H

#include <QObject>
#include <QPushButton>

class Krasnayaknopka : public QPushButton
{
    Q_OBJECT
public:
    explicit Krasnayaknopka();
    ~Krasnayaknopka() = default;
public slots:
    void changeText(QString *txt);
signals:
    void panic();
};

#endif // KRASNAYAKNOPKA_H

#ifndef OTCHISLYATOR_H
#define OTCHISLYATOR_H

#include <QObject>

class Otchislyator : public QObject
{
    Q_OBJECT
public:
    explicit Otchislyator(QObject *parent = nullptr);

public slots:
    void someSlot();
signals:
    void expell(QString *reason);
};

#endif // OTCHISLYATOR_H

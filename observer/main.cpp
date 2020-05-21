#include <QString>
#include <QTextEdit>
#include <QObject>
#include <QApplication>
#include <QDebug>

using namespace std;
class Handler : public QObject{
public:
    virtual void setName(QString) = 0;
    virtual void notify(/*Опциональные параметры*/) = 0;
};
class Observer : public QObject{
public:
    virtual void subscribe(Handler*, int ev) = 0;
    virtual void unsubscribe(Handler*, int ev) = 0;
    virtual void notify(/*, Опциональные параметры, такие как тип события*/) = 0;
};
class curHandler : public Handler {
public:
    curHandler() = default;
    void setName(QString name){
        n = name;
    };
public slots:
    void notify(/*Опциональные параметры*/){
        qDebug() << "The cursor has been changed";
    };
private:
    QString n;
};
class selHandler : public Handler {
public:
    selHandler() = default;
    void setName(QString name){
        n = name;
    };
public slots:
    void notify(/*Опциональные параметры*/){
        qDebug() << "The selection has been changed";
    };
private:
    QString n;
};
class teHandler : public Handler {
public:
    teHandler() = default;
    void setName(QString name){
        n = name;
    };
public slots:
    void notify(/*Опциональные параметры*/){
        qDebug() << "The text has been edited";
    };
private:
    QString n;
};

class concreteObserver : public Observer{
public:
    concreteObserver(){
        te = new QTextEdit();
    };
    concreteObserver(QTextEdit* ste){
        te = ste;
    };
    ~concreteObserver() = default;
    void subscribe(Handler* hand, int ev) {
        switch (ev){
            case 0:
                QObject::connect(te,&QTextEdit::cursorPositionChanged, hand,&Handler::notify);
                break;
            case 1:
                QObject::connect(te,&QTextEdit::selectionChanged, hand,&Handler::notify);
                break;
            case 2:
                QObject::connect(te,&QTextEdit::textChanged, hand,&Handler::notify);
                break;
            default:
                break;
            };
    };
    void unsubscribe(Handler* hand, int ev) {
        switch (ev){
        case 0:
            QObject::disconnect(te,&QTextEdit::cursorPositionChanged, hand,&Handler::notify);
            break;
        case 1:
            QObject::disconnect(te,&QTextEdit::selectionChanged, hand,&Handler::notify);
            break;
        case 2:
            QObject::disconnect(te,&QTextEdit::textChanged, hand,&Handler::notify);
            break;
        default:
            break;
        };
    };
    void notify(){};
private:
    QTextEdit* te = nullptr;
};

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    QTextEdit *te = new QTextEdit();
    concreteObserver co(te);
    curHandler cr; teHandler th; selHandler sel;
    co.subscribe(&cr,0); co.subscribe(&th,2); co.subscribe(&sel,1);
    te->show();
    return a.exec();
}

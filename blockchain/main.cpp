#include <iostream>
#include <QString>
#include <QMap>
#include <QCryptographicHash>
#include <QByteArray>
struct Rights{
    bool read = false;
    bool write = false;
};

using namespace std;
class User {
public:
    virtual QString getName() = 0;
    virtual void setName(QString) = 0;
    virtual void setPassword(QString) = 0;
    virtual void setRights(QString resourceId, Rights r) = 0;
    virtual Rights getRights(QString resourceId) = 0;
    virtual QByteArray getPasswordHash() = 0;
};

class Authorization {
public:
    virtual bool check(User*, QString resourceId) = 0;
    virtual void setNext(Authorization*) = 0;
};

class Person : public User{
public:
    virtual QString getName(){
        return name;
    }
    virtual void setName(QString new_name){
        name = new_name;
    }
    virtual void setPassword(QString new_pass){
        pass = QCryptographicHash::hash(QByteArray::fromStdString(new_pass.toStdString()),QCryptographicHash::Sha1);
    }
    virtual void setRights(QString resourceId, Rights n_r){
        access.insert(resourceId, n_r);
    }
    virtual Rights getRights(QString resourceId){
        return access[resourceId];
    }
    virtual QByteArray getPasswordHash(){
        return pass;
    }
private:
    QByteArray pass;
    QString name;
    QMap<QString, Rights> access;
};

class Check_read : public Authorization{
public:
    Check_read() = default;
    ~Check_read() = default;
    bool check(User *u, QString resourceId){
        if (u->getRights(resourceId).read)
             std::cout << resourceId.toStdString() << ": read rights granted "<< std::endl;
        bool res = false;
        if (next)
                res = next->check(u, resourceId);
        return res || u->getRights(resourceId).read;
    };
    void setNext(Authorization* a){
        next = a;
    };
private:
    Authorization* next = nullptr;
};

class Check_write : public Authorization{
public:
    Check_write() = default;
    ~Check_write() = default;
    bool check(User *u, QString resourceId){
        if (u->getRights(resourceId).write)
            std::cout << resourceId.toStdString() << ": write rights granted "<< std::endl;
        bool res = false;
        if (next)
            res = next->check(u, resourceId);
        return res || u->getRights(resourceId).write;
    };
    void setNext(Authorization* a){
        next = a;
    };
private:
    Authorization* next = nullptr;
};

class Check_pass : public Authorization{
public:
    Check_pass() = default;
    ~Check_pass() = default;
    bool check(User *u, QString resourceId){
        std::string name;
        std::string pass;
        std::cout << "Enter name and password" << endl;
        std::cin >> name >> pass;
        auto hash = QCryptographicHash::hash(QByteArray::fromStdString(pass),QCryptographicHash::Sha1);
        bool res = false;
        if (u->getName().toStdString() == name && u->getPasswordHash() == hash){
            std::cout << u->getName().toStdString() << " : user authorized "<< std::endl;
            res = next->check(u, resourceId);
        }
        return res;
    };
    void setNext(Authorization* a){
        next = a;
    };
private:
    Authorization* next = nullptr;
};

int main()
{
    Rights rw;
    rw.read = true;
    rw.write = true;

    Rights r;
    r.read = true;
    r.write = false;

    Rights nothing;
    nothing.read = false;
    nothing.write = false;

    Person Pavel;
    Pavel.setName("Pavel");
    Pavel.setPassword("Strong_pass");
    Pavel.setRights("secret_object", r);

    Check_pass cp;
    Check_read cr;
    Check_write cw;
    cp.setNext(&cr);
    cr.setNext(&cw);
    cp.check(&Pavel, "secret_object");
    return 0;
}

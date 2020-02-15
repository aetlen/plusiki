#include <QApplication>
#include <QString>
#include <iostream>
#include <memory>

const int CHILD_COUNT = 10;

class FileSystemInterface {
public:
    virtual QString name() = 0; // Получить имя папки/файла
    virtual void name(QString) = 0; // Задать имя папки/файла

    // Получить количество всех элементов в папке (рекурсивно, включая подпапки)
    virtual int count() = 0;
    virtual bool isFile() = 0; // Возвращает True для файлов
    virtual bool isFolder() = 0;// Возвращает False для файлов
    virtual QString toString() = 0; // Выводит имя файла/имя папки и список папок/файлов внутри
};

class File : public FileSystemInterface{
public:
    QString name() override{
        return nm;
    }
    void name(QString new_name) override{
        nm = new_name;
    }
    bool isFolder() override{
        return false;
    };
    bool isFile() override{
        return true;
    }
    int count() override{
        return 1;
    }
    QString toString() override{
        return nm;
    }
private:
    QString nm;
};

class Directory : public FileSystemInterface{
    using FPtr = FileSystemInterface *;
public:
    QString name() override{
        return nm;
    }
    void add(FPtr child){
        children.push_back(child);
    }
    void name(QString new_name) override{
        nm = new_name;
    }
    bool isFolder() override{
        return true;
    };
    bool isFile() override{
        return false;
    }
    int count() override{
        int i = 0;
        for (auto c: children){
            i+=c->count();
        }
        return i;
    }
    QString toString() override{
        QString allofthem;
        allofthem.append(nm);
        allofthem.append(":\n");
        for (auto c: children){
            auto tx = c->toString().split("\n");
            for (auto &t: tx)
                t = "   " + t;
            allofthem.append(tx.join("\n") + "\n");
        }
        return allofthem;
    }
private:
    QString nm;
    std::vector<FPtr> children;
};

int main()
{
    auto dir = new Directory();
    dir->name("ROOT");
    for (int i=0; i< CHILD_COUNT; i++){
        auto f = new File();
        f->name(QString("File #%1").arg(i));
        dir->add(f);
    }
    auto dir2 = new Directory();
    dir2->name("ULTRA");
    for (int i=0; i< CHILD_COUNT; i++){
        auto f = new File();
        f->name(QString("Ultrafile #%1").arg(i));
        dir2->add(f);
    }
    dir->add(dir2);
    std::cout << "Child count:" << dir->count() << std::endl;
    std::cout << dir->toString().toStdString();
    return 0;
}

#include <QApplication>
#include <QString>
#include <iostream>
#include <memory>

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
    QString name(){
        return nm;
    }
    void name(QString new_name){
        nm = new_name;
    }
    bool isFolder(){
        return false;
    };
    bool isFile(){
        return true;
    }
    int count(){
        return 1;
    }
    QString toString(){
        return nm;
    }
private:
    QString nm;
};

class Directory : public FileSystemInterface{
    typedef FileSystemInterface* FPtr;
public:
    QString name(){
        return nm;
    }
    void add(FPtr child){
        children.push_back(child);
    }
    void name(QString new_name){
        nm = new_name;
    }
    bool isFolder(){
        return true;
    };
    bool isFile(){
        return false;
    }
    int count(){
        int i = 0;
        for (auto c: children){
            i+=c->count();
        }
        return i;
    }
    QString toString(){
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
    Directory *dir = new Directory();
    dir->name("ROOT");
    for (int i=0; i<10; i++){
        auto f = new File();
        f->name(QString("File #%1").arg(i));
        dir->add(f);
    }
    Directory *dir2 = new Directory();
    dir2->name("ULTRA");
    for (int i=0; i<10; i++){
        auto f = new File();
        f->name(QString("Ultrafile #%1").arg(i));
        dir2->add(f);
    }
    dir->add(dir2);
    std::cout << "Child count:" << dir->count() << std::endl;
    std::cout << dir->toString().toStdString();
    return 0;
}

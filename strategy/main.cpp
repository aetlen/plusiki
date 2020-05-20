#include <iostream>
#include <fstream>
#include <QApplication>
#include <QTextEdit>

class Strategy
{
public:
    virtual ~Strategy() {}
    virtual void use(std::string str) = 0;
};

class Strategy_std: public Strategy
{
public:
    void use(std::string str){
        std::cout << str << std::endl;
    }
};

class Strategy_file: public Strategy
{
public:
    void use(std::string str){
        std::ofstream myfile;
        myfile.open ("example.txt");
        myfile << str << std::endl;
        myfile.close();
    }
};

class Strategy_te: public Strategy
{
public:
    void use(std::string str){
        QTextEdit *te = new QTextEdit(QString::fromStdString(str));
        te->show();
    }
};

class Context
{
protected:
    Strategy* operation;

public:
    virtual ~Context() {}
    virtual void useStrategy(std::string str) = 0;
    virtual void setStrategy(Strategy* v) = 0;
};

class Client: public Context
{
public:
    void useStrategy(std::string str)
    {
        operation->use(str);
    }

    void setStrategy(Strategy* o)
    {
        operation = o;
    }
};

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Client customClient;
    Strategy_std str1;
    Strategy_file str2;
    Strategy_te str3;

    customClient.setStrategy(&str1);
    customClient.useStrategy("Standart strategy");
    customClient.setStrategy(&str2);
    customClient.useStrategy("File strategy");
    customClient.setStrategy(&str3);
    customClient.useStrategy("QTextEdit is here");

    return app.exec();
}

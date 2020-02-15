#include <QApplication>
#include <QFont>
#include <QLabel>

class Underlined : public QFont{
public:
    Underlined(QFont* p) : QFont(*p){
        setUnderline(true);
    }
};

class Bold : public QFont{
public:
    Bold(QFont* p) : QFont(*p){
        setBold(true);
    }
};

class Italic : public QFont{
public:
    Italic(QFont* p) : QFont(*p){
        setItalic(true);
    }
};
class TimesNewRoman : public QFont{
public:
    TimesNewRoman(QFont* p) : QFont(*p){
        setFamily("Times new Roman");
    }
};
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont* font = new TimesNewRoman(
                new Italic(
                    new Bold(
                        new Underlined(new QFont))));
    QLabel label("Hello fontrld");
    label.setFont(*font);
    label.show();
    return QApplication::exec();
}

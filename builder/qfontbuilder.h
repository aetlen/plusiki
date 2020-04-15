#ifndef QFONTBUILDER_H
#define QFONTBUILDER_H
#include <QFont>
#include <QString>

class QFontBuilder : public QFont
{
public:
    QFontBuilder() = default;
    QFontBuilder size(int sz){_size = sz; return *this;}
    QFontBuilder bold(){_bold = true; return *this;}
    QFontBuilder italic(){_italic = true; return *this;}
    QFontBuilder font(QString str){_font = str; return *this;}
    QFont build(){
        setWeight(_size);
        setBold(_bold);
        setItalic(_italic);
        setFamily(_font);
        return *((QFont*) this);
    }
private:
    int _size = 0;
    bool _bold = false, _italic = false;
    QString _font;
};

#endif // QFONTBUILDER_H

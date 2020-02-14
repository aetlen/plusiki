#include <QApplication>
#include <QTextEdit>
#include <string>
#include <QString>

class QTextEditAdapter : public QTextEdit{
public:
    void setText(const std::string &text){
        QTextEdit::setText(QString::fromStdString(text));
    }
    void append(const std::string &text){
        QTextEdit::append(QString::fromStdString(text));
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextEdit *adapter = new QTextEditAdapter();
    std::string intro = "<b>Artom</b>";
    ((QTextEditAdapter* ) adapter)->setText(intro);
    adapter->append("loch");
    // std::string res = adapter.toplaintext();
    adapter->show();
    return a.exec();
}

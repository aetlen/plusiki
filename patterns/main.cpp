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
    QTextEditAdapter *adapter = new QTextEditAdapter();
    std::string intro = "<b>Artom</b>";
    adapter->setText(intro);
    adapter->append("loch");
    // std::string res = adapter.toplaintext();
    ((QTextEditAdapter* )adapter)->show();
    return a.exec();
}

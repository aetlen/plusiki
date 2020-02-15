#include <QApplication>
#include <QTextEdit>
#include <string>

class QTextEditAdapter : public QTextEdit{
public:
    void setText(const std::string &text){
        QTextEdit::setText(QString::fromStdString(text));
    }
    void append(const std::string &text){
        QTextEdit::append(QString::fromStdString(text));
    }
    std::string toPlainText(){
        return QTextEdit::toPlainText().toStdString();
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextEdit *adapter = new QTextEditAdapter();
    std::string intro = "<b>Artom</b>";
    (dynamic_cast<QTextEditAdapter*>( adapter))->setText(intro);
    (dynamic_cast<QTextEditAdapter*>( adapter))->append((std::string) "loch");
    std::string res = (dynamic_cast<QTextEditAdapter*>( adapter))->toPlainText();
    adapter->show();
    return QApplication::exec();
}

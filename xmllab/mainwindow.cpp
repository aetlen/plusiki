#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDataWidgetMapper>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QList>
#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QXmlSimpleReader>
#include <QInputDialog>
// Method 1 = DOM, 0 = SAX
#define method 0

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dataFrame->hide();
    model->setColumnCount(10);  //Too much for today
    mapper->setModel(model);
    mapper->addMapping(ui->fnameEdit, 0);
    mapper->addMapping(ui->lnameEdit, 1);
    mapper->addMapping(ui->countryEdit, 2);
    mapper->addMapping(ui->cityEdit, 3);
    mapper->addMapping(ui->emailEdit, 4);
    mapper->addMapping(ui->mnumEdit, 5);
    mapper->addMapping(ui->hnumEdit, 6);
    mapper->addMapping(ui->wnumEdit, 7);

    mapper->toFirst();
    ui->contactlist->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addButton_clicked()
{
    auto row = new QStandardItem();
    row->setText("Contact");
    model->appendRow(row);
    if (ui->dataFrame->isHidden()){
        mapper->setCurrentIndex(0);
        ui->contactlist->setCurrentIndex(model->index(0,0));
        ui->dataFrame->show();
    }
}

void MainWindow::on_contactlist_clicked(const QModelIndex &index)
{
    mapper->setCurrentIndex(index.row());
}

void MainWindow::storeXML(QString path){
    QDomDocument doc("contacts");
    auto root = doc.createElement("contacts");
    for (auto i = 0; i < model->rowCount(); i++){
        QString firstname = model->data(model->index(i, 0)).toString();
        QString lastname = model->data(model->index(i, 1)).toString();
        QString country = model->data(model->index(i, 2)).toString();
        QString city = model->data(model->index(i, 3)).toString();
        QString email = model->data(model->index(i, 4)).toString();

        QDomElement el = doc.createElement("contact");
        QDomElement Identiefer = doc.createElement("Identiefer");
        Identiefer.setAttribute("firstname", firstname);
        Identiefer.setAttribute("lastname", lastname);
        QDomElement Address = doc.createElement("Address");
        Address.setAttribute("country", country);
        Address.setAttribute("city", city);
        QDomElement Phones = doc.createElement("Phones");
        for (int numid = 5; numid <=7; numid++){
            QDomElement Phone = doc.createElement("Phone");
            QString num = model->data(model->index(i, numid)).toString();
            Phone.setAttribute("number", num);
            Phone.setAttribute("type", numid);
            Phones.appendChild(Phone);
        }
        QDomElement Email = doc.createElement("Email");
        Email.setAttribute("email", email);
        el.appendChild(Address);
        el.appendChild(Identiefer);
        el.appendChild(Phones);
        el.appendChild(Email);
        root.appendChild(el);
    }
    doc.appendChild(root);
    QFile file(path);
    if(file.open(QIODevice::WriteOnly)) {
        QString text_xml = doc.toString();
        qDebug() << text_xml;
        QTextStream(&file) << text_xml;
        file.close();
    }
}

void MainWindow::on_saveButton_clicked()
{
    storeXML("adressbook.xml");
}

void MainWindow::on_deleteButton_clicked()
{
    model->removeRows(ui->contactlist->currentIndex().row(),1);
}

#if method
void MainWindow::on_atrkitButton_clicked()
{
    model->clear();
    qDebug() << "DOM";
    QDomDocument document;
    //load the file
    QFile xmlFile("adressbook.xml");
    if (!xmlFile.exists() || !xmlFile.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Check your file";
        return;
    }
    QDomDocument domDocument;
    domDocument.setContent(&xmlFile);
    QDomElement topElement = domDocument.documentElement();
    QDomNode contactNode = topElement.firstChild();
    int contnum = 0;
    while (!contactNode.isNull()){
        QDomElement contactElement = contactNode.toElement();
        if (contactElement.tagName() == "contact"){
              QDomNode node = contactElement.firstChild();
              auto row = new QStandardItem();
              row->setText("Contact");
              model->appendRow(row);
              while (!node.isNull()){
                 QDomElement element = node.toElement();
                 if (element.tagName() == "Identiefer"){
                     QStandardItem *item = new QStandardItem(element.attribute("firstname"));
                     model->setItem(contnum, 0, item);
                     QStandardItem *item2 = new QStandardItem(element.attribute("lastname"));
                     model->setItem(contnum, 1, item2);
                 }
                 else if (element.tagName() == "Address"){
                     QStandardItem *item = new QStandardItem(element.attribute("country"));
                     model->setItem(contnum, 2, item);
                     QStandardItem *item2 = new QStandardItem(element.attribute("city"));
                     model->setItem(contnum, 3, item2);
                 }
                 else if (element.tagName() == "Email"){
                         QStandardItem *item = new QStandardItem(element.attribute("email"));
                         model->setItem(contnum, 4, item);
                 }
                 else if (element.tagName() == "Phones"){
                     auto pnode = element.firstChild();
                     while (!pnode.isNull()){
                         QDomElement pelement = pnode.toElement();
                         QStandardItem *item = new QStandardItem(pelement.attribute("number"));
                         model->setItem(contnum, pelement.attribute("type").toInt(), item);
                         pnode = pnode.nextSibling();
                     }
                 }
                 node = node.nextSibling();
              }
              contnum++;
        }
        contactNode = contactNode.nextSibling();
    }
    if (ui->dataFrame->isHidden()){
        mapper->setCurrentIndex(0);
        ui->contactlist->setCurrentIndex(model->index(0,0));
        ui->dataFrame->show();
    }
}

#else
class AddressBookParser : public QXmlDefaultHandler {
public:
    QStandardItemModel* model;
    bool startElement(const QString&,
                      const QString&,
                      const QString &tagName,
                      const QXmlAttributes& attrs
                     )
    {
        if (tagName =="contact")
        {
            auto row = new QStandardItem();
            row->setText("contact");
            model->appendRow(row);
        }
        if (tagName == "Phone")
        {
            int type;
            QString num;
            for (int i = 0; i< attrs.count();i++)
            {
                if (attrs.localName(i)=="type")
                    type = attrs.value(i).toInt();
                if (attrs.localName(i)=="number")
                    num = attrs.value(i);
            }
            QStandardItem *item = new QStandardItem(num);
            model->setItem(cur_num, type, item);
        }
        for(int i = 0; i < attrs.count(); i++) {
            if(attrs.localName(i) == "country") {
                QStandardItem *item = new QStandardItem(attrs.value(i));
                model->setItem(cur_num, 2, item);
            }
            if(attrs.localName(i) == "city") {
                QStandardItem *item = new QStandardItem(attrs.value(i));
                model->setItem(cur_num, 3, item);
            }
            if(attrs.localName(i) == "firstname") {
                QStandardItem *item = new QStandardItem(attrs.value(i));
                model->setItem(cur_num, 0, item);
            }
            if(attrs.localName(i) == "lastname") {
                QStandardItem *item = new QStandardItem(attrs.value(i));
                model->setItem(cur_num, 1, item);
            }
            if(attrs.localName(i) == "email") {
                QStandardItem *item = new QStandardItem(attrs.value(i));
                model->setItem(cur_num, 4, item);
            }
            if(attrs.localName(i) == "type") {
            }
            if(attrs.localName(i) == "number") {
            }
        }
        return true;
    }

    bool characters(const QString& strText)
    {
        m_strText = strText;
        return true;
    }

    bool endElement(const QString&, const QString&, const QString& str)
    {
            if (str=="contact")
                cur_num++;
        return true;
    }

    bool fatalError(const QXmlParseException& exception)
    {
        qDebug() << "Line:"      << exception.lineNumber()
                 << ", Column:"  << exception.columnNumber()
                 << ", Message:" << exception.message();
        return false;
    }
private:
    QString m_strText;
    int cur_num = 0;
};

void MainWindow::on_atrkitButton_clicked()
{
    model->clear();
    qDebug() << "SAX";
    AddressBookParser handler;
    QFile             file("adressbook.xml");
    QXmlInputSource   source(&file);
    QXmlSimpleReader  reader;
    handler.model = model;
    reader.setContentHandler(&handler);
    reader.parse(source);
    if (ui->dataFrame->isHidden()){
        mapper->setCurrentIndex(0);
        ui->contactlist->setCurrentIndex(model->index(0,0));
        ui->dataFrame->show();
    }
}
#endif

void MainWindow::on_searchButton_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Search"),
                                         tr("Search:"), QLineEdit::Normal,
                                         "Whatever you're interested in", &ok);
    if (ok && !text.isEmpty()){
        // Num of the last result
        int num = -1;
        // Search
        for (int i = model->rowCount(); i >= 0; i--){
            int searches[] = {0, 1, 5, 6, 7};
            for (auto l : searches){
                QString val = model->data(model->index(i, l)).toString();
                qDebug() << val;
                if (val.contains(text))
                    num = i;
            }
        }
        if (num == -1){
            qDebug() << "Not found: " << text;
        }
        else{
            ui->contactlist->setCurrentIndex(model->index(num,0));
            mapper->setCurrentIndex(num);
        }
    }
}

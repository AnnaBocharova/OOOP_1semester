#include "new_task.h"
#include "ui_new_task.h"
#include "notation.h"

#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QComboBox>
#include <QDebug>

#include <QClipboard>

new_task::new_task(QWidget *parent, bool b) :
    QMainWindow(parent),
    ui(new Ui::new_task)
{
    ui->setupUi(this);
    setWindowTitle("New note");

    keyEnter = new QShortcut(this);
    keyEnter->setKey(Qt::Key_Return);
    connect(keyEnter, SIGNAL(activated()), this, SLOT(on_add_clicked()));

    QClipboard *clipboard = QApplication::clipboard();
    if (b == true)
        ui->inptext->setText(clipboard->text());
}

new_task::~new_task()
{
    delete ui;
}

void new_task::on_add_clicked()
{
    QString data = QDate::currentDate().toString("dd-MM-yyyy");
    QString time = QTime::currentTime().toString("hh:mm:ss");
    Notation notation{data,
                     time,
                     ui->inpname->text(),
                     ui->inptext->toPlainText(),
                     ui->inptype->currentText(), 1};

    QFile file{"data.txt"};
       if (!file.open(QIODevice::WriteOnly |QIODevice::Append | QIODevice::Text))
       return;

       QTextStream stream(&file);
       stream<< notation.data()<<"\n"
             << notation.time()<<"\n"
             << notation.name()<<"\n"
             << notation.text()<<"\n"
             << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n"
             << notation.type()<<"\n"
             << notation.availability()<<"\n\n";

   file.close();
   this->close();

   sendData();
}

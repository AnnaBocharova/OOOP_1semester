#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "new_task.h"
#include "notation.h"

#include "ui_new_task.h"

#include <QFile>
#include <QTextStream>
#include <QTableWidgetItem>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Notes");

   if (! RegisterHotKey(HWND(winId()), 0, MOD_ALT | MOD_CONTROL, 0x46))
        QMessageBox::warning(this, "Warning", "Can't register hotkey CTRL+D");

    load_from_file(0);

    ui->tbwNotation_Notes->setColumnWidth(0, 100);
    ui->tbwNotation_Notes->setColumnWidth(1, 75);
    ui->tbwNotation_Notes->setColumnWidth(3, 200);
    ui->tbwNotation_Notes->setColumnWidth(4, 100);

    QTableWidgetItem* item = new QTableWidgetItem("Date");
    ui->tbwNotation_Notes->setHorizontalHeaderItem(0, item);

    item = new QTableWidgetItem("Time");
    ui->tbwNotation_Notes->setHorizontalHeaderItem(1, item);

    item = new QTableWidgetItem("Name");
    ui->tbwNotation_Notes->setHorizontalHeaderItem(2, item);

    item = new QTableWidgetItem("Information");
    ui->tbwNotation_Notes->setHorizontalHeaderItem(3, item);

    item = new QTableWidgetItem("Type");
    ui->tbwNotation_Notes->setHorizontalHeaderItem(4, item);

    item = new QTableWidgetItem("To the archive");
    ui->tbwNotation_Notes->setHorizontalHeaderItem(5, item);

    item = new QTableWidgetItem("Date");
    ui->tbwNotation_Archive->setHorizontalHeaderItem(0, item);

    item = new QTableWidgetItem("Time");
    ui->tbwNotation_Archive->setHorizontalHeaderItem(1, item);

    item = new QTableWidgetItem("Name");
    ui->tbwNotation_Archive->setHorizontalHeaderItem(2, item);

    item = new QTableWidgetItem("Information");
    ui->tbwNotation_Archive->setHorizontalHeaderItem(3, item);

    item = new QTableWidgetItem("Type");
    ui->tbwNotation_Archive->setHorizontalHeaderItem(4, item);

    ui->listWidget->addItem("general");
    ui->listWidget->addItem("work");
    ui->listWidget->addItem("study");
    ui->listWidget->addItem("thought");
    ui->listWidget->addItem("plans");

    ui->listWidget->item(0)->setBackground(Qt::lightGray);
    ui->listWidget->item(1)->setBackground(Qt::white);
    ui->listWidget->item(2)->setBackground(Qt::lightGray);
    ui->listWidget->item(3)->setBackground(Qt::white);
    ui->listWidget->item(4)->setBackground(Qt::lightGray);


    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)),
               this, SLOT(onListMailItemClicked(QListWidgetItem*)));
    connect(ui->listWidget_2, SIGNAL(itemClicked(QListWidgetItem*)),
               this, SLOT(onListMailItemClicked(QListWidgetItem*)));

    keyCtrl_D = new QShortcut(this);
    keyCtrl_D->setKey(Qt::CTRL + Qt::Key_D);
    connect(keyCtrl_D, SIGNAL(activated()), this, SLOT(on_new_task_clicked()));


    ui->tbwNotation_Notes->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tbwNotation_Archive->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onListMailItemClicked(QListWidgetItem* item)
{
    if (item->text() == "general")
        load_from_file(0);

    else if (item->text() == "work")
        load_from_file(1);

    else if (item->text() == "study")
        load_from_file(2);

    else if (item->text() == "thought")
        load_from_file(3);

    else if (item->text() == "plans")
        load_from_file(4);

    ui->listWidget_2->addItem(item->text());
}


void MainWindow::on_new_task_clicked()
{
   new_task *window = new new_task;
   window->show();
   connect(window, SIGNAL(sendData()), this, SLOT(update()));

}

void MainWindow::add_notation_to_table_notes(const Notation &notation)
{
    const int rows = ui->tbwNotation_Notes->rowCount();
    ui->tbwNotation_Notes->setRowCount(rows+1);

    ui->tbwNotation_Notes->setColumnCount(6);

    QTableWidgetItem* item = new QTableWidgetItem(notation.data());
    ui->tbwNotation_Notes->setItem(rows, 0, item);

    item = new QTableWidgetItem(notation.time());
    ui->tbwNotation_Notes->setItem(rows, 1, item);

    item = new QTableWidgetItem(notation.name());
    ui->tbwNotation_Notes->setItem(rows, 2, item);

    item = new QTableWidgetItem(notation.text());
    ui->tbwNotation_Notes->setItem(rows, 3, item);

    item = new QTableWidgetItem(notation.type());
    ui->tbwNotation_Notes->setItem(rows, 4, item);

    add_number_buttons(rows);
}

void MainWindow::add_number_buttons(size_t rows)
{
    QPushButton* button = new QPushButton(QString::number(rows));
    button->setText("Delate");

    connect(button, &QPushButton::clicked, [this, rows] { this->moving_to_archive(rows); });
    ui->tbwNotation_Notes->setCellWidget(rows, 5, button);
}

void MainWindow::moving_to_archive(size_t rows)
{

    Notation current_notation_2 {ui->tbwNotation_Notes->item(rows, 0)->text(),
                                 ui->tbwNotation_Notes->item(rows, 1)->text(),
                                 ui->tbwNotation_Notes->item(rows, 2)->text(),
                                 ui->tbwNotation_Notes->item(rows, 3)->text(),
                                 0,
                                 1};
    QFile file{"data.txt"};
    QFile file2{"data_copy.txt"};
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    if (!file2.open(QIODevice::WriteOnly |QIODevice::Append | QIODevice::Text))
        return;
    QTextStream in(&file);

    QTextStream stream(&file2);
    size_t i = 1;
    int current_field = 0;
    Notation current_notation;
    while (!in.atEnd())
    {
       QString line = in.readLine();
       switch (current_field) {
       case 0:
           current_notation.setData(line);
           break;
       case 1:
           current_notation.setTime(line);
           break;
       case 2:
           current_notation.setName(line);
           break;
       case 3:
       {
           QString str = in.readLine();
           while(str != "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-")
           {
               line.append(str);
               str = in.readLine();
           }
           current_notation.setText(line);
       }
           break;
       case 4:
           current_notation.setType(line);
           break;
       case 5:
            current_notation.setAvailability(line.toInt());
           break;
       }

       switch (current_field) {
       case 0:
           stream<< current_notation.data()<<"\n";
           break;
       case 1:
           stream<< current_notation.time()<<"\n";
           break;
       case 2:
           stream<< current_notation.name()<<"\n";
           break;
       case 3:
           stream<< current_notation.text()<<"\n"
           << "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n";
           break;
       case 4:
           stream<< current_notation.type()<<"\n";
           break;
       case 5:
           if(current_notation_2.data() == current_notation.data() &&
              current_notation_2.time() == current_notation.time() &&
              current_notation_2.name() == current_notation.name() && current_notation.availability())
                        stream<< 0 <<"\n\n";
            else
                stream<< current_notation.availability()<<"\n\n";
           break;
       default:
           current_field = -1;
           i++;
           break;
       }
        current_field++;
    }
    file.close();
    file2.close();

   remove("data.txt");
   rename("data_copy.txt", "data.txt");

   update();
}

void MainWindow::add_notation_to_table_archive(const Notation &notation)

{
    ui->tbwNotation_Archive->setRowCount(0);
    int rows = ui->tbwNotation_Archive->rowCount();
    ui->tbwNotation_Archive->setRowCount(rows+1);

    ui->tbwNotation_Archive->setColumnCount(5);

    QTableWidgetItem* item = new QTableWidgetItem(notation.data());
    ui->tbwNotation_Archive->setItem(rows, 0, item);

    item = new QTableWidgetItem(notation.time());
    ui->tbwNotation_Archive->setItem(rows, 1, item);

    item = new QTableWidgetItem(notation.name());
    ui->tbwNotation_Archive->setItem(rows, 2, item);

    item = new QTableWidgetItem(notation.text());
    ui->tbwNotation_Archive->setItem(rows, 3, item);

    item = new QTableWidgetItem(notation.type());
    ui->tbwNotation_Archive->setItem(rows, 4, item);
}

void MainWindow::load_from_file(int i)
{
    QFile file{"data.txt"};
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

  ui->tbwNotation_Notes->clearContents();
  ui->tbwNotation_Notes->setRowCount(0);
  ui->tbwNotation_Archive->clearContents();
  ui->tbwNotation_Archive->setRowCount(0);

    QTextStream in(&file);
    int current_field = 0;
    Notation current_notation;
    while (!in.atEnd())
    {
       QString line = in.readLine();
       qDebug() << line;
       switch (current_field) {
       case 0:
           current_notation.setData(line);
           break;
       case 1:
           current_notation.setTime(line);
           break;
       case 2:
           current_notation.setName(line);
           break;
       case 3:
       {
           QString str = in.readLine();
           while(str != "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-")
           {
               line.append(str);
               str = in.readLine();
           }
           current_notation.setText(line);
       }
           break;
       case 4:
           current_notation.setType(line);
           break;
       case 5:
            current_notation.setAvailability(line.toInt());
           break;
       case 6:
           current_field = -1;
           if (i == 0 )
           {
               if (current_notation.availability())
                   add_notation_to_table_notes(current_notation);
                else
                   add_notation_to_table_archive(current_notation);
           }
           else if (i == 1 && current_notation.type() == "work")
           {
               if (current_notation.availability())
                   add_notation_to_table_notes(current_notation);
                else
                   add_notation_to_table_archive(current_notation);
           }
           else if (i == 2 && current_notation.type() == "study")
           {
               if (current_notation.availability())
                   add_notation_to_table_notes(current_notation);
                else
                   add_notation_to_table_archive(current_notation);
           }
           else if (i == 3 && current_notation.type() == "thought")
           {
               if (current_notation.availability())
                   add_notation_to_table_notes(current_notation);
                else
                   add_notation_to_table_archive(current_notation);
           }
           else if (i == 4 && current_notation.type() == "plans")
           {
               if (current_notation.availability())
                   add_notation_to_table_notes(current_notation);
                else
                   add_notation_to_table_archive(current_notation);
           }
           break;
       }
       current_field++;
    }
    file.close();
}

void MainWindow::update()
{
     load_from_file(0);
}

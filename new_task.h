#ifndef NEW_TASK_H
#define NEW_TASK_H

#include "mainwindow.h"

#include <QMainWindow>
#include <QApplication>
#include <QShortcut>

#include <QDebug>

namespace Ui {
class new_task;
}

class new_task : public QMainWindow
{
    Q_OBJECT

public:
    explicit new_task(QWidget *parent = nullptr, bool b = false);
    ~new_task();
signals:
   void sendData();

private slots:

    void on_add_clicked();

private:
    Ui::new_task *ui;
    QShortcut  *keyEnter;
};

#endif // NEW_TASK_H

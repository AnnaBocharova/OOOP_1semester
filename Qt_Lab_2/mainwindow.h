#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "notation.h"
#include <QMainWindow>
#include <QShortcut>
#include <QListWidget>

#include "windows.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);

public slots:
    void update();

private slots:
    void add_number_buttons(size_t rows);
    void moving_to_archive(size_t rows);
    void on_new_task_clicked();


    void onListMailItemClicked(QListWidgetItem* item);


private:
    Ui::MainWindow *ui;
    QShortcut  *keyCtrl_D;
    void add_notation_to_table_notes(const Notation& notation);
    void add_notation_to_table_archive(const Notation& notation);
    void load_from_file(int i);
};
#endif // MAINWINDOW_H

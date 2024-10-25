// mainwindow.h

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QHBoxLayout>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addItemToList1();
    void editItemInList1();
    void deleteItemFromList1();
    void addItemToList2();
    void editItemInList2();
    void deleteItemFromList2();
    void saveList(QListWidget *listWidget);
    void loadList(QListWidget *listWidget);
    void onItemDoubleClicked(QListWidgetItem *item);
    void onItemChanged(QListWidgetItem *item);

private:
    QListWidget *listWidget1;
    QListWidget *listWidget2;
    QPushButton *addButton1;
    QPushButton *editButton1;
    QPushButton *deleteButton1;
    QPushButton *saveButton1;
    QPushButton *loadButton1;
    QPushButton *addButton2;
    QPushButton *editButton2;
    QPushButton *deleteButton2;
    QPushButton *saveButton2;
    QPushButton *loadButton2;

    void setupList(QListWidget *listWidget);
    void setupButtons();
};

#endif // MAINWINDOW_H

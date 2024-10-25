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

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addItem();
    void editItem();
    void deleteItem();
    void saveList();
    void loadList();
    void onItemDoubleClicked(QListWidgetItem *item);
    void onItemChanged(QListWidgetItem *item);

private:
    QListWidget *listWidget;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QPushButton *saveButton;
    QPushButton *loadButton;
};

#endif // MAINWINDOW_H

// mainwindow.cpp

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    listWidget1 = new QListWidget(this);
    listWidget2 = new QListWidget(this);

    // Устанавливаем настройки для drag-and-drop
    setupList(listWidget1);
    setupList(listWidget2);

    // Инициализация кнопок и привязка сигналов
    setupButtons();

    // Макет кнопок и списков
    QVBoxLayout *layout1 = new QVBoxLayout;
    layout1->addWidget(listWidget1);
    layout1->addWidget(addButton1);
    layout1->addWidget(editButton1);
    layout1->addWidget(deleteButton1);
    layout1->addWidget(saveButton1);
    layout1->addWidget(loadButton1);

    QVBoxLayout *layout2 = new QVBoxLayout;
    layout2->addWidget(listWidget2);
    layout2->addWidget(addButton2);
    layout2->addWidget(editButton2);
    layout2->addWidget(deleteButton2);
    layout2->addWidget(saveButton2);
    layout2->addWidget(loadButton2);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(layout1);
    mainLayout->addLayout(layout2);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    setWindowTitle("Списки с Drag-and-Drop");
}

MainWindow::~MainWindow() {}

void MainWindow::setupList(QListWidget *listWidget) {
    listWidget->setDragEnabled(true);
    listWidget->setDropIndicatorShown(true);
    listWidget->setAcceptDrops(true);
    listWidget->setDefaultDropAction(Qt::MoveAction);

    connect(listWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::onItemDoubleClicked);
    connect(listWidget, &QListWidget::itemChanged, this, &MainWindow::onItemChanged);
}

void MainWindow::setupButtons() {
    // Кнопки для списка 1
    addButton1 = new QPushButton("Добавить в список 1", this);
    editButton1 = new QPushButton("Редактировать в списке 1", this);
    deleteButton1 = new QPushButton("Удалить из списка 1", this);
    saveButton1 = new QPushButton("Сохранить список 1", this);
    loadButton1 = new QPushButton("Загрузить список 1", this);

    connect(addButton1, &QPushButton::clicked, this, &MainWindow::addItemToList1);
    connect(editButton1, &QPushButton::clicked, this, &MainWindow::editItemInList1);
    connect(deleteButton1, &QPushButton::clicked, this, &MainWindow::deleteItemFromList1);
    connect(saveButton1, &QPushButton::clicked, [this](){ saveList(listWidget1); });
    connect(loadButton1, &QPushButton::clicked, [this](){ loadList(listWidget1); });

    // Кнопки для списка 2
    addButton2 = new QPushButton("Добавить в список 2", this);
    editButton2 = new QPushButton("Редактировать в списке 2", this);
    deleteButton2 = new QPushButton("Удалить из списка 2", this);
    saveButton2 = new QPushButton("Сохранить список 2", this);
    loadButton2 = new QPushButton("Загрузить список 2", this);

    connect(addButton2, &QPushButton::clicked, this, &MainWindow::addItemToList2);
    connect(editButton2, &QPushButton::clicked, this, &MainWindow::editItemInList2);
    connect(deleteButton2, &QPushButton::clicked, this, &MainWindow::deleteItemFromList2);
    connect(saveButton2, &QPushButton::clicked, [this](){ saveList(listWidget2); });
    connect(loadButton2, &QPushButton::clicked, [this](){ loadList(listWidget2); });
}

void MainWindow::addItemToList1() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Добавить элемент в список 1"),
                                         tr("Текст:"), QLineEdit::Normal,
                                         QString(), &ok);
    if (ok && !text.isEmpty()) {
        listWidget1->addItem(text);
    }
}

void MainWindow::editItemInList1() {
    QListWidgetItem *currentItem = listWidget1->currentItem();
    if (currentItem) {
        bool ok;
        QString text = QInputDialog::getText(this, tr("Редактировать элемент в списке 1"),
                                             tr("Текст:"), QLineEdit::Normal,
                                             currentItem->text(), &ok);
        if (ok && !text.isEmpty()) {
            currentItem->setText(text);
        }
    }
}

void MainWindow::deleteItemFromList1() {
    delete listWidget1->currentItem();
}

void MainWindow::addItemToList2() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Добавить элемент в список 2"),
                                         tr("Текст:"), QLineEdit::Normal,
                                         QString(), &ok);
    if (ok && !text.isEmpty()) {
        listWidget2->addItem(text);
    }
}

void MainWindow::editItemInList2() {
    QListWidgetItem *currentItem = listWidget2->currentItem();
    if (currentItem) {
        bool ok;
        QString text = QInputDialog::getText(this, tr("Редактировать элемент в списке 2"),
                                             tr("Текст:"), QLineEdit::Normal,
                                             currentItem->text(), &ok);
        if (ok && !text.isEmpty()) {
            currentItem->setText(text);
        }
    }
}

void MainWindow::deleteItemFromList2() {
    delete listWidget2->currentItem();
}

void MainWindow::saveList(QListWidget *listWidget) {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить список"),
                                                    "", tr("Text Files (*.txt);;All Files (*)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            for (int i = 0; i < listWidget->count(); ++i) {
                out << listWidget->item(i)->text() << "\n";
            }
        }
    }
}

void MainWindow::loadList(QListWidget *listWidget) {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Загрузить список"),
                                                    "", tr("Text Files (*.txt);;All Files (*)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            listWidget->clear();
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                listWidget->addItem(line);
            }
        }
    }
}

void MainWindow::onItemDoubleClicked(QListWidgetItem *item) {
    editItemInList1();
}

void MainWindow::onItemChanged(QListWidgetItem *item) {
    if (item->text() != item->data(Qt::UserRole).toString()) {
        QFont font = item->font();
        font.setItalic(true);
        item->setFont(font);
        item->setData(Qt::UserRole, item->text());
    }
}

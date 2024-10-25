#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    listWidget = new QListWidget(this);
    listWidget->setDragEnabled(true);
    listWidget->setDropIndicatorShown(true);
    listWidget->setAcceptDrops(true);

    // Устанавливаем типы поддержки для перетаскивания
    listWidget->setDefaultDropAction(Qt::MoveAction);

    // Connect signals for double-click editing and item change
    connect(listWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::onItemDoubleClicked);
    connect(listWidget, &QListWidget::itemChanged, this, &MainWindow::onItemChanged);

    addButton = new QPushButton("Добавить", this);
    editButton = new QPushButton("Редактировать", this);
    deleteButton = new QPushButton("Удалить", this);
    saveButton = new QPushButton("Сохранить", this);
    loadButton = new QPushButton("Загрузить", this);

    connect(addButton, &QPushButton::clicked, this, &MainWindow::addItem);
    connect(editButton, &QPushButton::clicked, this, &MainWindow::editItem);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteItem);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveList);
    connect(loadButton, &QPushButton::clicked, this, &MainWindow::loadList);

    // Layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(listWidget);
    layout->addWidget(addButton);
    layout->addWidget(editButton);
    layout->addWidget(deleteButton);
    layout->addWidget(saveButton);
    layout->addWidget(loadButton);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);
    setWindowTitle("Список");
}

MainWindow::~MainWindow() {}

void MainWindow::addItem() {
    bool ok;
    QString text = QInputDialog::getText(this, tr("Добавить элемент"),
                                         tr("Текст:"), QLineEdit::Normal,
                                         QString(), &ok);
    if (ok && !text.isEmpty()) {
        listWidget->addItem(text);
    }
}

void MainWindow::editItem() {
    QListWidgetItem *currentItem = listWidget->currentItem();
    if (currentItem) {
        bool ok;
        QString text = QInputDialog::getText(this, tr("Редактировать элемент"),
                                             tr("Текст:"), QLineEdit::Normal,
                                             currentItem->text(), &ok);
        if (ok && !text.isEmpty()) {
            currentItem->setText(text);
        }
    }
}

void MainWindow::deleteItem() {
    delete listWidget->currentItem();
}

void MainWindow::saveList() {
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

void MainWindow::loadList() {
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
    editItem();
}

void MainWindow::onItemChanged(QListWidgetItem *item) {
    // Если текст элемента изменился
    if (item->text() != item->data(Qt::UserRole).toString()) {
        // Устанавливаем курсивный шрифт
        QFont font = item->font(); // Получаем текущий шрифт
        font.setItalic(true);       // Устанавливаем курсив
        item->setFont(font);        // Применяем шрифт к элементу
        item->setData(Qt::UserRole, item->text()); // Сохраняем текст для сравнения
    }
}

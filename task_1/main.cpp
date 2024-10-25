#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFont>
#include <QBrush>
#include <QDebug>

bool isUpperCase(const QString& str) {
    for (auto ch : str) {
        if (ch.isLetter() && !ch.isUpper()) {
            return false;
        }
    }
    return true;
}

bool isNegativeNumber(const QString& str) {
    bool ok;
    double value = str.toDouble(&ok);
    qDebug() << "Checking string:" << str << "Value:" << value << "isNegative:" << (ok && value < 0);
    return ok && value < 0;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setStyle("Fusion"); // Установите стиль приложения

    QWidget window;
    window.setWindowTitle("Список из файла");

    QVBoxLayout *layout = new QVBoxLayout(&window);
    QListWidget *listWidget = new QListWidget(&window);

    // Диалог открытия файла
    QString fileName = QFileDialog::getOpenFileName(&window, "Открыть текстовый файл", "", "Text Files (*.txt)");
    if (fileName.isEmpty()) {
        QMessageBox::warning(&window, "Ошибка", "Не выбран файл!");
        return -1;
    }

    // Чтение файла
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(&window, "Ошибка", "Не удалось открыть файл!");
        return -1;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QListWidgetItem *item = new QListWidgetItem(line);

        // Если строка капсом
        if (isUpperCase(line)) {
            QFont font = item->font();
            font.setBold(true);
            font.setPointSize(14); // Увеличиваем размер шрифта
            item->setFont(font);
        }

        // Если строка содержит отрицательное число
        if (isNegativeNumber(line)) {
            item->setForeground(QBrush(Qt::red)); // Устанавливаем кисть как цвет текста
            qDebug() << "Setting red color for:" << line; // Отладочная информация
        }

        listWidget->addItem(item);
    }

    layout->addWidget(listWidget);
    window.setLayout(layout);
    window.resize(400, 300);
    listWidget->update(); // Обновляем виджет
    window.show();

    return app.exec();
}

//
// Created by Сергей on 02.06.2024.
//

#ifndef AI_QT_APP_LOG_H
#define AI_QT_APP_LOG_H


#include <QString>

class Logger {
public:
    // Конструктор, принимающий путь к лог-файлу
    Logger(const QString& filePath);

    // Метод для записи сообщения в лог-файл
    void writeToLog(const QString& message);

private:
    QString logFilePath; // Путь к лог-файлу
};

#endif // LOGGER_H

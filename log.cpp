//
// Created by Сергей on 02.06.2024.
//
#include "log.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>

// Конструктор класса Logger
Logger::Logger(const QString& filePath) : logFilePath(filePath) {}

// Метод для записи сообщения в лог-файл
void Logger::writeToLog(const QString& message) {
    QFile file(logFilePath);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << " - " << message << "\n";
    }
}

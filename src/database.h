#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDebug>

#include "history.h"

/*!
    \brief Інтерфейс БД

    Даж можливість звертатися до БД
*/

class Database
{
private:
    QSqlDatabase db;

    /*!
        \brief Створення БД

        \return чи існує БД
    */
    bool createDB();

    /*!
        \brief Відкрити БД

        Якщо виникла помилка - виводить у консоль
    */
    void open();

    /*!
        \brief Виконати sqlite запит

        Якщо виникла помилка - виводить у консоль

        \return чи успішно виконалався запит
    */
    bool mod_exec(QSqlQuery *query);
public:
    Database();

    /*!
        \brief Додати скріншот у БД

        \param [in] screenshot_path шлях до скріншоту
        \param [in] simular_procent % того на скільки схожий з попереднім
        \param [in] md5 хеш скріншоту

        \return id новостореного скріншоту. Якщо 0, то помилка
    */
    int appendScreenshot(QString screenshot_path, double simular_procent, QString md5);

    /*!
        \brief Отримати усі скріншоти з БД
    */
    std::vector<HistoryItem*> getScreenshots();

    /*!
        \brief Отримати шлях до останнього скрішоту
    */
    QString getLastScreenshotPath();
};

#endif // DATABASE_H

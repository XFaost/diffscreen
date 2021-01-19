#ifndef BACKEND_H
#define BACKEND_H


#include <QDebug>
#include <QTimer>
#include <QThread>

#include "history.h"
#include "screenshotworker.h"
#include "database.h"
#include "workerthread.h"

/*!
    \brief Головний клас

    Цей клас керує усією програмою
*/

class Backend : public QObject
{
    Q_OBJECT

private:
    History *history;
    Database *database;
    QTimer *timer;
    QThread workerThread;

private slots:

    /*!
        \brief Створення скрішоту по сигналу

        Кожну хвилину її викликає таймер, щоб зробити скріншот, порівняти його з попереднім, вивести у інтерфейс та записати у БД
    */
    void cheese();

public:
    Backend(QObject *parent = nullptr);

public slots:

    /*!
        \brief Отримати модель з історією скріншотів

        Викликається з інтерфейсу для заповнення Grid View
    */
    History *getHistoryModel();

    /*!
        \brief Керування таймером

        Викликається з інтерфейсу. Відповідає за запуск/зупинку таймера. Назад повертається текст, який має присвоїти собі кнопка
    */
    QString pressPause();

    /*!
        \brief Виведення скрішоту у інтерфейс та запис у БД

        Його викликає WorkerThread::resultReady, тобто коли завершиться процес порівнянн скріншотів у потоці

        \param [in] simular_procent % того на скільки схожі скріншоти
        \param [in] path шлях до першого скріншоту
        \param [in] md5 хеш першого скріншоту
    */
    void handleResults(const double &simular_procent, const QString path, const QString md5);
};

#endif // BACKEND_H

#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>

#include "screenshotworker.h"

/*!
    \brief Клас для порівняння скріншотів у окремому потоці
*/

class WorkerThread : public QThread
{
    Q_OBJECT

    QString first_path, second_path, md5;

public:
    /*!
        \brief Задати шлях до скріншотів

        \param [in] first_path шлях до першого скріншоту
        \param [in] second_path шлях до другого скріншоту
        \param [in] md5 хеш першого скріншоту
    */
    WorkerThread(QString first_path, QString second_path, QString md5);

    /*!
        \brief Запустити процес порівняння
    */
    void run() override;
signals:
    /*!
        \brief Сигнал, який виникає, коли порівняння скріншотів завершене

        \param [in] simular_procent % того на скільки схожі скріншоти
        \param [in] path шлях до першого скріншоту
        \param [in] md5 хеш першого скріншоту
    */
    void resultReady(const double &simular_procent, const QString path, const QString md5);
};

#endif // WORKERTHREAD_H

#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>

#include "screenshotworker.h"

class WorkerThread : public QThread
{
    Q_OBJECT

    QString first_path, second_path, md5;

public:
    WorkerThread(QString first_path, QString second_path, QString md5);

    void run() override;
signals:
    void resultReady(const double &simular_procent, const QString path, const QString md5);
};

#endif // WORKERTHREAD_H

#ifndef BACKEND_H
#define BACKEND_H


#include <QDebug>
#include <QTimer>
#include <QThread>

#include "history.h"
#include "screenshotworker.h"
#include "database.h"
#include "workerthread.h"

class Backend : public QObject
{
    Q_OBJECT

private:
    History *history;
    Database *database;
    QTimer *timer;
    QThread workerThread;

private slots:
    void cheese();

public:
    Backend(QObject *parent = nullptr);

public slots:

    History *getHistoryModel();
    QString pressPause();
    void handleResults(const double &simular_procent, const QString path, const QString md5);
};

#endif // BACKEND_H

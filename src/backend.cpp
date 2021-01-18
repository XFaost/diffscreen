#include "backend.h"


void Backend::cheese()
{
    QString path, md5;
    ScreenshotWorker::takeScreenshot(&path, &md5);

    WorkerThread *workerThread = new WorkerThread(path, database->getLastScreenshotPath(), md5);
    connect(workerThread, &WorkerThread::resultReady, this, &Backend::handleResults);
    connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
    workerThread->start();
}

Backend::Backend(QObject *parent)
{
    Q_UNUSED(parent)
    database = new Database();
    history = new History();
    history->setList(database->getScreenshots());
    timer = new QTimer();
    timer->setInterval(60000);
    connect(timer, SIGNAL(timeout()), this, SLOT(cheese()));
}

History *Backend::getHistoryModel()
{
    return history;
}

QString Backend::pressPause() {

    if(timer->isActive()) {
        timer->stop();
        return "Start";
    }
    else {
        timer->start();
        return "Stop";
    }
}

void Backend::handleResults(const double &simular_procent, const QString path, const QString md5)
{
    int id = database->appendScreenshot(path, md5);
    database->setSimularProcent(id, simular_procent);
    history->append(id, path, simular_procent, md5);
}



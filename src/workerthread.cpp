#include "workerthread.h"


WorkerThread::WorkerThread(QString first_path, QString second_path, QString md5)
{
    this->first_path = first_path;
    this->second_path = second_path;
    this->md5 = md5;
}

void WorkerThread::run()
{
    emit resultReady(ScreenshotWorker::compareScreenshots(first_path, second_path), first_path, md5);
}

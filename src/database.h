#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDebug>

#include "history.h"


class Database
{
private:
    QSqlDatabase db;

    bool createDB();
    void open();
    bool mod_exec(QSqlQuery *query);
public:
    Database();

    int appendScreenshot(QString screenshot_path, QString md5, double simular_procent = NULL);
    bool setSimularProcent(int id, double simular_procent);
    std::vector<HistoryItem*> getScreenshots();
    QString getLastScreenshotPath();
};

#endif // DATABASE_H

#include "database.h"

bool Database::createDB()
{
    open();
    QSqlQuery query;
    bool result = query.exec("create table Screenshots (\
                                id INTEGER PRIMARY KEY AUTOINCREMENT, \
                                screenshot_path varchar(50) NOT NULL, \
                                simular_procent REAL NOT NULL, \
                                md5 varchar(32) NOT NULL)");

    db.close();
    return result;
}

void Database::open()
{
    if (!db.open())
        qDebug() << "!db.open()";
}

bool Database::mod_exec(QSqlQuery *query)
{
    bool result = query->exec();
    if(!result)
        qDebug() << "SqLite error:" << query->lastError().text();
    return result;
}

Database::Database()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.sqlite3");
    createDB();
}

int Database::appendScreenshot(QString screenshot_path, double simular_procent, QString md5)
{
    open();

    int result = 0;

    QSqlQuery query;
    query.prepare("INSERT INTO Screenshots(screenshot_path, simular_procent, md5) \
                    VALUES(:screenshot_path, :simular_procent, :md5)");
    query.bindValue(":screenshot_path", screenshot_path);
    query.bindValue(":simular_procent", simular_procent);
    query.bindValue(":md5", md5);
    mod_exec(&query);

    result = query.lastInsertId().toInt();

    db.close();

    return result;
}

std::vector<HistoryItem*> Database::getScreenshots()
{
    open();

    std::vector<HistoryItem*> list;

    QSqlQuery query;
    query.prepare("SELECT * FROM Screenshots ORDER BY id DESC");

    if(mod_exec(&query))
    {
        while (query.next()) {
            list.push_back(new HistoryItem(query.value(0).toInt(), query.value(1).toString(), query.value(2).toDouble(), query.value(3).toString()));
        }
    }

    db.close();

    return list;
}

QString Database::getLastScreenshotPath()
{
    open();

    QString result;

    QSqlQuery query;
    query.prepare("SELECT screenshot_path FROM Screenshots ORDER BY id DESC LIMIT 1");

    if(mod_exec(&query) && query.first())
        result = query.value(0).toString();

    db.close();

    return result;
}

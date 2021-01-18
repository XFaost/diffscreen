#ifndef SCREENSHOTWORKER_H
#define SCREENSHOTWORKER_H

#include <QObject>
#include <QImage>
#include <QDir>
#include <QCryptographicHash>
#include <QScreen>
#include <QDebug>
#include <QGuiApplication>
#include <QPixmap>

#include <windows.h>
#include <gdiplus.h>
#include <ctime>



using namespace Gdiplus;

class ScreenshotWorker : public QObject
{
    Q_OBJECT

public:
    ScreenshotWorker();

public slots:
    static void takeScreenshot(QString *path, QString *md5);
    static double compareScreenshots(QString first_path, QString second_path);

private:

    static QString generateMD5(QString path);
    static QString createScreenshotName();
    static bool checkScreenshotsDirectory();
    static QString getScreenshotsDirectoryName();
};

#endif // SCREENSHOTWORKER_H

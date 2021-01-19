#include "screenshotworker.h"

ScreenshotWorker::ScreenshotWorker()
{

}


void ScreenshotWorker::takeScreenshot(QString *path, QString *md5)
{
    if(!checkScreenshotsDirectory())
    {
        qDebug() << "error: screenshot directory cannot be created";
        return;
    }

    *path = createScreenshotPath();

    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap screenshot = screen->grabWindow(0);
    screenshot.save(*path,"PNG",100);
    *md5 = generateMD5(*path);
}

QString ScreenshotWorker::generateMD5(QString path)
{
    QFile f(path);
    if (f.open(QFile::ReadOnly))
    {
        QCryptographicHash hash(QCryptographicHash::Md5);
        if (hash.addData(&f))
            return hash.result().toHex();
    }
    return QString();
}

double ScreenshotWorker::compareScreenshots(QString first_path, QString second_path)
{
    if(first_path == "" || second_path == "")
    {
        qDebug() << "ScreenshotWorker::compareScreenshots() | Один із параметрів пустий" ;
        return -1;    }


    QImage firstImage (first_path);
    QImage secondImage (second_path);
    double totaldiff = 0.0;
    int h = firstImage.height();
    int w = firstImage.width();
    int hsecond = secondImage.height();
    int wsecond = secondImage.width();
    if (w != wsecond || h != hsecond)
    {
        qDebug() << "ScreenshotWorker::compareScreenshots() | Помилка, картинки повинні мати однакові розміри!" ;
        return -2;
    }
    for (int y = 0; y<h; y++)
    {
        uint *firstLine = ( uint* )firstImage.scanLine(y);
        uint *secondLine = ( uint* )secondImage.scanLine(y);

        for (int x = 0; x<w; x++)
        {

            uint pixelFirst = firstLine[x];
            int rFirst = qRed(pixelFirst);
            int gFirst = qGreen(pixelFirst);
            int bFirst = qBlue(pixelFirst);
            uint pixelSecond = secondLine[x];
            int rSecond = qRed(pixelSecond);
            int gSecond = qGreen(pixelSecond);
            int bSecond = qBlue(pixelSecond);
            totaldiff += std::abs(rFirst-rSecond)/255.0;
            totaldiff += std::abs(gFirst-gSecond)/255.0;
            totaldiff += std::abs(bFirst-bSecond)/255.0;
        }
    }

    double result = 100 - (totaldiff * 100)/(w * h * 3);

    return trunc(result * 100.00) / 100.00;
}

QString ScreenshotWorker::createScreenshotPath()
{
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);

    return getScreenshotsDirectoryName()+"//" + QString::number(now->tm_mday) + "-" + QString::number(now->tm_mon+1) + "-" + QString::number(now->tm_year + 1900) + "_" + QString::number(now->tm_hour) + "-" + QString::number(now->tm_min) + "-" + QString::number(now->tm_sec) + ".png";
}

bool ScreenshotWorker::checkScreenshotsDirectory()
{
    if (!QDir(getScreenshotsDirectoryName()).exists())
        return QDir().mkdir(getScreenshotsDirectoryName());
    return true;
}

QString ScreenshotWorker::getScreenshotsDirectoryName()
{
    return "screenshots";
}

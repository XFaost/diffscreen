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

#include <ctime>


/*!
    \brief Роботоа з скріншотами
*/

class ScreenshotWorker : public QObject
{
    Q_OBJECT

public:
    ScreenshotWorker();

public slots:

    /*!
        \brief Створити скріншот

        Створює та зберігає скріншот у директорію

        \param [out] path шлях до скріншоту
        \param [out] md5 хеш скріншоту
    */
    static void takeScreenshot(QString *path, QString *md5);

    /*!
        \brief Порівняння скріншотів

        \warning Виконується у потоці

        \param [in] first_path шлях до першого скріншоту
        \param [in] second_path шлях до другого скріншоту

        \return % подібності \
            -1 - один із параметрів пустий \
            -2 - картинки не однакового розміру
    */
    static double compareScreenshots(QString first_path, QString second_path);

private:

    /*!
        \brief Згенерувати хеш скріншоту

        \param [in] first_path шлях до скріншоту
    */
    static QString generateMD5(QString path);

    /*!
        \brief Створити шлях для скріншоту

        Створити шлях для скріншоту у форматі <день>-<місяць>-<рік>_<год>-<хв>-<сек>.png
    */
    static QString createScreenshotPath();

    /*!
        \brief Перевірка директорії для скріншотів

        Перевіряє чи існує. Якщо ні - створити
    */
    static bool checkScreenshotsDirectory();

    /*!
        \brief Отримати назву директорії для скріншотів
    */
    static QString getScreenshotsDirectoryName();
};

#endif // SCREENSHOTWORKER_H

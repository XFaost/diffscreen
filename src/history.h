#ifndef HISTORY_H
#define HISTORY_H

#include <QAbstractListModel>
#include <vector>
#include <QDebug>

/*!
    \brief Елемент списку History

    Зберігає у собі усі дані скріншоту з БД
*/

class HistoryItem : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int id READ getID CONSTANT)
    Q_PROPERTY(QString screenshot_path READ getScreenshotPath CONSTANT)
    Q_PROPERTY(double simular_procent READ getSimularProcent CONSTANT)
    Q_PROPERTY(QString md5 READ getMD5 CONSTANT)

    size_t id;
    QString screenshot_path;
    double simular_procent;
    QString md5;

public:
    HistoryItem(
            const size_t id,
            const QString screenshot_path,
            const double simular_procent,
            const QString md5) {

        this->id = id;
        this->screenshot_path = screenshot_path;
        this->simular_procent = simular_procent;
        this->md5 = md5;
    }

public:
    size_t getID() {
        return id;
    }
    QString getScreenshotPath() {
        return screenshot_path;
    }
    double getSimularProcent() {
        return simular_procent;
    }
    void setSimularProcent(double simular_procent) {
        this->simular_procent = simular_procent;
    }
    QString getMD5() {
        return md5;
    }
};

Q_DECLARE_METATYPE(HistoryItem*)



/*!
    \brief Grid View QML модель, відображає історію скріншотів

    У цій моделі елементом списку є клас HistoryItem
*/

class History : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit History(QObject* parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /*!
        \brief Додати скріншот у історію

        Додає на початок списку

        \param [in] id шлях ідентифікатор у БД
        \param [in] screenshot_path шлях до скріншоту
        \param [in] simular_procent % того на скільки схожий з попереднім
        \param [in] md5 хеш скріншоту
    */
    void append(const size_t id, const QString screenshot_path, const double simular_procent, const QString md5);

    /*!
        \brief Ініціалізація спику

        \param [in] m_list список скріншотів
    */
    void setList(std::vector<HistoryItem*> m_list);

public slots:

    /*!
        \brief Отримати елемент списку

        \param [in] index індекс елементу у списку
    */
    HistoryItem *get(int index);

private:
    std::vector<HistoryItem*> m_list;
};



#endif // HISTORY_H

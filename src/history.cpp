#include "history.h"

History::History(QObject *parent)
    : QAbstractListModel {parent}
{

}

int History::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_list.size();
}

QVariant History::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || role != Qt::DisplayRole)
        return {};

    const int rowIndex{index.row()};

    return QVariant::fromValue(m_list[rowIndex]);
}

void History::append(const size_t id, const QString screenshot_path, const double simular_procent, const QString md5)
{
    emit beginResetModel();
    m_list.insert(m_list.begin(), new HistoryItem(id, screenshot_path, simular_procent, md5));
    emit endResetModel();
}

void History::setList(std::vector<HistoryItem *> m_list)
{
    emit beginResetModel();
    this->m_list = m_list;
    emit beginResetModel();
}

HistoryItem *History::get(int index)
{
    if (index < 0 || index >= m_list.size())
        return nullptr;

    return m_list[index];
}


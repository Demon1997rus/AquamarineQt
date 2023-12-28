#include "targettablemodel.h"

#include <QDebug>

TargetTableModel::TargetTableModel(QObject* parent)
  : QAbstractTableModel(parent), m_data(TargetRepository::instance())
{
    m_headers << "№ цели";
    m_headers << "Дистанция до цели\nот центра круга (м)";
    m_headers << "Пеленг\nотносительно\nцентра круга\n(градусы)";
    connect(&m_data, &TargetRepository::updateRepository, this, &TargetTableModel::updateModel);
}

int TargetTableModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 9;
}

int TargetTableModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_headers.size();
}

QVariant TargetTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
    {
        return QVariant();
    }

    if (index.row() < m_data.size())
    {
        switch (index.column())
        {
            case 0:
                return m_data.at(index.row()).getId();
            case 1:
                return m_data.at(index.row()).getDistance();
            case 2:
                return m_data.at(index.row()).getBearing();
        }
    }
    return QVariant();
}

QVariant TargetTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    if (orientation == Qt::Horizontal)
    {
        return m_headers.at(section);
    }
    return QVariant();
}

/*!
 * \brief TargetTableModel::updateModel - обновление модели
 */
void TargetTableModel::updateModel()
{
    QModelIndex topLeft = index(0, 0);
    QModelIndex bottomRight = index(rowCount(QModelIndex()) - 1, columnCount(QModelIndex()) - 1);
    if (topLeft.isValid() && bottomRight.isValid())
    {
        emit dataChanged(topLeft, bottomRight);
    }
}

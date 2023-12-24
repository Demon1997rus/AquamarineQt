#include "targettablemodel.h"

TargetTableModel::TargetTableModel(QObject* parent) : QAbstractTableModel(parent)
{
    headers << "№ цели";
    headers << "Дистанция до цели от центра круга (м)";
    headers << "Пеленг относительно центра круга (градусы)";
}

int TargetTableModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 9;
}

int TargetTableModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return headers.size();
}

QVariant TargetTableModel::data(const QModelIndex& index, int role) const { return QVariant(); }

QVariant TargetTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return headers.at(section);
    }
    return QVariant();
}

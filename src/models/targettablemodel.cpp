#include "targettablemodel.h"

#include "info/targetrepository.h"

#include <QDebug>

#define DATA TargetRepository::instance()

TargetTableModel::TargetTableModel(QObject* parent) : QAbstractTableModel(parent)
{
    headers << "№ цели";
    headers << "Дистанция до цели\nот центра круга (м)";
    headers << "Пеленг\nотносительно\nцентра круга\n(градусы)";
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

QVariant TargetTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
    {
        return QVariant();
    }

    if (index.row() < DATA.size())
    {
        switch (index.column())
        {
            case 0:
                return DATA.at(index.row()).getId();
            case 1:
                return DATA.at(index.row()).getDistance();
            case 2:
                return DATA.at(index.row()).getBearing();
        }
    }
    return QVariant();
}

QVariant TargetTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return headers.at(section);
    }
    return QVariant();
}
#undef DATA

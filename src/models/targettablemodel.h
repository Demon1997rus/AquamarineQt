#ifndef TARGETTABLEMODEL_H
#define TARGETTABLEMODEL_H

#include <QAbstractTableModel>

/*!
 * \brief The TargetTableModel class - табличная модель для отображения данных по целям
 */
class TargetTableModel : public QAbstractTableModel
{
public:
    explicit TargetTableModel(QObject* parent = Q_NULLPTR);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    QStringList headers;
};

#endif  // TARGETTABLEMODEL_H

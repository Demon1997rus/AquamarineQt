#ifndef TARGETTABLEMODEL_H
#define TARGETTABLEMODEL_H

#include <QAbstractTableModel>

#include "info/targetrepository.h"

/*!
 * \brief The TargetTableModel class - табличная модель для отображения данных по целям
 */
class TargetTableModel : public QAbstractTableModel
{
public:
    explicit TargetTableModel(QObject* parent = Q_NULLPTR);

public:
    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

public slots:
    void updateModel();

private:
    const TargetRepository& m_data;
    QStringList m_headers;
};

#endif  // TARGETTABLEMODEL_H

#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QFrame>
#include <QTableView>
#include <QGridLayout>
#include <QPushButton>

#include "models/targettablemodel.h"

class ControlPanel : public QFrame
{
    Q_OBJECT
public:
    explicit ControlPanel(QWidget* parent = Q_NULLPTR);

signals:
    void startImitation();
    void stopImitation();

private:
    void initWidgets();
    void controlPanelSettings();
    void setupLayout();
    void initializingConnections();

private:
    QGridLayout* mainLayout = Q_NULLPTR;
    QHBoxLayout* horizontalLayout = Q_NULLPTR;
    QTableView* tableView = Q_NULLPTR;
    TargetTableModel* model = Q_NULLPTR;
    QPushButton* pbImitation = Q_NULLPTR;
    QPushButton* pbPause = Q_NULLPTR;
};

#endif  // CONTROLPANEL_H

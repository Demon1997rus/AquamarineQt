#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QFrame>
#include <QTableView>
#include <QGridLayout>

#include "models/targettablemodel.h"

class ControlPanel : public QFrame
{
    Q_OBJECT
public:
    explicit ControlPanel(QWidget* parent = Q_NULLPTR);

private:
    void initWidgets();
    void controlPanelSettings();
    void setupLayout();

private:
    QGridLayout* mainLayout = Q_NULLPTR;
    QTableView* tableView = Q_NULLPTR;
    TargetTableModel* model = Q_NULLPTR;
};

#endif  // CONTROLPANEL_H

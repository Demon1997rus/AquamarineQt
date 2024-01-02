#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QFrame>
#include <QTableView>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

#include "models/targettablemodel.h"

class ControlPanel : public QFrame
{
    Q_OBJECT
public:
    explicit ControlPanel(QWidget* parent = Q_NULLPTR);

signals:
    void startImitation();
    void stopImitation();
    void allClose();
    void clearImitation();
    void sendSelectedId(int id);

public slots:
    void getDataMapWidgetMouseMove(int x, int y, double distance, double bearing);

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
    QLabel* labelMapXY = Q_NULLPTR;
    QLabel* labelDistance = Q_NULLPTR;
    QLabel* labelBearing = Q_NULLPTR;
    QPushButton* pbImitation = Q_NULLPTR;
    QPushButton* pbPause = Q_NULLPTR;
    QPushButton* pbClose = Q_NULLPTR;
    QPushButton* pbClearImitation = Q_NULLPTR;
};

#endif  // CONTROLPANEL_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "widgettime.h"
#include "controlpanel.h"
#include "mapwidget.h"

/*!
 * \brief The MainWindow class - Экранная форма
 */
class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = Q_NULLPTR);

private:
    void initWidgets();
    void setWindowSettings();
    void setupLayout();
    void initializingConnections();

private:
    QGridLayout* mainLayout = Q_NULLPTR;
    QHBoxLayout* horizontalLayout = Q_NULLPTR;
    QVBoxLayout* verticalLayout = Q_NULLPTR;
    WidgetTime* widgetTime = Q_NULLPTR;
    ControlPanel* controlPanel = Q_NULLPTR;
    MapWidget* mapWidget = Q_NULLPTR;
};

#endif  // MAINWINDOW_H

#include "controlpanel.h"

#include <QHeaderView>
#include <QDebug>

ControlPanel::ControlPanel(QWidget* parent) : QFrame(parent)
{
    initWidgets();
    controlPanelSettings();
    setupLayout();
}

/*!
 * \brief ControlPanel::initWidgets - инициализация виджетов панели управления
 */
void ControlPanel::initWidgets()
{
    mainLayout = new QGridLayout(this);
    tableView = new QTableView(this);
    model = new TargetTableModel(this);
}

/*!
 * \brief ControlPanel::controlPanelSettings - настройки панель управления
 */
void ControlPanel::controlPanelSettings()
{
    // Устанавливаем модель таблицы с целями представлению
    tableView->setModel(model);

    // Размер заголовков согласно содержимому
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void ControlPanel::setupLayout()
{
    // Добавляем таблицу с целями на слой
    mainLayout->addWidget(tableView);

    // Установка главного слоя
    setLayout(mainLayout);
}

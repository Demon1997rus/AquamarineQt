#include "controlpanel.h"

#include <QHeaderView>
#include <QDebug>

ControlPanel::ControlPanel(QWidget* parent) : QFrame(parent)
{
    initWidgets();
    controlPanelSettings();
    setupLayout();
    initializingConnections();
}

/*!
 * \brief ControlPanel::initWidgets - инициализация виджетов панели управления
 */
void ControlPanel::initWidgets()
{
    mainLayout = new QGridLayout(this);
    horizontalLayout = new QHBoxLayout();
    tableView = new QTableView(this);
    model = new TargetTableModel(this);
    pbImitation = new QPushButton("Имитация", this);
    pbPause = new QPushButton("Пауза", this);
}

/*!
 * \brief ControlPanel::controlPanelSettings - настройки панель управления
 */
void ControlPanel::controlPanelSettings()
{
    // Устанавливаем модель таблицы с целями представлению
    tableView->setModel(model);

    // Настройки кнопок управления
    pbPause->setEnabled(false);

    // Размер заголовков согласно содержимому
    tableView->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    tableView->horizontalHeader()->setStretchLastSection(true);
}

void ControlPanel::setupLayout()
{
    // Добавляем кнопки управления на вертикальный слой
    horizontalLayout->addWidget(pbImitation);
    horizontalLayout->addWidget(pbPause);

    // Добавляем таблицу с целями на слой
    mainLayout->addWidget(tableView);

    // Добавляем вертикальный слой с кнопками
    mainLayout->addLayout(horizontalLayout, 1, 0);

    // Установка главного слоя
    setLayout(mainLayout);
}

void ControlPanel::initializingConnections()
{
    connect(pbImitation, &QPushButton::clicked, [this]() {
        pbImitation->setEnabled(false);
        pbPause->setEnabled(true);
    });

    connect(pbPause, &QPushButton::clicked, [this]() {
        pbImitation->setEnabled(true);
        pbPause->setEnabled(false);
    });

    connect(pbImitation, &QPushButton::clicked, this, &ControlPanel::startImitation);

    connect(pbPause, &QPushButton::clicked, this, &ControlPanel::stopImitation);
}

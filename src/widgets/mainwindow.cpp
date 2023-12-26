#include "mainwindow.h"

#include <QDebug>
#include <QStyle>
#include <QApplication>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget* parent) : QWidget(parent)
{
    initWidgets();
    setWindowSettings();
    setupLayout();
    initializingConnections();
}

/*!
 * \brief MainWindow::initWidgets - инициализация виджетов экранной формы
 */
void MainWindow::initWidgets()
{
    mainLayout = new QGridLayout(this);
    horizontalLayout = new QHBoxLayout();
    verticalLayout = new QVBoxLayout();
    widgetTime = new WidgetTime(this);
    pbClose = new QPushButton("Выход", this);
    controlPanel = new ControlPanel(this);
    mapWidget = new MapWidget(this);
}

/*!
 * \brief MainWindow::setWindowSettings - установка настроек формы и её виджетов
 */
void MainWindow::setWindowSettings()
{
    // Установка минимального размера
    setMinimumSize(1024, 768);

    // Установка виджета по центру и размера по умолчанию
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, QSize(1152, 864),
                                    qApp->desktop()->availableGeometry()));

    // Настройки виджета текущего времени
    widgetTime->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
    widgetTime->setLineWidth(3);

    // Настройки правой панели
    controlPanel->setFixedWidth(400);
    controlPanel->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);

    // Настройки левой панели
    mapWidget->setFrameStyle(QFrame::StyledPanel | QFrame::Plain);
}

/*!
 * \brief MainWindow::setupLayout - установка настроек слоя
 */
void MainWindow::setupLayout()
{
    // Добавляем левую и правую панель на горизонтальный слой
    horizontalLayout->addWidget(mapWidget);
    horizontalLayout->addWidget(controlPanel);

    // Добавляем виджет времени и кнопку "Выход" на вертикальный слой
    verticalLayout->addWidget(widgetTime);
    verticalLayout->addWidget(pbClose);

    // Добавляем горизонтальный и вертикальный на основной слой
    // Также вжимаем вертикальный слой вниз
    mainLayout->addLayout(horizontalLayout, 0, 0);
    mainLayout->setRowStretch(mainLayout->rowCount() - 1, 1);
    mainLayout->addLayout(verticalLayout, 1, 0);

    // Установка главного слоя
    setLayout(mainLayout);
}

/*!
 * \brief MainWindow::initializingConnections - инициализация connect-ов
 */
void MainWindow::initializingConnections()
{
    connect(pbClose, &QPushButton::clicked, this, &MainWindow::close);

    connect(controlPanel, &ControlPanel::startImitation, mapWidget, &MapWidget::startImitation);

    connect(controlPanel, &ControlPanel::stopImitation, mapWidget, &MapWidget::stopImitation);
}

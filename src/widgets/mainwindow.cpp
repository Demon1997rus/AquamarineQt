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
void MainWindow::initWidgets() { mainLayout = new QGridLayout(this); }

/*!
 * \brief MainWindow::setWindowSettings - установка настроек формы и её виджетов
 */
void MainWindow::setWindowSettings()
{
    // установка минимального размера
    setMinimumSize(1024, 768);

    // установка виджета по центру и размера по умолчанию
    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, QSize(1152, 864),
                                    qApp->desktop()->availableGeometry()));
}

/*!
 * \brief MainWindow::setupLayout - установка настроек слоя
 */
void MainWindow::setupLayout() { setLayout(mainLayout); }

/*!
 * \brief MainWindow::initializingConnections - инициализация connect-ов
 */
void MainWindow::initializingConnections() {}

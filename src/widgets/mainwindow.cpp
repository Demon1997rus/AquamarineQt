#include "mainwindow.h"

#include <QDebug>
#include <QStyle>
#include <QApplication>
#include <QDesktopWidget>

MainWindow::MainWindow(Qt::WindowFlags f, QWidget* parent) : QWidget(parent, f)
{
    setWindowSettings();
    initializingConnections();
}

/*!
 * \brief MainWindow::setWindowSettings - установка настроек формы
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
 * \brief MainWindow::initializingConnections - инициализация connect-ов
 */
void MainWindow::initializingConnections() {}

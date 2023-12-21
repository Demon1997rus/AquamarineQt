#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGridLayout>

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
};

#endif  // MAINWINDOW_H

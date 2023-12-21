#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(Qt::WindowFlags f = Qt::WindowFlags(), QWidget* parent = nullptr);

private:
    void setWindowSettings();
    void initializingConnections();
};

#endif  // MAINWINDOW_H

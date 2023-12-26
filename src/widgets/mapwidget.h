#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QFrame>
#include <QPaintEvent>
#include <QPainter>
#include <QTimer>

class MapWidget : public QFrame
{
    Q_OBJECT
public:
    explicit MapWidget(QWidget* parent = nullptr);

public slots:
    void startImitation();
    void stopImitation();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    void drawBackground(QPainter& painter);
    void drawMap(QPainter& painter);
    void drawTargets(QPainter& painter);

private:
    QTimer timer;
    int timerCounter;  // счетчик для подсчета срабатываний таймера

private slots:
    void updateImitation();
};

#endif  // MAPWIDGET_H

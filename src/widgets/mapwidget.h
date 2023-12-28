#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QFrame>
#include <QPaintEvent>
#include <QPainter>
#include <QTimer>

#include "utils/randomgenerator.h"
#include "info/targetrepository.h"

class MapWidget : public QFrame
{
    Q_OBJECT
public:
    explicit MapWidget(QWidget* parent = nullptr);

public slots:
    void startImitation();
    void stopImitation();
    void clearImitation();

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    void drawBackground(QPainter& painter);
    void drawMap(QPainter& painter);
    void drawTargets(QPainter& painter);

private:
    QTimer timer;
    RandomGenerator randomGenerator;
    TargetRepository& data;
    int timerCounter = 19;
    const int stepCircle = 200;

private slots:
    void updateImitation();
};

#endif  // MAPWIDGET_H

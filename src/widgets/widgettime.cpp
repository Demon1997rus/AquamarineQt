#include "widgettime.h"

#include <QTime>

WidgetTime::WidgetTime(QWidget* parent) : QLabel(parent), timer(this)
{
    connect(&timer, &QTimer::timeout,
            [this]() { setText("Текущее время: " + QTime::currentTime().toString()); });
    timer.start(1000);
}

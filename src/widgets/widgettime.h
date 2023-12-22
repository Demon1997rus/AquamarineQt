#ifndef WIDGETTIME_H
#define WIDGETTIME_H

#include <QLabel>
#include <QTimer>

/*!
 * \brief The WidgetTime class - виджет для отображения текущего времени
 */
class WidgetTime : public QLabel
{
    Q_OBJECT
public:
    explicit WidgetTime(QWidget* parent = Q_NULLPTR);

private:
    QTimer timer;
};

#endif  // WIDGETTIME_H

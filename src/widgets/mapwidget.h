#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QFrame>
#include <QPaintEvent>
#include <QPainter>

class MapWidget : public QFrame
{
    Q_OBJECT
public:
    explicit MapWidget(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    void drawBackground(QPainter& painter);
};

#endif  // MAPWIDGET_H

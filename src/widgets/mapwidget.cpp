#include "mapwidget.h"

#include <QDebug>

#include <QtMath>

MapWidget::MapWidget(QWidget* parent) : QFrame(parent) {}

void MapWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    drawBackground(painter);

    // Рассчитываем центр и радиус основной окружности
    int centerX = width() / 2;
    int centerY = height() / 2;
    int maxDistance = 1000;
    int step = 200;

    // Рисуем окружности
    int additionalCircleCount = maxDistance / step;
    for (int i = 1; i <= additionalCircleCount; i++)
    {
        int radius = i * centerX * step / maxDistance;
        painter.setPen(Qt::black);
        if (i == additionalCircleCount)
        {
            painter.setPen(Qt::red);  // Цвет для последней окружности
        }
        painter.drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);
    }

    // Рисуем линии
    painter.setPen(Qt::black);
    for (double angle = 0; angle < 360; angle += 45)
    {
        int x = centerX + width() / 2 * qCos(qDegreesToRadians(angle));
        int y = centerY - width() / 2 * qSin(qDegreesToRadians(angle));
        painter.drawLine(centerX, centerY, x, y);
    }
}

/*!
 * \brief MapWidget::drawBackground - рисование фона карты
 */
void MapWidget::drawBackground(QPainter& painter)
{
    // Заполняем фон "шумовой" картиной
    QImage noiseImage(width(), height(), QImage::Format_Grayscale8);
    for (int y = 0; y < height(); ++y)
    {
        for (int x = 0; x < width(); ++x)
        {
            int brightness = qrand() % 81;  // Яркость от 0 до 80
            noiseImage.setPixel(x, y, qRgb(brightness, brightness, brightness));
        }
    }
    painter.drawImage(0, 0, noiseImage);
}

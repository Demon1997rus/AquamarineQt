#include "mapwidget.h"

#include <QDebug>
#include <QtMath>

#include "info/targetrepository.h"

#define DATA TargetRepository::instance()

MapWidget::MapWidget(QWidget* parent) : QFrame(parent), timer(this)
{
    connect(&timer, &QTimer::timeout, this, &MapWidget::updateImitation);
    timerCounter = 19;  // Устанавливаем для генераций цели при начале имитаций сразу
}

void MapWidget::startImitation()
{
    if (!timer.isActive())
    {
        timer.start(500);
    }
}

void MapWidget::stopImitation()
{
    if (timer.isActive())
    {
        timer.stop();
    }
}

void MapWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    drawBackground(painter);
    drawMap(painter);
    drawTargets(painter);
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

/*!
 * \brief MapWidget::drawMap - отрисовка карты
 */
void MapWidget::drawMap(QPainter& painter)
{
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
 * \brief MapWidget::drawTargets - отрисовка целей
 */
void MapWidget::drawTargets(QPainter& painter)
{
    for (const Target& target : DATA)
    {
        // Вычисляем координаты цели
        int centerX = width() / 2;
        int centerY = height() / 2;
        double x = centerX + target.getPosition().x();
        double y = centerY - target.getPosition().y();

        // Рисуем цель
        painter.setPen(QPen(target.getColor(), 2));
        painter.setBrush(target.getColor());
        painter.drawEllipse(QPointF(x, y), 10, 10);  // Регулировка размера

        // Рисуем историю движения
        painter.setPen(QPen(target.getColor(), 1, Qt::DashLine));
        for (int i = 1; i < target.getHistory().size(); ++i)
        {
            QPointF prev = target.getHistory().at(i - 1);
            QPointF current = target.getHistory().at(i);
            prev.setX(centerX + prev.x());
            prev.setY(centerY - prev.y());
            current.setX(centerX + current.x());
            current.setY(centerY - current.y());
            painter.drawLine(prev, current);
        }
    }
}

/*!
 * \brief MapWidget::updateImitation - имитация целей
 */
void MapWidget::updateImitation()
{
    ++timerCounter;
    DATA.updateTargets();
    if (timerCounter >= 20)
    {
        DATA.generateTarget();
        timerCounter = 0;  // сбрасываем счётчик
    }
    update();
}

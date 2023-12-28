#include "mapwidget.h"

#include <QDebug>
#include <QtMath>

#include "utils/angle.h"

MapWidget::MapWidget(QWidget* parent)
  : QFrame(parent), timer(this), data(TargetRepository::instance())
{
    connect(&timer, &QTimer::timeout, this, &MapWidget::updateImitation);
}

/*!
 * \brief MapWidget::startImitation - запуск имитаций
 */
void MapWidget::startImitation()
{
    if (!timer.isActive())
    {
        timer.start(500);
    }
}

/*!
 * \brief MapWidget::stopImitation - остановка имитаций
 */
void MapWidget::stopImitation()
{
    if (timer.isActive())
    {
        timer.stop();
    }
}

/*!
 * \brief MapWidget::clearImitation - очистка имитаций
 */
void MapWidget::clearImitation()
{
    data.clear();
    timerCounter = 19;  // выставляем чтобы после очистки сразу сгенерировалась новая цель
    update();
}

void MapWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    drawBackground(painter);
    // Для отрисовки остального переводим начала координат в центр и поворачиваем виджет на -90 для
    // того чтобы условный "Север" был вверху
    painter.translate(width() / 2, height() / 2);
    painter.rotate(-90);
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
            int brightness = randomGenerator.generateRandomInt(0, 80);  // Яркость от 0 до 80
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
    /*
        Вписанные в свободное пространство окружности с шагом в 200м по
        дистанции и одну окружность по максимально доступному радиусу в отведенном
        свободном пространстве, которая выделена другим цветом.
    */
    QPointF center(0, 0);
    int maxRadius = qMin(width(), height()) / 2;
    painter.setPen(Qt::black);
    for (int radius = stepCircle; radius < maxRadius; radius += stepCircle)
    {
        painter.drawEllipse(center, radius, radius);
    }
    painter.setPen(Qt::red);
    painter.drawEllipse(center, maxRadius, maxRadius);

    /*
        От центра круга с шагом 45 градусов по радиусу отрисовать пунктирные линии до
        границ круга (оси)
   */
    painter.setPen(Qt::black);
    for (double angle = 0; angle < 360; angle += 45)
    {
        int x = qRound(maxRadius * qCos(qDegreesToRadians(angle)));
        int y = qRound(maxRadius * qSin(qDegreesToRadians(angle)));
        painter.drawLine(0, 0, x, y);
    }
}

/*!
 * \brief MapWidget::drawTargets - отрисовка целей
 */
void MapWidget::drawTargets(QPainter& painter)
{
    //              N(x)
    //               |
    //               |
    //               |
    // W(-y) --------*-------- E(y)
    //               |
    //               |
    //               |
    //              S(-x)

    for (const Target& target : data.getTargets())
    {
        // 1) Сохраняем состояние в котором находится QPainter
        painter.save();

        // 2) Смещаемся к текущей позиций цели
        painter.translate(target.getPosition());

        // 3) Начинаем отрисовку цели
        /*
            Условно отображаемая равнобедренным треугольником с углами (30,75, 75 градусов)
            При этом острый угол треугольника цели должен быть направлен в сторону ее движения.
        */
        painter.setPen(target.getColor());

        // За вершину треугольника с острым углом, я буду принимать позицию цели
        double sharpAngle = 30.0;  // Острый угол
        double sideLength = 20.0;  // Размер стороны равнобедренного треугольника
        double offset = (360 - sharpAngle) / 2;  // Смещение от острого угла

        // Далее мы получаем угол (смещение + направление цели) + нормализация углов, а то выйдем за
        // пределы 360 градусов
        double angle1 = Angle::normalizeAngle360(offset + target.getHeading());
        double angle2 =
            Angle::normalizeAngle360(Angle::normalizeAngle360(-offset) + target.getHeading());

        // Получим все три точки треугольника
        QPointF point1;
        point1.setX(0);
        point1.setY(0);

        QPointF point2;
        point2.setX(qCos(qDegreesToRadians(angle1)) * sideLength);
        point2.setY(qSin(qDegreesToRadians(angle1)) * sideLength);

        QPointF point3;
        point3.setX(qCos(qDegreesToRadians(angle2)) * sideLength);
        point3.setY(qSin(qDegreesToRadians(angle2)) * sideLength);

        painter.drawPolygon(QPolygonF() << point1 << point2 << point3);

        // Возращаемся к обратному состоянию после отрисовки цели
        painter.restore();
    }
}

/*!
 * \brief MapWidget::updateImitation - имитация целей
 */
void MapWidget::updateImitation()
{
    ++timerCounter;
    if (timerCounter == 20)
    {
        /*
            В случайном месте в пределах первого внутреннего 200м кольца сначала появляется
            одна цель, каждые 10 секунд
        */
        data.generateTarget();
        timerCounter = 0;
    }
    update();
}

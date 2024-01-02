#include "mapwidget.h"

#include <QDebug>
#include <QtMath>
#include <chrono>

#include "utils/angle.h"

MapWidget::MapWidget(QWidget* parent)
  : QFrame(parent), timerImitation(this), timerFlashState(this), data(TargetRepository::instance())
{
    connect(&timerImitation, &QTimer::timeout, this, &MapWidget::updateImitation);

    connect(&timerFlashState, &QTimer::timeout, this, &MapWidget::updateFlashState);

    timerFlashState.start(200);
}

/*!
 * \brief MapWidget::startImitation - запуск имитаций
 */
void MapWidget::startImitation()
{
    if (!timerImitation.isActive())
    {
        timerImitation.start(500);
    }
}

/*!
 * \brief MapWidget::stopImitation - остановка имитаций
 */
void MapWidget::stopImitation()
{
    if (timerImitation.isActive())
    {
        timerImitation.stop();
    }
}

/*!
 * \brief MapWidget::clearImitation - очистка имитаций
 */
void MapWidget::clearImitation()
{
    data.clear();
    timerCounterImitation = 19;  // выставляем чтобы после очистки сразу сгенерировалась новая цель
    currentTargetId = 0;
    update();
}

void MapWidget::getSelectedIdFromTable(int id)
{
    if (id == currentTargetId)
    {
        currentTargetId = 0;
    }
    else
    {
        currentTargetId = id;
    }
    data.offFlashState();
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

void MapWidget::mouseMoveEvent(QMouseEvent* event)
{
    /*
     * В правой части окна предусмотреть текстовый вывод текущего положения курсора мыши,
     * в случае его нахождения на круге,
     * с информацией, указанной в таблице за исключением номера цели.
     */
    QPointF circleCenter(width() / 2, height() / 2);  // центр круга
    int maxRadius = qMin(width(), height()) / 2;      // максимальный радиус
    int mouseX = event->x() - circleCenter.x();       // координата X курсора
    int mouseY = event->y() - circleCenter.y();       // координата Y курсора

    // Расстояния от центра круга
    double distance = qSqrt(qPow(mouseX, 2) + qPow(mouseY, 2));

    // Пеленг относительно центра круга(градусы)
    double bearing = Angle::normalizeAngle360(qRadiansToDegrees(qAtan2(mouseY, mouseX)) + 90);

    // В случае его нахождения только на круге!
    if ((distance < maxRadius) || qFuzzyCompare(distance, maxRadius))
    {
        emit sendDataMouseMove(mouseX, -mouseY, distance, bearing);
    }
    else
    {
        emit sendDataMouseMove(0, 0, 0.0, 0.0);
    }
}

void MapWidget::mousePressEvent(QMouseEvent* event)
{
    /*
     * Аналогично, при выборе цели на круговом индикаторе она должна выделяться в таблице, и,
     * в случае если цель находится за пределами отображаемой части таблицы, таблица должна
     * «прокрутиться» так, чтобы цель была расположена по центру таблицы.
     */
    QPointF circleCenter(width() / 2, height() / 2);  // центр круга
    int mouseX = event->x() - circleCenter.x();       // координата X курсора
    int mouseY = event->y() - circleCenter.y();       // координата Y курсора

    // Перевод на координаты отрисовки цели
    qSwap(mouseX, mouseY);
    mouseX = -mouseX;

    for (const Target& target : data.getTargets())
    {
        const QPointF& positionTarget = target.getPosition();
        QPointF tempPointMouse(mouseX - positionTarget.x(), mouseY - positionTarget.y());
        if (target.getTriangle().containsPoint(tempPointMouse, Qt::OddEvenFill))
        {
            // Отправляю выбранный идентификатор на карте
            sendSelectedId(target.getId());
            return;
        }
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

    for (Target& target : data.getTargets())
    {
        /*
         *  Должна отображаться трасса цели в виде отрезков, соединяющих 3 последних
         *  положения цели (по аналогии с игрой «змейка»)
         */
        painter.setPen(target.getColor());
        const QQueue<QPointF>& history = target.getHistory();
        for (int i = 1; i < history.size(); ++i)
        {
            painter.drawLine(history.at(i - 1), history.at(i));
        }

        /*
            Условно отображаемая равнобедренным треугольником с углами (30,75, 75 градусов)
            При этом острый угол треугольника цели должен быть направлен в сторону ее движения.
        */
        painter.save();
        painter.translate(target.getPosition());

        painter.setPen(target.getColor());

        if (target.getFlashState())
        {
            painter.setBrush(Qt::black);
        }
        else
        {
            painter.setBrush(target.getColor());
        }

        // За вершину треугольника с острым углом, я буду принимать позицию цели
        double offset = (360 - sharpAngle) / 2;  // Смещение от острого угла

        // Далее мы получаем угол (смещение + направление цели) + нормализация углов, а то выйдем за
        // пределы 360 градусов
        double angle1 = Angle::normalizeAngle360(offset + target.getHeading());
        double angle2 =
            Angle::normalizeAngle360(Angle::normalizeAngle360(-offset) + target.getHeading());

        QPointF point1;
        point1.setX(0);
        point1.setY(0);

        QPointF point2;
        point2.setX(qCos(qDegreesToRadians(angle1)) * sideLength);
        point2.setY(qSin(qDegreesToRadians(angle1)) * sideLength);

        QPointF point3;
        point3.setX(qCos(qDegreesToRadians(angle2)) * sideLength);
        point3.setY(qSin(qDegreesToRadians(angle2)) * sideLength);

        QPolygonF triangle;
        triangle << point1 << point2 << point3;
        painter.drawPolygon(triangle);
        target.setTriangle(qMove(triangle));
        painter.restore();
    }
}

/*!
 * \brief MapWidget::updateImitation - имитация целей
 */
void MapWidget::updateImitation()
{
    ++timerCounterImitation;
    if (timerCounterImitation == 20)
    {
        /*
         *   В случайном месте в пределах первого внутреннего 200м кольца сначала появляется
         *   одна цель, каждые 10 секунд
         */
        data.generateTarget();
        timerCounterImitation = 0;
    }
    /*
     *  Каждый цикл обновления информации цель смещается на 20м(!) в произвольном тангенциальном или
     * радиальном направлении, кроме обратного направления ±45°(!). При этом острый угол
     * треугольника цели должен быть направлен в сторону ее движения.
     */
    data.updateTargets();
    update();
}

/*!
 * \brief MapWidget::updateFlashState - обновления состояния мерцания
 */
void MapWidget::updateFlashState()
{
    /*
     * При выборе цели в таблице соответствующая ей на экране цель должна начать мигать с
     * частотой 5Гц. Трасса цели при этом мигать не должна.
     */

    // 1) Если идентификатор равен нулю, то такой цели не существует сразу выходим
    if (currentTargetId == 0)
        return;

    // Ищем цель в репозиторий по идентификатору
    Target* target = data.findTargetById(currentTargetId);
    if (!target)
        return;

    // инвертируем состояния мерцания
    target->setFlashState(!target->getFlashState());

    //перерисовываем
    update();
}

#ifndef TARGET_H
#define TARGET_H

#include <QColor>
#include <QPointF>
#include <QQueue>
#include <QDebug>
#include <QPolygonF>

/*!
 * \brief The Target class - класс цели
 */
class Target
{
public:
    Target() = default;
    Target(double _distance, double _heading, double _bearing, const QColor& _color);
    Target(const Target& other);
    Target(Target&& other) Q_DECL_NOTHROW;
    Target& operator=(const Target& other);
    Target& operator=(Target&& other) Q_DECL_NOTHROW;

    // геттеры
public:
    int getId() const;
    double getDistance() const;
    double getHeading() const;
    double getBearing() const;
    const QColor& getColor() const;
    const QPointF& getPosition() const;
    const QQueue<QPointF>& getHistory() const;
    bool getFlashState() const;
    void setFlashState(bool value);
    const QPolygonF& getTriangle() const;

    // Изменение состояние объекта
public:
    static void resetCounter();
    void updatePosition(double newHeading, double length);
    void setTriangle(const QPolygonF& value);
    void setTriangle(QPolygonF&& value) Q_DECL_NOTHROW;

    // friend
public:
    friend QDebug operator<<(QDebug debug, const Target& other);

private:
    int id;           // Уникальный идентификатор
    double distance;  // Дистанция до корабля от центра круга в метрах
    double heading;  // Курс корабля относительно центра круга (градусы)
    double bearing;  // Пеленг относительно центра круга (градусы)
    QColor color;    // Цвет корабля
    QPointF position;         // Текущая позиция
    QQueue<QPointF> history;  // История перемещения
    bool flashState;          // Состояние мерцания
    QPolygonF triangle;       // Последний отрисованный треугольник

private:
    /*
        "На всякий случай" - если считать что идентификаторы выдаются раз в 10 секунд, то
       закончатся они через 58496450 тысяч лет)
    */
    static unsigned long long int ID;  // Выдача уникального идентификатора
};

#endif  // TARGET_H

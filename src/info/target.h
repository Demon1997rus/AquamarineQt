#ifndef TARGET_H
#define TARGET_H

#include <QPointF>
#include <QColor>
#include <QList>

/*!
 * \brief The Target class - класс цели
 */
class Target
{
public:
    Target();
    Target(double _distance, double _bearing, const QColor& _color);
    Target(const Target& other);
    Target(Target&& other) Q_DECL_NOTHROW;
    Target& operator=(const Target& other);
    Target& operator=(Target&& other) Q_DECL_NOTHROW;

    //геттеры
public:
    int getId() const;
    double getDistance() const;
    double getBearing() const;

    // Изменение данных по цели
public:
    void updatePosition(double distanceChange, double angleChange);

private:
    int id;           // Уникальный идентификатор цели
    double distance;  // Дистанция до цели от центра круга (м)
    double bearing;  //Пеленг относительно центра круга(градусы)
    QColor color;    // Цвет
    QPointF position;        //Текущая позиция
    QList<QPointF> history;  // История движения

private:
    static int ID;  // автоинкремент для уникальности идентификатора цели
};

#endif  // TARGET_H

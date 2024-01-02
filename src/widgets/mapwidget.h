#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QFrame>
#include <QPaintEvent>
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>

#include "utils/randomgenerator.h"
#include "info/targetrepository.h"

class MapWidget : public QFrame
{
    Q_OBJECT
public:
    explicit MapWidget(QWidget* parent = nullptr);

signals:
    void sendDataMouseMove(int x, int y, double distance, double bearing);
    void sendSelectedId(int id);

public slots:
    void startImitation();
    void stopImitation();
    void clearImitation();
    void getSelectedIdFromTable(int id);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    void drawBackground(QPainter& painter);
    void drawMap(QPainter& painter);
    void drawTargets(QPainter& painter);

private:
    QTimer timerImitation;  //таймер для обновления информаций на экране
    QTimer timerFlashState;           // таймер для мигания
    RandomGenerator randomGenerator;  // генератор рандомныъ значений
    TargetRepository& data;           // репозиторий с целями
    int timerCounterImitation = 19;   // счетчик таймера имитации
    const int stepCircle = 200;       // шаг круга
    int currentTargetId = 0;  // текущий выбраннный идентификатор цели
    double sideLength = 15.0;  // Размер стороны равнобедренного треугольника
    double sharpAngle = 30.0;  // Острый угол цели

private slots:
    void updateImitation();
    void updateFlashState();
};

#endif  // MAPWIDGET_H

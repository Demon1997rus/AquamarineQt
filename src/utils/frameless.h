#ifndef FRAMELESS_H
#define FRAMELESS_H

#include <QWidget>
#include <QRubberBand>
#include <QObject>
#include <QEvent>
#include <QPoint>
#include <QEvent>
#include <QHoverEvent>
#include <QMouseEvent>

/*!
 * \brief The FrameLess class - утилита для изменения стандартного виджета
 *
 * Делает его без заголовка. Также позволяет манипулировать размером и перемещать виджет.
 */
class FrameLess : public QObject
{
    Q_OBJECT

public:
    enum Edge
    {
        None = 0x0,
        Left = 0x1,
        Top = 0x2,
        Right = 0x4,
        Bottom = 0x8,
        TopLeft = 0x10,
        TopRight = 0x20,
        BottomLeft = 0x40,
        BottomRight = 0x80,
    };
    Q_ENUM(Edge);
    Q_DECLARE_FLAGS(Edges, Edge);

    FrameLess(QWidget* target);

    void setBorderWidth(int w) { _borderWidth = w; }
    int borderWidth() const { return _borderWidth; }

protected:
    bool eventFilter(QObject* o, QEvent* e) override;
    void mouseHover(QHoverEvent*);
    void mouseLeave(QEvent*);
    void mousePress(QMouseEvent*);
    void mouseRealese(QMouseEvent*);
    void mouseMove(QMouseEvent*);
    void updateCursorShape(const QPoint&);
    void calculateCursorPosition(const QPoint&, const QRect&, Edges&);

private:
    QWidget* _target = nullptr;
    QRubberBand* _rubberband = nullptr;
    bool _cursorchanged;
    bool _leftButtonPressed;
    Edges _mousePress = Edge::None;
    Edges _mouseMove = Edge::None;
    int _borderWidth;

    QPoint _dragPos;
    bool _dragStart = false;
};

Q_DECLARE_OPERATORS_FOR_FLAGS(FrameLess::Edges);

#endif  // FRAMELESS_H

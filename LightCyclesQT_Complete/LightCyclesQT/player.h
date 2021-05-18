#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QPainter>
#include <QPen>

class Player : public QObject, public QGraphicsPixmapItem
{
public:
    explicit Player(QPixmap pixmap, std::string c);
    void updatePixmap();

    //QRectF boundingRect() const override;
    //QPainterPath shape() const override;

    void goUp();
    void goDown();
    void goLeft();
    void goRight();

    QPoint head;
    QVector<QPoint> path;

    //QPainter* painter;

    enum dir{
        Left,
        Right,
        Up,
        Down,
        None
    };

    std::string color;

    void setDir(dir direction);

    qreal getX() const;
    qreal getY() const;

    dir playerDir;
    qreal speed = 3;

public slots:
    //void setX(qreal X);
    //void setY(qreal Y);
private:
    Q_OBJECT
};

#endif // PLAYER_H

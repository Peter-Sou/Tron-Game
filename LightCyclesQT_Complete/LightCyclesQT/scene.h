#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QAction>
#include "player.h"
#include "aiplayer.h"

class Scene : public QGraphicsScene{
    Q_OBJECT

    public:
        explicit Scene(QObject *parent = nullptr);
        ~Scene();

        void add2Player();
        void addPlayerVSAI();
        void checkCollisions();

        enum GameOver{
            redwins,
            bluewins,
            draw,
        };
        GameOver gameover;

    private:
        Player* player1;
        Player* player2;
        AIPlayer* aiplayer;

        QTimer timer;
        QTimer *countdown;
        int timerincr;
        bool powerup_on_field;

        QPolygonF blue;
        QPolygonF red;
        QPainterPath bluepath;
        QPainterPath redpath;
        QGraphicsPathItem* lastbluepath;
        QGraphicsPathItem* lastredpath;
        QGraphicsRectItem* lastbluerect;
        QGraphicsRectItem* lastredrect;
        QGraphicsRectItem* AICheck;
        QGraphicsRectItem* powerup;
        QRect powerupdims;

        Player::dir p1dir;
        Player::dir p2dir;

    public slots:
        void pause();
        void resume();
        void advance();

    signals:
        void collision();

    protected:
        void keyPressEvent(QKeyEvent *event);
};

#endif // SCENE_H

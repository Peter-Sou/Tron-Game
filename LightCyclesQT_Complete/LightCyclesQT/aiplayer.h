#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "player.h"

class AIPlayer : public Player
{
    Q_OBJECT
public:
    explicit AIPlayer(QPixmap pixmap, std::string c);

    void collisionAvoidance();

    int incrementcollisioncancel;

};

#endif // AIPLAYER_H

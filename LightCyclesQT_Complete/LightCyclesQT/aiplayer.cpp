#include "aiplayer.h"

AIPlayer::AIPlayer(QPixmap pixmap, std::string c) : Player(pixmap, c)
{
    setPixmap(pixmap);
    head = QPoint(550,367);
    playerDir = Left;
    path.append(head);
    color = c;
    speed = 3;
}

void AIPlayer::collisionAvoidance(){
    if(incrementcollisioncancel > 15){
        if(playerDir == Player::Left){
            if(head.rx() - 60 < 0){
                playerDir = Player::Up;
                incrementcollisioncancel = 0;
                path.append(QPoint(head.rx(), head.ry()));
            }
        }
        if(playerDir == Player::Up){
            if(head.ry() - 60 < 0){
                playerDir = Player::Right;
                incrementcollisioncancel = 0;
                path.append(QPoint(head.rx(), head.ry()));
            }
        }
        if(playerDir == Player::Right){
            if(head.rx() + 60 > 750){
                playerDir = Player::Down;
                incrementcollisioncancel = 0;
                path.append(QPoint(head.rx(), head.ry()));
            }
        }
        if(playerDir == Player::Down){
            if(head.ry() + 60 > 500) {
                playerDir = Player::Left;
                incrementcollisioncancel = 0;
                path.append(QPoint(head.rx(), head.ry()));
            }
        }
    }
    incrementcollisioncancel++;
}

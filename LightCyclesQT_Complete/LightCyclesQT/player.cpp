#include "player.h"
#include <QDebug>

Player::Player(QPixmap pixmap, std::string c)
{
    setPixmap(pixmap);
    if(c == "blue"){
        head = QPoint(100,100);
        playerDir = Right;
        //QPen pen(Qt::blue, 3);
        //painter->setPen(pen);
    }
    if(c == "red"){
        head = QPoint(550,367);
        playerDir = Left;
        //QPen pen(Qt::red, 3);
        //painter->setPen(QPen(Qt::red, 3));
    }
    path.append(head);
    color = c;
    speed = 3;
}

void Player::updatePixmap(){
    if(this->color == "blue"){
        switch(playerDir){
            case Player::Left:
                setPixmap(QPixmap(":/resources/images/bluecycle50left.png"));
                break;
            case Player::Right:
                setPixmap(QPixmap(":/resources/images/bluecycle50right.png"));
                break;
            case Player::Up:
                setPixmap(QPixmap(":/resources/images/bluecycle50up.png"));
                break;
            case Player::Down:
                setPixmap(QPixmap(":/resources/images/bluecycle50down.png"));
                break;
            case Player::None:
                setPixmap(QPixmap(":/resources/images/bluecycle50.png"));
                break;
        }
    }
    if(this->color == "red"){
        switch(playerDir){
            case Player::Left:
                setPixmap(QPixmap(":/resources/images/redcycle50left.png"));
                break;
            case Player::Right:
                setPixmap(QPixmap(":/resources/images/redcycle50right.png"));
                break;
            case Player::Up:
                setPixmap(QPixmap(":/resources/images/redcycle50up.png"));
                break;
            case Player::Down:
                setPixmap(QPixmap(":/resources/images/redcycle50down.png"));
                break;
            case Player::None:
                setPixmap(QPixmap(":/resources/images/redcycle50.png"));
                break;
        }
    }
}

void Player::setDir(dir direction){
    playerDir = direction;
}


void Player::goUp()
{
    head.ry() -= speed;
    updatePixmap();
}

void Player::goDown()
{
    head.ry() += speed;
    updatePixmap();
}

void Player::goLeft()
{
    head.rx() -= speed;
    updatePixmap();
}

void Player::goRight()
{
    head.rx() += speed;
    updatePixmap();
}

#include "scene.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDebug>



Scene::Scene(QObject *parent) : QGraphicsScene(parent){
}



Scene::~Scene(){

}



void Scene::add2Player(){
    //timer.start(1000/33);
    countdown = new QTimer(this);
    countdown->start(3000);
    player1 = new Player(QPixmap(":/resources/images/bluecycle50right.png"), "blue");
    player2 = new Player(QPixmap(":/resources/images/redcycle50left.png"), "red");
    aiplayer = nullptr;
    addItem(player1);
    addItem(player2);

    player1->setPos(100,100);
    player2->setPos(550, 367);
    player1->path.append(QPoint(100,100));
    player2->path.append(QPoint(550,367));
    player1->playerDir = Player::Right;
    player2->playerDir = Player::Left;
    lastbluepath = NULL;
    lastredpath = NULL;
    lastbluerect = NULL;
    lastredrect = NULL;
    timerincr = 0;
    powerup_on_field = false;

    while(countdown->remainingTime() > 0){

    }
    delete countdown;
    timer.start(1000/33);
    installEventFilter(this);
    resume();
}



void Scene::addPlayerVSAI(){
    countdown = new QTimer(this);
    countdown->start(3000);
    player1 = new Player(QPixmap(":/resources/images/bluecycle50right.png"), "blue");
    aiplayer = new AIPlayer(QPixmap(":/resources/images/redcycle50left.png"), "red");
    player2 = nullptr;
    addItem(player1);
    addItem(aiplayer);

    player1->setPos(100,100);
    aiplayer->setPos(550, 367);
    player1->path.append(QPoint(100,100));
    aiplayer->path.append(QPoint(550,367));
    player1->playerDir = Player::Right;
    aiplayer->playerDir = Player::Left;
    lastbluepath = NULL;
    lastredpath = NULL;
    lastbluerect = NULL;
    lastredrect = NULL;
    timerincr = 0;
    powerup_on_field = false;

    aiplayer->incrementcollisioncancel = 0;

    while(countdown->remainingTime() > 0){

    }
    delete countdown;
    timer.start(1000/33);
    installEventFilter(this);
    resume();
}



void Scene::pause(){
    disconnect(&timer, SIGNAL(timeout()), this, SLOT(advance()));
}



void Scene::resume(){
    connect(&timer, SIGNAL(timeout()), this, SLOT(advance()));
    //update();
}



void Scene::advance(){
    //if(!step) return;
    //Generate powerups
    if((timerincr % 330 == 0) && (powerup_on_field == false)){
        QPointF coords = QPointF((rand() % 550)+100, (rand() % 300) + 100);
        //qInfo() << "powerup added";
        powerupdims = QRect(coords.rx(), coords.ry(), 20, 20);
        powerup = addRect(powerupdims, QPen(Qt::green, 2));
        powerup_on_field = true;
    }

    if(player1 != nullptr){
            switch(player1->playerDir){
                case Player::Left:
                    player1->setPos(player1->head.rx()-60, player1->head.ry()-8);
                    player1->goLeft();
                    p1dir = Player::Left;
                    break;
                case Player::Right:
                    player1->setPos(player1->head.rx()+10, player1->head.ry()-8);
                    player1->goRight();
                    p1dir = Player::Right;
                    break;
                case Player::Up:
                    player1->setPos(player1->head.rx()-8, player1->head.ry()-60);
                    player1->goUp();
                    p1dir = Player::Up;
                    break;
                case Player::Down:
                    player1->setPos(player1->head.rx()-8, player1->head.ry()+10);
                    player1->goDown();
                    p1dir = Player::Down;
                    break;
                case Player::None:
                    break;
            }
            player1->path.removeLast();
            player1->path.append(QPoint(player1->head.rx(), player1->head.ry()));

            blue << player1->path.last();

            if(lastbluepath != NULL){
                this->removeItem(lastbluepath);
            }

            bluepath.clear();
            bluepath.addPolygon(blue);
            lastbluepath = addPath(bluepath, QPen(Qt::cyan,6));
    }
    if(player2 != nullptr){
            switch(player2->playerDir){
                case Player::Left:
                    player2->setPos(player2->head.rx()-60, player2->head.ry()-8);
                    player2->goLeft();
                    break;
                case Player::Right:
                    player2->setPos(player2->head.rx()+10, player2->head.ry()-8);
                    player2->goRight();
                    break;
                case Player::Up:
                    player2->setPos(player2->head.rx()-8, player2->head.ry()-60);
                    player2->goUp();
                    break;
                case Player::Down:
                    player2->setPos(player2->head.rx()-8, player2->head.ry()+10);
                    player2->goDown();
                    break;
                case Player::None:
                    break;
            }
            player2->path.removeLast();
            player2->path.append(QPoint(player2->head.rx(), player2->head.ry()));

            red << player2->path.last();

            if(lastredpath != NULL){
                    this->removeItem(lastredpath);
            }

            redpath.clear();
            redpath.addPolygon(red);
            lastredpath = addPath(redpath, QPen(Qt::red,6));
    }
    if(aiplayer != nullptr){
            switch(aiplayer->playerDir){
                case Player::Left:
                    aiplayer->setPos(aiplayer->head.rx()-60, aiplayer->head.ry()-8);
                    aiplayer->goLeft();
                    break;
                case Player::Right:
                    aiplayer->setPos(aiplayer->head.rx()+10, aiplayer->head.ry()-8);
                    aiplayer->goRight();
                    break;
                case Player::Up:
                    aiplayer->setPos(aiplayer->head.rx()-8, aiplayer->head.ry()-60);
                    aiplayer->goUp();
                    break;
                case Player::Down:
                    aiplayer->setPos(aiplayer->head.rx()-8, aiplayer->head.ry()+10);
                    aiplayer->goDown();
                    break;
                case Player::None:
                    break;
            }
            aiplayer->path.removeLast();
            aiplayer->path.append(QPoint(aiplayer->head.rx(), aiplayer->head.ry()));

            red << aiplayer->path.last();

            if(lastredpath != NULL){
                this->removeItem(lastredpath);
            }

            redpath.clear();
            redpath.addPolygon(red);
            lastredpath = addPath(redpath, QPen(Qt::red,6));
    }
    checkCollisions();
    timerincr++;
    //qInfo() << timerincr;
}



void Scene::keyPressEvent(QKeyEvent *event)
{
    if(player1 != nullptr){
        if(event->key()==Qt::Key_W){
            //can't go back and forth
            if(player1->playerDir != Player::Down){
                player1->setDir(Player::Up);
            }
        }
        else if(event->key()==Qt::Key_A){
            if(player1->playerDir != Player::Right){
                player1->setDir(Player::Left);
            }
        }
        else if(event->key()==Qt::Key_S){
            if(player1->playerDir != Player::Up){
                player1->setDir(Player::Down);
            }
        }
        else if(event->key()==Qt::Key_D){
            if(player1->playerDir != Player::Left){
                player1->setDir(Player::Right);
            }
        }
        /*for(int i = 0; i < player1->path.size(); i++){
            qInfo() << player1->path[i] ;
        }*/
        player1->path.append(QPoint(player1->head.rx(), player1->head.ry()));
    }
    if(player2 != nullptr){
        if(event->key()==Qt::Key_Up){
            if(player2->playerDir != Player::Down){
                player2->setDir(Player::Up);
            }
        }
        else if(event->key()==Qt::Key_Left){
            if(player2->playerDir != Player::Right){
                player2->setDir(Player::Left);
            }
        }
        else if(event->key()==Qt::Key_Down){
            if(player2->playerDir != Player::Up){
                player2->setDir(Player::Down);
            }
        }
        else if(event->key()==Qt::Key_Right){
            if(player2->playerDir != Player::Left){
                player2->setDir(Player::Right);
            }
        }
        player2->path.append(QPoint(player2->head.rx(), player2->head.ry()));
    }
    QGraphicsScene::keyPressEvent(event);
}



void Scene::checkCollisions(){
    QRect p1head;
    QRect p2head;
    //QRect AIEyes;

    //Create bounding rectangles for player 1 and 2/ai
    if(player1 != nullptr){
        switch(player1->playerDir){
            case Player::Left:
                p1head = QRect(player1->head.rx()-60, player1->head.ry()-8, 55, 17);
                break;
            case Player::Right:
                p1head = QRect(player1->head.rx()+5, player1->head.ry()-8, 55, 17);
                break;
            case Player::Up:
                p1head = QRect(player1->head.rx()-8, player1->head.ry()-60, 17, 55);
                break;
            case Player::Down:
                p1head = QRect(player1->head.rx()-8, player1->head.ry()+5, 17, 55);
                break;
            case Player::None:
                break;
        }
    }
    if(player2 != nullptr){
        switch(player2->playerDir){
            case Player::Left:
                p2head = QRect(player2->head.rx()-60, player2->head.ry()-8, 55, 17);
                break;
            case Player::Right:
                p2head = QRect(player2->head.rx()+5, player2->head.ry()-8, 55, 17);
                break;
            case Player::Up:
                p2head = QRect(player2->head.rx()-8, player2->head.ry()-60, 17, 55);
                break;
            case Player::Down:
                p2head = QRect(player2->head.rx()-8, player2->head.ry()+5, 17, 55);
                break;
            case Player::None:
                break;
        }
    }
    if(aiplayer != nullptr){
        switch(aiplayer->playerDir){
            case AIPlayer::Left:
                p2head = QRect(aiplayer->head.rx()-60, aiplayer->head.ry()-8, 55, 17);
                //AIEyes = QRect(aiplayer->head.rx()-77, aiplayer->head.ry()-8, 17,17);
                break;
            case AIPlayer::Right:
                p2head = QRect(aiplayer->head.rx()+5, aiplayer->head.ry()-8, 55, 17);
                //AIEyes = QRect(aiplayer->head.rx()+60, aiplayer->head.ry()-8, 17,17);
                break;
            case AIPlayer::Up:
                p2head = QRect(aiplayer->head.rx()-8, aiplayer->head.ry()-60, 17, 55);
                //AIEyes = QRect(aiplayer->head.rx()-8, aiplayer->head.ry()-77, 17,17);
                break;
            case AIPlayer::Down:
                p2head = QRect(aiplayer->head.rx()-8, aiplayer->head.ry()+5, 17, 55);
                //AIEyes = QRect(aiplayer->head.rx()-8, aiplayer->head.ry()+60, 17,17);
                break;
            case AIPlayer::None:
                break;
        }
    }

    //for painting the collision detection rectangles
    /*if(lastbluerect != NULL){
        this->removeItem(lastbluerect);
    }
    if(lastredrect != NULL){
        this->removeItem(lastredrect);
    }*/

    //lastbluerect = addRect(p1head, QPen(Qt::cyan));
    //lastredrect = addRect(p2head, QPen(Qt::red));
    //addRect(AIEyes, QPen(Qt::green));

    //Check if out of bounds
    if(player1 != nullptr){
        if(player1->head.rx() < 55 || player1->head.rx() > 705 || player1->head.ry() < 55 || player1->head.ry() > 455){
            qInfo() << "blue crashed";
            this->pause();
        }
    }
    if(player2 != nullptr){
        if(player2->head.rx() < 55 || player2->head.rx() > 705 || player2->head.ry() < 55 || player2->head.ry() > 455){
            qInfo() << "red crashed";
            this->pause();
        }
    }

    //Check for a draw
    if(p1head.intersects(p2head)){
        qInfo() << "both crashed";
        gameover = draw;
        this->pause();
        emit collision();
    }

    //Check paths and collisions with any of our rectangles for player 1 and 2/ai
    if(player1 != nullptr){
        for(int i = 0; i < player1->path.size()-1; i++){
            QPoint currPt = player1->path[i];
            QPoint nextPt = player1->path[i+1];
            QRect p1Lines;
            //if current point is to the right of nextPt
            if(currPt.x() - nextPt.x() >= 0){
                p1Lines.setX(nextPt.x());
                p1Lines.setWidth(currPt.x()-nextPt.x());
            }
            else{
                p1Lines.setX(currPt.x());
                p1Lines.setWidth(nextPt.x()-currPt.x());
            }
            //if current point is below nextpt
            if(currPt.y() - nextPt.y() >= 0){
                p1Lines.setY(nextPt.y());
                p1Lines.setHeight(currPt.y()-nextPt.y());
            }
            else{
                p1Lines.setY(currPt.y());
                p1Lines.setHeight(nextPt.y()-currPt.y());
            }
            /*if(aiplayer != nullptr){
                if(AIEyes.intersects(p1Lines)){
                    qInfo() << "Intersection detected";
                    if(aiplayer->incrementcollisioncancel > 15){
                        if(aiplayer->playerDir == AIPlayer::Left){
                            qInfo() << static_cast<string>(aiplayer->playerDir);
                            aiplayer->playerDir = AIPlayer::Up;
                        }
                        if(aiplayer->playerDir == AIPlayer::Up){
                            aiplayer->playerDir = AIPlayer::Right;
                        }
                        if(aiplayer->playerDir == AIPlayer::Right){
                            aiplayer->playerDir = AIPlayer::Down;
                        }
                        if(aiplayer->playerDir == AIPlayer::Down){
                            aiplayer->playerDir = AIPlayer::Left;
                        }
                        aiplayer->incrementcollisioncancel = 0;
                    }
                }
            }*/
            if(p1head.intersects(p1Lines)){
                qInfo() << "blue crashed";
                gameover = redwins;
                this->pause();
                emit collision();
            }
            if(p2head.intersects(p1Lines)){
                qInfo() << "red crashed";
                gameover = bluewins;
                this->pause();
                emit collision();
            }
        }
    }
    if(player2 != nullptr){
        for(int i = 0; i < player2->path.size()-1; i++){
            QPoint currPt = player2->path[i];
            QPoint nextPt = player2->path[i+1];
            QRect p2Lines;
            //if current point is to the right of nextPt
            if(currPt.x() - nextPt.x() >= 0){
                p2Lines.setX(nextPt.x());
                p2Lines.setWidth(currPt.x()-nextPt.x());
            }
            else{
                p2Lines.setX(currPt.x());
                p2Lines.setWidth(nextPt.x()-currPt.x());
            }
            //if current point is below nextpt
            if(currPt.y() - nextPt.y() >= 0){
                p2Lines.setY(nextPt.y());
                p2Lines.setHeight(currPt.y()-nextPt.y());
            }
            else{
                p2Lines.setY(currPt.y());
                p2Lines.setHeight(nextPt.y()-currPt.y());
            }

            if(p1head.intersects(p2Lines)){
                qInfo() << "blue crashed";
                gameover = redwins;
                this->pause();
                emit collision();
            }
            if(p2head.intersects(p2Lines)){
                qInfo() << "red crashed";
                gameover = bluewins;
                this->pause();
                emit collision();
            }
        }
    }
    if(aiplayer != nullptr){
        for(int i = 0; i < aiplayer->path.size()-1; i++){
            QPoint currPt = aiplayer->path[i];
            QPoint nextPt = aiplayer->path[i+1];
            QRect p2Lines;
            //if current point is to the right of nextPt
            if(currPt.x() - nextPt.x() >= 0){
                p2Lines.setX(nextPt.x());
                p2Lines.setWidth(currPt.x()-nextPt.x());
            }
            else{
                p2Lines.setX(currPt.x());
                p2Lines.setWidth(nextPt.x()-currPt.x());
            }
            //if current point is below nextpt
            if(currPt.y() - nextPt.y() >= 0){
                p2Lines.setY(nextPt.y());
                p2Lines.setHeight(currPt.y()-nextPt.y());
            }
            else{
                p2Lines.setY(currPt.y());
                p2Lines.setHeight(nextPt.y()-currPt.y());
            }

            /*
            if(AIEyes.intersects(p2Lines)){
                if(aiplayer->playerDir == AIPlayer::Left){
                    aiplayer->playerDir = Player::Up;
                }
                if(aiplayer->playerDir == Player::Up){
                    aiplayer->playerDir = Player::Right;
                }
                if(aiplayer->playerDir == Player::Right){
                    aiplayer->playerDir = Player::Down;
                }
                if(aiplayer->playerDir == Player::Down){
                    aiplayer->playerDir = Player::Left;
                }
            }
            */

            if(p1head.intersects(p2Lines)){
                qInfo() << "blue crashed";
                gameover = redwins;
                this->pause();
                emit collision();
            }
            if(p2head.intersects(p2Lines)){
                qInfo() << "red crashed";
                gameover = bluewins;
                this->pause();
                emit collision();
            }
        }
    }

    //Check for powerup collision
    if(player1 != nullptr){
        if(p1head.intersects(powerupdims)){
            powerup_on_field = false;
            player1->speed += 1;
            this->removeItem(powerup);
            powerupdims = QRect(0,0,0,0);
        }
    }
    if(player2 != nullptr){
        if(p2head.intersects(powerupdims)){
            powerup_on_field = false;
            player2->speed += 1;
            this->removeItem(powerup);
            powerupdims = QRect(0,0,0,0);
        }
    }


    //AI Avoidance
    if(aiplayer != nullptr){
        aiplayer->collisionAvoidance();
        //qInfo() << aiplayer->incrementcollisioncancel;
    }
}

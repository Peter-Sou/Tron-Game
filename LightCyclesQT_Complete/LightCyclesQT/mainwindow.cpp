#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include "player.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix(":/resources/images/tron-logo-font-download2.jpg");
    ui->logo->setPixmap(pix);

    //ui->logo->setPixmap(pix.scaled(ui->logo->size(), 4));
    ui->logo->setScaledContents(true);

    connect(ui->playButton, &QPushButton::released, this, &MainWindow::createGame);
    connect(ui->aiplayButton, &QPushButton::released, this, &MainWindow::createAIGame);

}

void MainWindow::createGame(){
    scene = new Scene(this);
    ui->graphicsView->raise();

    scene->setSceneRect(0, 0, 750, 500);

    QGraphicsPixmapItem * background = new QGraphicsPixmapItem(QPixmap(":/resources/images/newbackground.png"));
    scene->addItem(background);

    ui->graphicsView->setScene(scene);

    //player init, 1 = blue, 2 = red
    connect(scene, &Scene::collision, this, &MainWindow::gameOver);
    scene->add2Player();
}

void MainWindow::createAIGame(){
    scene = new Scene(this);
    ui->graphicsView->raise();

    scene->setSceneRect(0, 0, 750, 500);

    QGraphicsPixmapItem * background = new QGraphicsPixmapItem(QPixmap(":/resources/images/newbackground.png"));
    scene->addItem(background);

    ui->graphicsView->setScene(scene);

    //player init, 1 = blue, 2 = red
    connect(scene, &Scene::collision, this, &MainWindow::gameOver);
    scene->addPlayerVSAI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::gameOver(){
    //ui->victorLabel->setStyleSheet(QStringLiteral("QLabel{color: rgb(0, 0, 0);}"));
    ui->victorLabel->setStyleSheet("background-color: white");
    if(scene->gameover == Scene::GameOver::redwins){
        qInfo() << "Red Wins!";
        ui->victorLabel->setText("Red Wins!");
    }
    if(scene->gameover == Scene::GameOver::bluewins){
        qInfo() << "Blue Wins!";
        ui->victorLabel->setText("Blue Wins!");
    }
    if(scene->gameover == Scene::GameOver::draw){
        qInfo() << "It's a draw.";
        ui->victorLabel->setText("It's a draw.");
    }
    ui->victorLabel->raise();
}

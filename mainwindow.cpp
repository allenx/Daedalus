#include "gamefield.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QIcon>
#include "ai.h"
#include "winningdialog.h"
#include "defeateddialog.h"
#include "aboutpage.h"
#include "preferences.h"
#include "stopwatch.h"
#include <QtAlgorithms>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    alignmentGroupOfGame(new QActionGroup(this)),
    alignmentGroupOfMore(new QActionGroup(this)),
    newGameAct(new QAction(tr("&New Game"), this)),
    restartAct(new QAction(tr("&Restart"), this)),
    preferencesAct(new QAction(tr("&Preferences"), this)),
    aboutAct(new QAction(tr("&About"), this))
{


    ui->setupUi(this);

    setWindowTitle("Daedalus -- A MineSweeper Game");
    setStyleSheet("background-color: black");
//    this->setFixedSize(1000, 1000);
    bindAIToUI(&AI::sharedInstance(), this);

    alignmentGroupOfMore->setExclusive(true);
    alignmentGroupOfMore->addAction(preferencesAct);
    alignmentGroupOfMore->addAction(aboutAct);

    connect(newGameAct, SIGNAL(triggered(bool)), &AI::sharedInstance(), SLOT(userClickedRestart()));
    connect(restartAct, SIGNAL(triggered(bool)), &AI::sharedInstance(), SLOT(userClickedRestart()));
    connect(preferencesAct, SIGNAL(triggered(bool)), this, SLOT(openPreferencesPage()));
    connect(aboutAct, SIGNAL(triggered(bool)), this, SLOT(openAboutPage()));


    //group alignment so that they are mutual exclusive
    QList<QAction *> gameOptionsMenuActionsGroup = QList<QAction *>();
    gameOptionsMenuActionsGroup.append(newGameAct);
    gameOptionsMenuActionsGroup.append(restartAct);
    createMenuWithNameAndActions("Game", gameOptionsMenuActionsGroup);

    QList<QAction *> moreOptionsMenuActionsGroup = QList<QAction *>();
    moreOptionsMenuActionsGroup.append(preferencesAct);
    moreOptionsMenuActionsGroup.append(aboutAct);
    createMenuWithNameAndActions("More", moreOptionsMenuActionsGroup);

    GameField *field = new GameField;
    StopWatch *stopWatch = new StopWatch;

    QVBoxLayout *vLayout = new QVBoxLayout;
    //QPushButton *btn1 = new QPushButton(QIcon(smilePic));
    QHBoxLayout *hLayout = new QHBoxLayout;
    QLabel *placeHolder1 = new QLabel;
    QLabel *placeHolder2 = new QLabel;
    hLayout->addWidget(placeHolder1);
    hLayout->addWidget(stopWatch);
    hLayout->addWidget(placeHolder2);
    vLayout->addLayout(hLayout);
//    vLayout->addWidget(stopWatch);
    vLayout->addWidget(field);
    this->centralWidget()->setLayout(vLayout);
}

MainWindow::~MainWindow()
{
    delete ui;
//    delete gameOptionsMenu;
//    delete moreOptionsMenu;
//    delete alignmentGroupOfGame;
//    delete alignmentGroupOfMore;
//    delete newGameAct;
//    delete restartAct;
//    delete preferencesAct;
//    delete aboutAct;
}

void MainWindow::createMenuWithNameAndActions(const char *str, QList<QAction *> actions) {
    QMenu *foo = menuBar()->addMenu(tr(str));
    foo->addActions(actions);
}

//QAction *MainWindow::actionWithName(const char *str) {
//    QAction *foo = new QAction(tr(str), this);
//    //foo->setShortcuts(QKeySequence::?);
//    //foo->setStatusTip(tr(""));
//    //connect(foo, SIGNAL(triggered(bool)), this, SLOT());
//}

void MainWindow::openAboutPage() {
    AboutPage *foo = new AboutPage;
    foo->show();
    emit newWindowPopped();
}

void MainWindow::openPreferencesPage() {
    Preferences *foo = new Preferences;
    foo->show();
    emit newWindowPopped();
}

void MainWindow::showWinningResults() {
    WinningDialog *foo = new WinningDialog;
    QObject::disconnect(&AI::sharedInstance(), SIGNAL(steppedOnAMine(Cell*)), this, SLOT(showFailure()));
    foo->show();
    emit newWindowPopped();
}

void MainWindow::showFailure() {
    DefeatedDialog *foo = new DefeatedDialog();
//    disconnect(&AI::sharedInstance(), SIGNAL(steppedOnAMine(Cell*)), SLOT(showFailure()));
    QObject::disconnect(&AI::sharedInstance(), SIGNAL(steppedOnAMine(Cell*)), this, SLOT(showFailure()));
    QObject::disconnect(&AI::sharedInstance(), SIGNAL(succeeded()), this, SLOT(showWinningResults()));
    foo->show();
    emit newWindowPopped();
}

//void MainWindow::newGame() {

//}

//void MainWindow::restart() {
//    emit restart();
//}

void MainWindow::refreshUI() {
    GameField *field = new GameField;
    StopWatch *stopWatch = new StopWatch;

    qDeleteAll(this->centralWidget()->children());

    QVBoxLayout *vLayout = new QVBoxLayout;
    //QPushButton *btn1 = new QPushButton(QIcon(smilePic));
    QHBoxLayout *hLayout = new QHBoxLayout;
    QLabel *placeHolder1 = new QLabel;
    QLabel *placeHolder2 = new QLabel;
    hLayout->addWidget(placeHolder1);
    hLayout->addWidget(stopWatch);
    hLayout->addWidget(placeHolder2);
    vLayout->addLayout(hLayout);
//    vLayout->addWidget(stopWatch);
    vLayout->addWidget(field);
    this->centralWidget()->setLayout(vLayout);
}


void MainWindow::bindAIToUI(AI *ai, MainWindow *window) {
    QObject::connect(ai, SIGNAL(steppedOnAMine(Cell*)), this, SLOT(showFailure()));
    QObject::connect(ai, SIGNAL(succeeded()), this, SLOT(showWinningResults()));
    QObject::connect(ai, SIGNAL(reloadGame()), this, SLOT(refreshUI()));
    QObject::connect(this, SIGNAL(newWindowPopped()), ai, SIGNAL(newWindowPopped()));


}

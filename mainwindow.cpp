#include "gamefield.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGridLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QIcon>
#include "ai.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GameField *field = new GameField;
    QVBoxLayout *foo = new QVBoxLayout;
    QPushButton *btn = new QPushButton("GO");
    //QPushButton *btn1 = new QPushButton(QIcon(smilePic));
    QPushButton *btn2 = new QPushButton("BEAU");
    QHBoxLayout *foo1 = new QHBoxLayout;
    foo1->addWidget(btn);
    //foo1->addWidget(btn1);
    foo1->addWidget(btn2);
    //layout.addWidget(field);
    //setCentralWidget(field);

    foo->addLayout(foo1);
    foo->addWidget(field);
    this->centralWidget()->setLayout(foo);




}

MainWindow::~MainWindow()
{
    delete ui;
}

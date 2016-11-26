#include "gamefield.h"
#include <QVBoxLayout>
#include <QSizePolicy>

GameField::GameField(QWidget *parent) :
    QWidget(parent),
    //ai(new AI),
    hasBeenSetup(false),
    gridLayout(new QGridLayout)

{
    CellMatrix *cells = AI::sharedInstance().cells;
    //CellMatrix *cells = ai->cells;

    for (int i=1; i<cells->count()-1; ++i) {
        for (int j=1; j<cells->at(i)->count()-1; ++j) {
            gridLayout->addWidget(cells->at(i)->at(j), i, j);
        }
    }

//    this->setLayout(gridLayout);

    QWidget *client = new QWidget(this);
    client->setLayout(gridLayout);

    scrollView = new QScrollArea(this);
    scrollView->setWidget(client);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(scrollView);
    //setFixedSize(800, 800);
    //setSizePolicy();
    setLayout(layout);

//    scrollView->setLayout(gridLayout);
//    scrollView->setWidget(this);


//    bottomLayout->addWidget(scrollView);
//    this->setLayout(bottomLayout);

}



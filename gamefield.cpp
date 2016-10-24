#include "gamefield.h"

GameField::GameField(QWidget *parent) :
    QWidget(parent),
    ai(new AI),
    hasBeenSetup(false),
    layout(new QGridLayout)

{
    CellMatrix *cells = ai->cells;

    for (int i=1; i<cells->count()-1; ++i) {
        for (int j=1; j<cells->at(i)->count()-1; ++j) {
            layout->addWidget(cells->at(i)->at(j), i, j);

        }
    }

    this->setLayout(layout);

}



#ifndef AI_H
#define AI_H

#include "cell.h"
#include "soundhandler.h"
#include <QList>


#include "userinteractionhandler.h"
#include "headerwrapper.h"

//Iterates the 8 pointers of a cell and apply the lambda function to them
template<typename Lambda>
void iterateCellsAround(Cell *cell, Lambda &&func) {
    func(cell->North);
    func(cell->NorthEast);
    func(cell->NorthWest);
    func(cell->South);
    func(cell->SouthEast);
    func(cell->SouthWest);
    func(cell->East);
    func(cell->West);
}

struct Board {
    bool isAllSet;
    int rowCount;
    int colCount;
    int mineCount;
};

class AI : public QObject
{

    Q_OBJECT

public:
    AI();
    Cell ***initCellsFoo(int rowCount, int columnCount);
    //QList<QList<Cell *> *> *initCells(int rowCount, int colCount);
    CellMatrix *initCells(int rowCount=20, int colCount=20);

    CellMatrix *cells;
    FlatList *mines;
    int flaggedCount;
    Board board;
    void layMines(Cell *);
    void countNeighbourMines(CellMatrix *cells);

signals:
    void steppedOnAMine(Cell *);


private:
    UserInteractionHandler *_interactionHandler;
    SoundHandler *_soundHandler;
    void bindCellsToHandler(Cell *, UserInteractionHandler *);
    void bindHandlerToAI(UserInteractionHandler *, AI *);

public slots:
    void rightClickACell(Cell *);
    void revealCell(Cell *);
    void pause();
    void resume();

};

#endif // AI_H

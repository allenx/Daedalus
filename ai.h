#ifndef AI_H
#define AI_H

#include "cell.h"
#include <QList>


#include "userinteractionhandler.h"
#include "headerwrapper.h"

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
    void countNeighbourMines(CellMatrix *cells);

signals:
    void steppedOnAMine(Cell *);


private:
    UserInteractionHandler *hand;

public slots:
    void layMines(Cell *);
    void rightClickACell(Cell *);
    void revealCell(Cell *);
};

#endif // AI_H

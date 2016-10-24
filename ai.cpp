#include "ai.h"
#include <QDebug>

AI::AI() :
    mines(new FlatList),
    flaggedCount(0),
    board(Board()),
    hand(new UserInteractionHandler)
{
    if (board.isAllSet) {
        cells = initCells(board.rowCount, board.colCount);
    } else {
        cells = initCells();
    }

}


//2-Dimensional C++ Typical Array of Cell *
Cell *** AI::initCellsFoo(int rowCount, int columnCount) {
    Cell ***cells = new Cell **[rowCount];
    for (int i = 0; i < rowCount; ++i) {
        cells[i] = new Cell *[columnCount];
        for (int j = 0; j < columnCount; ++j) {
            Cell *foo = new Cell(i, j);
            cells[i][j] = foo;
        }
    }
    return cells;
}


//2-Dimensional Qlist of Cell *
//Create a (rowCount + 2) * (columnCount + 2) Matrix to fix the out-of-bounds problem when counting asigning pointer to each Cell.
CellMatrix *AI::initCells(int rowCount, int columnCount) {

    CellMatrix *cells = new CellMatrix;

    //Weird Implementation Got Dumped
    //    for (int i = 0; i < rowCount + 2; ++i) {
    //        cells->append(new QList<Cell *>);
    //        for (int j = 0; j < columnCount + 2; ++j) {
    //            if (0 == i || rowCount + 1 == i) {
    //                cells->at(0)->append(NULL);
    //            } else {
    //                if (0 == j || columnCount + 1 == j) {
    //                    cells->at(i)->append(NULL);
    //                    continue;
    //                }
    //                Cell *foo = new Cell(i, j);
    //                cells->at(i)->append(foo);
    //            }
    //        }
    //    }

    for (int i=0; i < rowCount+2; ++i) {
        cells->append((new FlatList));
        for (int j=0; j<columnCount+2; ++j) {
            Cell *foo = new Cell(i, j);
            cells->at(i)->append(foo);
        }
    }

    for(int k = 1; k < rowCount + 1; ++k) {
        for (int l = 1; l < columnCount + 1; ++l) {
            auto foo = cells->at(k)->at(l);
//            QObject::connect(foo, SIGNAL(clicked_left(Cell*)), this, SLOT(layMinesFoo(Cell*)));
            foo->NorthWest = cells->at(k-1)->at(l-1);
            foo->North = cells->at(k-1)->at(l);
            foo->NorthEast = cells->at(k-1)->at(l+1);
            foo->East = cells->at(k)->at(l+1);
            foo->SouthEast = cells->at(k+1)->at(l+1);
            foo->South = cells->at(k+1)->at(l);
            foo->SouthWest = cells->at(k+1)->at(l-1);
            foo->West = cells->at(k)->at(l-1);
        }
    }

    return cells;
}


void AI::layMines(Cell *cell) {

}



//void AI::layMinesFoo(Cell *cell) {
//    if (!allSet) {
//        for (int i=1; i<cells->count()-1; ++i) {
//            for (int j=1; j<cells->at(i)->count()-1; ++j) {
//                if (cells->at(i)->at(j) != cell) {
//                    cells->at(i)->at(j)->isMine = true;
//                    mines.append(cells.at(i).at(j));
//                }

//            }
//        }
//        countNeighbourMines(cells);
//        allSet = true;
//        qDebug("YO");
//    }

//}

//[TODO]: Can think of some algorithm to simplify the this progress because there's currently a lot of iterations and if statements
void AI::countNeighbourMines(CellMatrix *cells) {

    for (int i = 1; i < cells->count()-1; ++i) {
        for (int j = 1; j < cells->at(i)->count()-1; ++j) {
            auto foo = cells->at(i)->at(j);
            if (foo->isMine) {
                foo->content = -1;
                continue;
            }
            if (foo->North->isMine) {
                foo->content += 1;
            }
            if (foo->South->isMine) {
                foo->content += 1;
            }
            if (foo->West->isMine) {
                foo->content += 1;
            }
            if (foo->East->isMine) {
                foo->content += 1;
            }
            if (foo->NorthWest->isMine) {
                foo->content += 1;
            }
            if (foo->NorthEast->isMine) {
                foo->content += 1;
            }
            if (foo->SouthWest->isMine) {
                foo->content += 1;
            }
            if (foo->SouthEast->isMine) {
                foo->content += 1;
            }
        }
    }
}


void AI::revealCell(Cell *cell) {
    int foo = 0;
    if (-2 == cell->content) {
        layMines(cell);
    }

    if (cell->status == revealed) {

        if (cell->North->status == revealed) ++foo;
        if (cell->NorthEast->status == revealed) ++foo;
        if (cell->East->status == revealed) ++foo;
        if (cell->SouthEast->status == revealed) ++foo;
        if (cell->South->status == revealed) ++foo;
        if (cell->SouthWest->status == revealed) ++foo;
        if (cell->West->status == revealed) ++foo;
        if (cell->NorthWest->status == revealed) ++foo;

        if (foo == cell->content) {

            revealCell(cell->NorthWest);
            revealCell(cell->NorthEast);
            revealCell(cell->SouthWest);
            revealCell(cell->SouthEast);
        }

    } else {
        cell->status = revealed;
        cell->setText("fucker");

        switch (cell->content) {

        case -1: {
            for (int i=0; i<mines->count(); ++i) {
                if (cell != mines->at(i)) {
                    revealCell(mines->at(i));
                }
            }
            emit steppedOnAMine(cell);
            break;
        }

        default: {

            if (cell->North->status == revealed) ++foo;
            if (cell->NorthEast->status == revealed) ++foo;
            if (cell->East->status == revealed) ++foo;
            if (cell->SouthEast->status == revealed) ++foo;
            if (cell->South->status == revealed) ++foo;
            if (cell->SouthWest->status == revealed) ++foo;
            if (cell->West->status == revealed) ++foo;
            if (cell->NorthWest->status == revealed) ++foo;

            if (foo == cell->content) {

                revealCell(cell->NorthWest);
                revealCell(cell->NorthEast);
                revealCell(cell->SouthWest);
                revealCell(cell->SouthEast);
            }
            break;
        }
        }



    }
}


void AI::rightClickACell(Cell *cell) {
    switch (cell->status) {
    case virgin:

        break;
    default:
        break;
    }
}

#include "ai.h"
#include <QDebug>

AI::AI() :
    mines(new FlatList),
    flaggedCount(0),
    board(Board()),
    _interactionHandler(new UserInteractionHandler),
    _soundHandler(new SoundHandler)
{

    if (board.isAllSet) {
        cells = initCells(board.rowCount, board.colCount);
    } else {
        board.rowCount = 20;
        board.colCount = 20;
        board.mineCount = 100;
        board.isAllSet = true;
        cells = initCells();
    }
    _soundHandler->playBGM();
    bindHandlerToAI(_interactionHandler, this);

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
            bindCellsToHandler(foo, _interactionHandler);
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
    int maxRow = cells->count() - 2;
    int maxCol = cells->at(0)->count() - 2;
    int foo = board.mineCount;
    while (foo != 0) {
        int randomRow = (qrand() % maxRow) + 1;
        int randomCol = (qrand() % maxCol) + 1;
        if ((randomRow != cell->coordinate.atRow) && (randomCol != cell->coordinate.atCol)) {
            cells->at(randomRow)->at(randomCol)->isMine = true;
            foo -= 1;
        }
    }
    countNeighbourMines(cells);
    qDebug("YO");
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
            foo->content = 0;
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

        FlatList *fooListToReveal = new FlatList;

        if (cell->North->status == flagged) {
            ++foo;
        } else {
            fooListToReveal->append(cell->North);
        }

        if (cell->NorthEast->status == flagged) {
            ++foo;
        } else {
            fooListToReveal->append(cell->NorthEast);
        }

        if (cell->East->status == flagged) {
            ++foo;
        } else {
            fooListToReveal->append(cell->East);
        }

        if (cell->SouthEast->status == flagged) {
            ++foo;
        } else {
            fooListToReveal->append(cell->SouthEast);
        }

        if (cell->South->status == flagged) {
            ++foo;
        } else {
            fooListToReveal->append(cell->South);
        }

        if (cell->SouthWest->status == flagged) {
            ++foo;
        } else {
            fooListToReveal->append(cell->SouthWest);
        }

        if (cell->West->status == flagged) {
            ++foo;
        } else {
            fooListToReveal->append(cell->West);
        }

        if (cell->NorthWest->status == flagged) {
            ++foo;
        } else {
            fooListToReveal->append(cell->NorthWest);
        }

        if (foo == cell->content) {

            for (int i=0; i<fooListToReveal->count(); ++i) {
                if (fooListToReveal->at(i)->status != revealed) {
                    revealCell(fooListToReveal->at(i));
                }
            }
        }

    } else {
        cell->setStatus(revealed);

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

            FlatList *fooListToReveal = new FlatList;

            if (cell->North->status == flagged) {
                ++foo;
            } else {
                fooListToReveal->append(cell->North);
            }

            if (cell->NorthEast->status == flagged) {
                ++foo;
            } else {
                fooListToReveal->append(cell->NorthEast);
            }

            if (cell->East->status == flagged) {
                ++foo;
            } else {
                fooListToReveal->append(cell->East);
            }

            if (cell->SouthEast->status == flagged) {
                ++foo;
            } else {
                fooListToReveal->append(cell->SouthEast);
            }

            if (cell->South->status == flagged) {
                ++foo;
            } else {
                fooListToReveal->append(cell->South);
            }

            if (cell->SouthWest->status == flagged) {
                ++foo;
            } else {
                fooListToReveal->append(cell->SouthWest);
            }

            if (cell->West->status == flagged) {
                ++foo;
            } else {
                fooListToReveal->append(cell->West);
            }

            if (cell->NorthWest->status == flagged) {
                ++foo;
            } else {
                fooListToReveal->append(cell->NorthWest);
            }

            if (foo == cell->content) {

                for (int i=0; i<fooListToReveal->count(); ++i) {
                    if (fooListToReveal->at(i)->status != revealed) {
                        revealCell(fooListToReveal->at(i));
                    }
                }
            }
            break;
        }
        }



    }
}


void AI::rightClickACell(Cell *cell) {
    switch (cell->status) {
    case virgin:
        cell->setStatus(flagged);
        break;
    case flagged:
        cell->setStatus(questioned);
    case questioned:
        cell->setStatus(virgin);
    default:
        break;
    }
}


void AI::bindCellsToHandler(Cell *cell, UserInteractionHandler *interactionHandler) {
    QObject::connect(cell, SIGNAL(statusChanged()), cell, SLOT(refreshUI()));

    QObject::connect(cell, SIGNAL(clicked(Cell*,QMouseEvent*)), interactionHandler, SLOT(interactionReceived(Cell*,QMouseEvent*)));
    QObject::connect(cell, SIGNAL(clicked_double(Cell*,QMouseEvent*)), interactionHandler, SLOT(interactionReceived_DoubleClick(Cell*,QMouseEvent*)));

    //cell was revealed
}


void AI::bindHandlerToAI(UserInteractionHandler *interactionHandler, AI *ai) {
    QObject::connect(interactionHandler, SIGNAL(clicked_left(Cell*)), ai, SLOT(revealCell(Cell*)));
    QObject::connect(interactionHandler, SIGNAL(clicked_right(Cell*)), ai, SLOT(rightClickACell(Cell*)));
    QObject::connect(interactionHandler, SIGNAL(clicked_double(Cell*)), ai, SLOT(revealCell(Cell*)));

}




void AI::pause() {

}


void AI::resume() {

}

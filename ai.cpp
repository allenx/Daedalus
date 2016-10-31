#include "ai.h"
#include <QDebug>
#include <QSound>

AI::AI() :
    mines(new FlatList),
    flaggedCount(0),
    _interactionHandler(new UserInteractionHandler(this)),
    board(Board()),
    _soundHandler(new SoundHandler(this))

{

    if (board.isAllSet) {
        cells = initCells(board.rowCount, board.colCount);
    } else {
        board.rowCount = 12;
        board.colCount = 12;
        board.mineCount = 40;
        board.isAllSet = true;
        cells = initCells();
    }

    bindInteractionHandlerToAI(_interactionHandler, this);
    bindInteractionhandlerToSoundHandler(_interactionHandler, _soundHandler);
    bindAIToSoundHandler(this, _soundHandler);

    emit gameInitialized();
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

            //Binds Signals and Slots
            bindCellsToInteractionHandler(foo, _interactionHandler);


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
        if ((randomRow != cell->coordinate.atRow) && (randomCol != cell->coordinate.atCol) && (cells->at(randomRow)->at(randomCol)->isMine != true)) {
            cells->at(randomRow)->at(randomCol)->isMine = true;
            foo -= 1;
        }
    }
    countNeighbourMines(cells);
    //qDebug("Mines Laid and counted");
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

//            if (foo->cellsAround() != NULL) {
//                FlatList *fooList = foo->cellsAround();
//                for (int i=0; i<fooList->count(); ++i) {
//                    if (fooList->at(i)->isMine) {
//                        foo->content += 1;
//                    }
//                }
//            }

        }
    }
}


void AI::revealCell(Cell *cell) {
    int foo = 0;
    if (-2 == cell->content) {
        layMines(cell);
    }

    if (cell->status == revealed && cell->content != 0) {

        FlatList *fooListToReveal = new FlatList;

//        if (cell->North->status == flagged) {
//            ++foo;
//        } else {
//            fooListToReveal->append(cell->North);
//        }

//        if (cell->NorthEast->status == flagged) {
//            ++foo;
//        } else {
//            fooListToReveal->append(cell->NorthEast);
//        }

//        if (cell->East->status == flagged) {
//            ++foo;
//        } else {
//            fooListToReveal->append(cell->East);
//        }

//        if (cell->SouthEast->status == flagged) {
//            ++foo;
//        } else {
//            fooListToReveal->append(cell->SouthEast);
//        }

//        if (cell->South->status == flagged) {
//            ++foo;
//        } else {
//            fooListToReveal->append(cell->South);
//        }

//        if (cell->SouthWest->status == flagged) {
//            ++foo;
//        } else {
//            fooListToReveal->append(cell->SouthWest);
//        }

//        if (cell->West->status == flagged) {
//            ++foo;
//        } else {
//            fooListToReveal->append(cell->West);
//        }

//        if (cell->NorthWest->status == flagged) {
//            ++foo;
//        } else {
//            fooListToReveal->append(cell->NorthWest);
//        }

        if (cell->cellsAround() != NULL) {
            FlatList *fooList = cell->cellsAround();
            for (int i=0; i<fooList->count(); ++i) {
                if (fooList->at(i)->status == flagged) {
                    foo += 1;
                } else {
                    fooListToReveal->append(fooList->at(i));
                }
            }
        }

        if (foo == cell->content) {

            for (int i=0; i<fooListToReveal->count(); ++i) {
                if (fooListToReveal->at(i)->status != revealed && fooListToReveal->at(i)->content != -2) {
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

//            if (cell->North->status == flagged) {
//                ++foo;
//            } else {
//                fooListToReveal->append(cell->North);
//            }

//            if (cell->NorthEast->status == flagged) {
//                ++foo;
//            } else {
//                fooListToReveal->append(cell->NorthEast);
//            }

//            if (cell->East->status == flagged) {
//                ++foo;
//            } else {
//                fooListToReveal->append(cell->East);
//            }

//            if (cell->SouthEast->status == flagged) {
//                ++foo;
//            } else {
//                fooListToReveal->append(cell->SouthEast);
//            }

//            if (cell->South->status == flagged) {
//                ++foo;
//            } else {
//                fooListToReveal->append(cell->South);
//            }

//            if (cell->SouthWest->status == flagged) {
//                ++foo;
//            } else {
//                fooListToReveal->append(cell->SouthWest);
//            }

//            if (cell->West->status == flagged) {
//                ++foo;
//            } else {
//                fooListToReveal->append(cell->West);
//            }

//            if (cell->NorthWest->status == flagged) {
//                ++foo;
//            } else {
//                fooListToReveal->append(cell->NorthWest);
//            }

            if (cell->cellsAround() != NULL) {
                FlatList *fooList = cell->cellsAround();
                for (int i=0; i<fooList->count(); ++i) {
                    if (fooList->at(i)->status == flagged) {
                        foo += 1;
                    } else {
                        fooListToReveal->append(fooList->at(i));
                    }
                }
            }

            //qDebug("I'm here");
            if (foo == cell->content) {
                //qDebug("entered if and content is %i", foo);
                for (int i=0; i<fooListToReveal->count(); ++i) {
                    //qDebug("entered for");
                    if (fooListToReveal->at(i)->status != revealed && fooListToReveal->at(i)->content != -2) {
                        revealCell(fooListToReveal->at(i));
                        //qDebug("recursively revealed");
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
        break;
    case questioned:
        cell->setStatus(virgin);
        break;
    default:
        break;
    }
}


void AI::bindCellsToInteractionHandler(Cell *cell, UserInteractionHandler *interactionHandler) {
    QObject::connect(cell, SIGNAL(statusChanged()), cell, SLOT(refreshUI()));

    QObject::connect(cell, SIGNAL(clicked(Cell*,QMouseEvent*)), interactionHandler, SLOT(interactionReceived(Cell*,QMouseEvent*)));
    QObject::connect(cell, SIGNAL(clicked_double(Cell*,QMouseEvent*)), interactionHandler, SLOT(interactionReceived_DoubleClick(Cell*,QMouseEvent*)));

    //cell was revealed
}


void AI::bindInteractionHandlerToAI(UserInteractionHandler *interactionHandler, AI *ai) {
    QObject::connect(interactionHandler, SIGNAL(clicked_left(Cell*)), ai, SLOT(revealCell(Cell*)));
    QObject::connect(interactionHandler, SIGNAL(clicked_right(Cell*)), ai, SLOT(rightClickACell(Cell*)));
    QObject::connect(interactionHandler, SIGNAL(clicked_double(Cell*)), ai, SLOT(revealCell(Cell*)));

}

void AI::bindInteractionhandlerToSoundHandler(UserInteractionHandler *interactionHandler, SoundHandler *soundHandler) {
    QObject::connect(interactionHandler, SIGNAL(clicked_left(Cell*)), soundHandler, SLOT(playLeftClickMusic()));
    QObject::connect(interactionHandler, SIGNAL(clicked_double(Cell*)), soundHandler, SLOT(playLeftClickMusic()));
    QObject::connect(interactionHandler, SIGNAL(clicked_right(Cell*)), soundHandler, SLOT(playRightClickMusic()));
}

void AI::bindAIToSoundHandler(AI *ai, SoundHandler *soundHandler) {
    QObject::connect(ai, SIGNAL(steppedOnAMine(Cell*)), soundHandler, SLOT(playExplosionMusic()));
    QObject::connect(ai, SIGNAL(gameInitialized()), soundHandler, SLOT(playBGM()));
}


void AI::pause() {

}


void AI::resume() {

}


void AI::restart() {
    QObject *obj = QObject::sender();
    if (obj->inherits("Preferences")) {
        Preferences *preferences = qobject_cast<Preferences *>(sender());
        board.rowCount = preferences->rowCount;
        board.colCount = preferences->colCount;
        board.mineCount = preferences->mineCount;
        cells = initCells(board.rowCount, board.colCount);
    } else {
        cells = initCells(board.rowCount, board.colCount);
    }
}


void AI::receivedNewPreferences(Preferences *preferences) {

}

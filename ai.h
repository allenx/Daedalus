#ifndef AI_H
#define AI_H

#include "cell.h"
#include "soundhandler.h"
#include <QList>


#include "userinteractionhandler.h"
#include "preferences.h"
#include "headerwrapper.h"

//Iterates the 8 pointers of a cell and apply the lambda function to them
template<typename Lambda>
void iterateCellsAround(Cell *cell, Lambda &&func) {
    if (cell->North != NULL) {
        func(cell->North);
    }
    if (cell->North != NULL) {
        func(cell->NorthEast);
    }
    if (cell->North != NULL) {
        func(cell->NorthWest);
    }
    if (cell->North != NULL) {
        
    }
    if (cell->North != NULL) {
        
    }
    if (cell->North != NULL) {
        
    }
    if (cell->North != NULL) {
        
    }
    if (cell->North != NULL) {
        
    }
    

    
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

//    Board(Preferences *preferences) {
//        isAllSet = true;
//        rowCount = preferences->rowCount;
//        colCount = preferences->colCount;
//        mineCount = preferences->mineCount;
//    }
};

class AI : public QObject
{

    Q_OBJECT

public:
    AI();
    Cell ***initCellsFoo(int rowCount, int columnCount);
    //QList<QList<Cell *> *> *initCells(int rowCount, int colCount);
    CellMatrix *initCells(int rowCount=12, int colCount=12);

    //Preferences *preferences;
    CellMatrix *cells;
    FlatList *mines;
    int flaggedCount;
    Board board;
    void layMines(Cell *);
    void countNeighbourMines(CellMatrix *cells);

signals:
    void steppedOnAMine(Cell *);
    void gameInitialized();


private:
    UserInteractionHandler *_interactionHandler;
    SoundHandler *_soundHandler;
    void bindCellsToInteractionHandler(Cell *, UserInteractionHandler *);
    void bindInteractionHandlerToAI(UserInteractionHandler *, AI *);
    void bindInteractionhandlerToSoundHandler(UserInteractionHandler *, SoundHandler *);
    void bindAIToSoundHandler(AI *, SoundHandler *);

public slots:
    void rightClickACell(Cell *);
    void revealCell(Cell *);
    void pause();
    void resume();
    void receivedNewPreferences(Preferences *);
    void restart();
};

#endif // AI_H

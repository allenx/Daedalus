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
    if (cell->North != nullptr) {
        func(cell->North);
    }
    if (cell->NorthEast != nullptr) {
        func(cell->NorthEast);
    }
    if (cell->NorthWest != nullptr) {
        func(cell->NorthWest);
    }
    if (cell->South != nullptr) {
        func(cell->South);
    }
    if (cell->SouthEast != nullptr) {
        func(cell->SouthEast);
    }
    if (cell->SouthWest != nullptr) {
        func(cell->SouthWest);
    }
    if (cell->East != nullptr) {
        func(cell->East);
    }
    if (cell->West != nullptr) {
        func(cell->West);
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
    int normalCellCount;

    int virginCellsLeft;
    int numberOfCellsRevealed;
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

    static AI &sharedInstance() {
        static AI instance;
        return instance;
    }
    AI();
    Cell ***initCellsFoo(int rowCount, int columnCount);
    //QList<QList<Cell *> *> *initCells(int rowCount, int colCount);
    CellMatrix *initCells(int rowCount=12, int colCount=12);

    //Preferences *preferences;
    CellMatrix *cells;
    FlatList *mines;
    //This could help the user see how many flags he's set
//    int flaggedCocunt;
    QString time;
    Board board;
    void layMines(Cell *clickedCell);
    void countNeighbourMines(CellMatrix *cells);
    void revealCell(Cell *);
    void judge();

signals:
    void steppedOnAMine(Cell *);
    void gameInitialized();
    void gameStarted();
    void waitingForTheTime();
    void succeeded();
    void reloadGame();
    void newWindowPopped();
    void topViewDismissed();

private:
    UserInteractionHandler *_interactionHandler;
    SoundHandler *_soundHandler;
    void bindCellsToInteractionHandler(Cell *, UserInteractionHandler *);
    void bindInteractionHandlerToAI(UserInteractionHandler *, AI *);
    void bindInteractionhandlerToSoundHandler(UserInteractionHandler *, SoundHandler *);
    void bindAIToSoundHandler(AI *, SoundHandler *);

public slots:
    void leftClickACell(Cell *);
    void rightClickACell(Cell *);
    void pause();
    void resume();
    void receivedNewPreferences(Preferences *);
    void userClickedRestart();
    void receivedTime(QString);
};

#endif // AI_H

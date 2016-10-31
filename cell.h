#ifndef CELL_H
#define CELL_H

#include <QObject>
#include <QLabel>
#include <QList>
#include <QHoverEvent>
#include "headerwrapper.h"

enum Status {
    virgin,
    flagged,
    questioned,
    revealed
};

struct Coordinate {
    int atRow;
    int atCol;
    Coordinate(int row, int col) {
        atRow = row;
        atCol = col;
    }
};

class Cell : public QLabel
{
    Q_OBJECT

public:
    Coordinate coordinate;
    int content;//0 - 8 means the numbers of mines around the cell.
    //-1 means it's a mine itself and -2 means it hasn't been handled by the AI yet.
    bool isMine;
    Status status;
    void setStatus(Status);
    Cell(int atRow, int atCol);
    FlatList *cellsAround();

    Cell *NorthWest,
    *North,
    *NorthEast,
    *East,
    *SouthEast,
    *South,
    *SouthWest,
    *West;

signals:
    void hovered();
    void clicked(Cell *, QMouseEvent *);
    void clicked_double(Cell *, QMouseEvent *);
    void wasRevealed(Cell *, QMouseEvent *);
    void statusChanged();

public slots:
    void refreshUI();


protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


};

#endif // CELL_H

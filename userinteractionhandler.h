#ifndef USERINTERACTIONHANDLER_H
#define USERINTERACTIONHANDLER_H

#include <QMouseEvent>
#include "cell.h"

class UserInteractionHandler : public QObject
{
    Q_OBJECT
public:
    explicit UserInteractionHandler(QObject *parent = 0);

signals:
//    void firstClicked_Left(Cell *);
//    void firstClicked_Right(Cell *);
//    void firstClicked_Double(Cell *);
    //The Above should be handled in the logic of an AI
    void clicked_left(Cell *);
    void clicked_right(Cell *);
    void clicked_double(Cell *);

//[TODO]: Simplify the slots into one
public slots:
    void interactionReceived(Cell *, QMouseEvent *);
    void interactionReceived_DoubleClick(Cell *, QMouseEvent *);
};

#endif // USERINTERACTIONHANDLER_H

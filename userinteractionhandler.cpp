#include "userinteractionhandler.h"

UserInteractionHandler::UserInteractionHandler(QObject *parent) : QObject(parent)
{

}


void UserInteractionHandler::interactionReceived(Cell *cell, QMouseEvent *event) {

        switch (event->button()) {
        case Qt::LeftButton:
            emit clicked_left(cell);
            break;
        case Qt::RightButton:
            emit clicked_right(cell);
            break;
        default:
            break;
        }

}


void UserInteractionHandler::interactionReceived_DoubleClick(Cell *cell, QMouseEvent *event) {

    switch (event->button()) {
    case Qt::LeftButton:
        emit clicked_double(cell);
        break;
    default:
        break;
    }

}

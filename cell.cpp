#include "cell.h"
#include <QDebug>
#include <QMouseEvent>

Cell::Cell(int row, int col) :
    coordinate(Coordinate(row, col)),
    content(-2),
    isMine(false),
    status(virgin)
{
   setFixedSize(25, 25);
   (new QPalette)->setColor(this->backgroundRole(), Qt::green);
   QPixmap pic(cellPic);

   setPixmap(pic.scaled(this->width(), this->height(), Qt::KeepAspectRatio));
}

void Cell::mousePressEvent(QMouseEvent *event) {
//    switch (event->button()) {
//    case Qt::LeftButton:
//        emit clicked_left(this, event);
//        break;
//    case Qt::RightButton:
//        emit clicked_right(this, event);
//    default:
//        break;
//    }
    emit clicked(this, event);
    qDebug("%i", this->content);
}

void Cell::mouseDoubleClickEvent(QMouseEvent *event) {
    emit clicked_double(this, event);
}

//bool Cell::isMine() {
//    if (-1 == this->content) {
//        return true;
//    } else {
//        return false;
//    }
//}

void Cell::setStatus(Status status) {
    this->status = status;
    emit statusChanged();
}


void Cell::refresh() {
    switch (status) {
    case virgin:
        setPixmap(QPixmap(cellPic).scaled(this->width(), this->height(), Qt::KeepAspectRatio));
        break;
    case flagged:
        setPixmap(QPixmap(flagPic).scaled(this->width(), this->height(), Qt::KeepAspectRatio));
        break;
    case questioned:
        setPixmap(QPixmap(flagPic).scaled(this->width(), this->height(), Qt::KeepAspectRatio));
        break;
    case revealed:
    {
        switch (content) {
        case -1:
            setPixmap(QPixmap(explosionPic).scaled(this->width(), this->height(), Qt::KeepAspectRatio));
            break;


        default:
            break;
        }
    }
    default:
        break;
    }
}

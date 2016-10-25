#include "cell.h"
#include <QDebug>
#include <QMouseEvent>

Cell::Cell(int row, int col) :
    coordinate(Coordinate(row, col)),
    content(-2),
    isMine(false),
    status(virgin)
{
   setFixedSize(30, 30);
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


void Cell::mouseReleaseEvent(QMouseEvent *event) {

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
    //qDebug("signal emitted");
}


void Cell::refreshUI() {

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
        case 0:
            //fuck with it
            break;
        case 1:
            setPixmap(QPixmap(one).scaled(this->width(), this->height(), Qt::KeepAspectRatio));
            break;
        case 2:
            setPixmap(QPixmap(two).scaled(this->width(), this->height(), Qt::KeepAspectRatio));
            break;
        case 3:
            setPixmap(QPixmap(three).scaled(this->width(), this->height(), Qt::KeepAspectRatio));
            break;
        case 4:
            setPixmap(QPixmap(four).scaled(this->width(), this->height(), Qt::KeepAspectRatio));
            break;
        case 5:
            setPixmap(QPixmap(five).scaled(this->width(), this->height(), Qt::KeepAspectRatio));
            break;
        case 6:
            setPixmap(QPixmap(six).scaled(this->width(), this->height(), Qt::KeepAspectRatio));
            break;
        case 7:
            setPixmap(QPixmap(seven).scaled(this->width(), this->height(), Qt::KeepAspectRatio));
            break;
        case 8:
            setPixmap(QPixmap(eight).scaled(this->width(), this->height(), Qt::KeepAspectRatio));
            break;
        default:
            break;
        }
    }
    default:
        break;
    }
}

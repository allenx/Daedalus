#include "adobeocrlabel.h"
#include <QFont>
#include <QBrush>
#include <QPalette>
#include <QDebug>

ADOBEOCRLabel::ADOBEOCRLabel(QColor textColor, QColor backgroundColor, QString text, QFont font)
{
    font.setPointSize(32);
    font.setBold(true);

    QPalette palette;
    //text color (white in default)
    QBrush brush(textColor);
    brush.setStyle(Qt::SolidPattern);

    //black background
    QBrush brush1(backgroundColor);
    brush1.setStyle(Qt::SolidPattern);

    //set cyan text
    palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
    palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);

    //set black background
    palette.setBrush(QPalette::Active, QPalette::Window, brush1);
    palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);


    this->setPalette(palette);
    this->setFont(font);
    this->setText(text);
    qDebug("label set");
}

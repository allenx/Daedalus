#ifndef ADOBEOCRLABEL_H
#define ADOBEOCRLABEL_H
#include <QLabel>
#include <QColor>

class ADOBEOCRLabel : public QLabel
{
public:
    ADOBEOCRLabel(QColor textColor, QColor backgroundColor, QString text, QFont font = QFont("OCR A STD"));
};

#endif // ADOBEOCRLABEL_H

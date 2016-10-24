#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QWidget>
#include <QGridLayout>
#include "ai.h"
#include "headerwrapper.h"


class GameField : public QWidget
{
    Q_OBJECT
public:
    explicit GameField(QWidget *parent = 0);

    CellMatrix *cells;
    AI *ai;
    bool hasBeenSetup;
    QGridLayout *layout;

//signals:

//public slots:
//    void setup(int, int);
};

#endif // GAMEFIELD_H

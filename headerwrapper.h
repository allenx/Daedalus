#ifndef HEADERWRAPPER_H
#define HEADERWRAPPER_H
//#define Matrix QList<QList<Cell *> *>
//The above is for some reason not working because Qt has a reserved class named Matrix
#define CellMatrix QList<QList<Cell *> *>
#define FlatList QList<Cell *>
#endif // HEADERWRAPPER_H

#include "resources.h"

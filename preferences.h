#ifndef PREFERENCES_H
#define PREFERENCES_H
#include <QObject>
#include <QDialog>

class Preferences : public QDialog
{
    Q_OBJECT

public:
    explicit Preferences();
    int rowCount;
    int colCount;
    int mineCount;

};

#endif // PREFERENCES_H

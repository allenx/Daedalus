#ifndef PREFERENCES_H
#define PREFERENCES_H
#include <QObject>
#include <QDialog>
#include <QDialogButtonBox>
#include <QSlider>
#include <QSpinBox>

class Preferences : public QDialog
{
    Q_OBJECT

signals:
    void accepted(Preferences *);

public:
    explicit Preferences();
    int rowCount;
    int colCount;
    int mineCount;

protected:
    QSlider *rowSlider;
    QSlider *colSlider;
    QSlider *mineSlider;

    QSpinBox *rowSpinBox;
    QSpinBox *colSpinBox;
    QSpinBox *mineSpinBox;

    QDialogButtonBox *buttonBox;
};

#endif // PREFERENCES_H

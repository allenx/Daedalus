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
    void rejected();
    void dismissed();

public:
    explicit Preferences();
    int rowCount;
    int colCount;
    int mineCount;

public slots:
    void accept();
    void reject();
    void refresh();

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

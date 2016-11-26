#include "preferences.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

Preferences::Preferences() :
    rowCount(0),
    colCount(0),
    mineCount(0),
    rowSlider(new QSlider(Qt::Horizontal)),
    colSlider(new QSlider(Qt::Horizontal)),
    mineSlider(new QSlider(Qt::Horizontal)),
    rowSpinBox(new QSpinBox),
    colSpinBox(new QSpinBox),
    mineSpinBox(new QSpinBox),
    buttonBox(new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok, this))
{
    //QObject::connect(this, SIGNAL(accepted()), this, SLOT(accept()));
    rowSlider->setRange(12, 50);
    colSlider->setRange(12, 50);
    //mineSlider->setRange();

    //rowSlider->setStyleSheet("background-color: white");


    QObject::connect(rowSlider, SIGNAL(valueChanged(int)), rowSpinBox, SLOT(setValue(int)));
    QObject::connect(colSlider, SIGNAL(valueChanged(int)), colSpinBox, SLOT(setValue(int)));
    QObject::connect(rowSpinBox, SIGNAL(valueChanged(int)), rowSlider, SLOT(setValue(int)));
    QObject::connect(colSpinBox, SIGNAL(valueChanged(int)), colSlider, SLOT(setValue(int)));

    QHBoxLayout *hLayout0 = new QHBoxLayout;
    hLayout0->addWidget(new QLabel("ROWS:"));
    hLayout0->addWidget(rowSlider);
    hLayout0->addWidget(rowSpinBox);

    QHBoxLayout *hLayout1 = new QHBoxLayout;
    hLayout1->addWidget(new QLabel("COLUMNS: "));
    hLayout1->addWidget(colSlider);
    hLayout1->addWidget(colSpinBox);

    QHBoxLayout *hLayout2 = new QHBoxLayout;
    hLayout2->addWidget(new QLabel("MINES: "));
    hLayout2->addWidget(mineSlider);
    hLayout2->addWidget(mineSpinBox);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayout0);
    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);
    vLayout->addWidget(buttonBox);

    //setStyleSheet("background-color: black");
    setLayout(vLayout);
}




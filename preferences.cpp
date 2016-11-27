#include "preferences.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include "ai.h"
#include <QDebug>

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
    QObject::connect(mineSlider, SIGNAL(valueChanged(int)), mineSpinBox, SLOT(setValue(int)));
    QObject::connect(mineSpinBox, SIGNAL(valueChanged(int)), mineSlider, SLOT(setValue(int)));

    QObject::connect(rowSlider, SIGNAL(valueChanged(int)), this, SLOT(refresh()));
    QObject::connect(colSlider, SIGNAL(valueChanged(int)), this, SLOT(refresh()));
    QObject::connect(rowSpinBox, SIGNAL(valueChanged(int)), this, SLOT(refresh()));
    QObject::connect(colSpinBox, SIGNAL(valueChanged(int)), this, SLOT(refresh()));
    QObject::connect(mineSlider, SIGNAL(valueChanged(int)), this, SLOT(refresh()));
    QObject::connect(mineSpinBox, SIGNAL(valueChanged(int)), this, SLOT(refresh()));

    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

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

    QObject::connect(this, SIGNAL(accepted(Preferences*)), &AI::sharedInstance(), SLOT(receivedNewPreferences(Preferences*)));
    QObject::connect(this, SIGNAL(rejected()), &AI::sharedInstance(), SLOT(resume()));
    QObject::connect(this, SIGNAL(dismissed()), &AI::sharedInstance(), SIGNAL(topViewDismissed()));

}


void Preferences::accept() {
    if ((rowCount > 0 || colCount > 0) && mineCount > 0) {
        this->done(1);
        connect(this, SIGNAL(accepted()), this, SIGNAL(dismissed()));
        emit accepted(this);
    } else {
        qDebug("nullll");
    }
}

void Preferences::reject() {
    this->done(0);
    connect(this, SIGNAL(rejected()), this, SIGNAL(dismissed()));
    emit rejected();
}

void Preferences::refresh() {
    rowCount = rowSlider->value();
    qDebug("rowCount: %i", rowCount);
    colCount = colSlider->value();
    mineCount = mineSlider->value();
}


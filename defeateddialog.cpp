#include "defeateddialog.h"
#include "adobeocrlabel.h"
#include <QPixmap>
#include "headerwrapper.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>


DefeatedDialog::DefeatedDialog()
{
    setStyleSheet("background-color: black");
    ADOBEOCRLabel *defeatedLabel = new ADOBEOCRLabel(QColor(255, 40, 0, 255), QColor(0, 0, 0, 255), "OOPS, YOU STEPPED ON A MINE!");
    QPixmap pic(frownPic);
    QLabel *frownFaceLabel = new QLabel;
    frownFaceLabel->setPixmap(pic);
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(new QLabel);
    hLayout->addWidget(frownFaceLabel);
    hLayout->addWidget(new QLabel);

    QPushButton *okBtn = new QPushButton("OKay");
    connect(okBtn, SIGNAL(released()), this, SLOT(done(int)));
    okBtn->setStyleSheet("background-color: blue, text-color:white");
    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayout);
    vLayout->addWidget(defeatedLabel);
    vLayout->addWidget(okBtn);
    this->setLayout(vLayout);
}

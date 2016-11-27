#include "winningdialog.h"
#include <QLabel>
#include "ai.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "adobeocrlabel.h"
#include <QPixmap>
#include "headerwrapper.h"

WinningDialog::WinningDialog()
{
    setStyleSheet("background-color: black");

    ADOBEOCRLabel *winningLabel = new ADOBEOCRLabel(QColor(0, 255, 40, 255), QColor(0, 0, 0, 255), "YOU WON! CONGRATS!!");
    ADOBEOCRLabel *timeLabel = new ADOBEOCRLabel(QColor(0, 228, 255, 255), QColor(0, 0, 0, 255), AI::sharedInstance().time);
    QPixmap pic(smilePic);
    QLabel *smileFaceLabel = new QLabel;
    smileFaceLabel->setPixmap(pic);
    QHBoxLayout *hLayout1 = new QHBoxLayout;
    hLayout1->addWidget(new QLabel);
    hLayout1->addWidget(smileFaceLabel);
    hLayout1->addWidget(new QLabel);
    QVBoxLayout *vLayout = new QVBoxLayout;
    QHBoxLayout *hLayout2 = new QHBoxLayout;
    QLabel *placeHolder1 = new QLabel;
    QLabel *placeHolder2 = new QLabel;
    hLayout2->addWidget(placeHolder1);
    hLayout2->addWidget(timeLabel);
    hLayout2->addWidget(placeHolder2);
    vLayout->addLayout(hLayout1);
    vLayout->addWidget(winningLabel);
    vLayout->addLayout(hLayout2);

    setLayout(vLayout);
}

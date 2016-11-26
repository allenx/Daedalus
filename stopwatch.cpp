#include "stopwatch.h"
#include <QHBoxLayout>
#include <QPushButton>
#include "ai.h"
#include <QFont>
#include <QPalette>


StopWatch::StopWatch(QWidget *parent) :
    QWidget(parent),
    mRunning(false),
    mStartTime(),
    //mLabel(new QLabel("0:0:0:0"))
    mLabel(new QLabel("0:0:0"))
{
    QHBoxLayout *hBoxLayout = new QHBoxLayout(this);
    //    QPushButton *startButton = new QPushButton("Start");
    //    QPushButton *stopButton = new QPushButton("Stop");

    //    hBoxLayout->addWidget(startButton);
    //    hBoxLayout->addWidget(stopButton);
    QFont font;
    font.setFamily("OCR A STD");
    //font.setItalic(true);
    font.setPointSize(32);
    font.setBold(true);

    QPalette palette;

    //white text
    QBrush brush(QColor(255, 255, 255, 255));
    brush.setStyle(Qt::SolidPattern);

    //black background
    QBrush brush1(QColor(0, 0, 0, 255));
    brush1.setStyle(Qt::SolidPattern);

    //set white text
    palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
    palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);

    //set black background
    palette.setBrush(QPalette::Active, QPalette::Window, brush1);
    palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);

    //set palette
    mLabel->setPalette(palette);

    mLabel->setFont(font);

    hBoxLayout->addWidget(mLabel);

    QObject::connect(&AI::sharedInstance(), SIGNAL(gameStarted()), SLOT(start()));
    //connect(stopButton, SIGNAL(clicked()), SLOT(stop()));

    startTimer(0);
}


void StopWatch::start(void) {
    mStartTime = QDateTime::currentDateTime();
    mRunning = true;
}


void StopWatch::stop(void) {
    mRunning = false;
}


void StopWatch::timerEvent(QTimerEvent *) {
    if(mRunning)
    {
        qint64 ms = mStartTime.msecsTo(QDateTime::currentDateTime());
        int h = ms / 1000 / 60 / 60;
        int m = (ms / 1000 / 60) - (h * 60);
        int s = (ms / 1000) - (m * 60);
        ms = ms - (s * 1000);
        //QString diff = QString("%1:%2:%3:%4").arg(h).arg(m).arg(s).arg(ms);
        QString diff = QString("%1:%2:%3").arg(h).arg(m).arg(s);
        mLabel->setText(diff);

    }
}

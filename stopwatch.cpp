#include "stopwatch.h"
#include <QHBoxLayout>
#include <QPushButton>
#include "ai.h"
#include <QFont>
#include <QPalette>
#include "headerwrapper.h"

StopWatch::StopWatch(QWidget *parent) :
    QWidget(parent),
    mRunning(false),
    mStartTime(),
    //mLabel(new QLabel("0:0:0:0"))
    mLabel(new ADOBEOCRLabel(QColor(0, 228, 255, 255), QColor(0, 0, 0, 255), "0:0:0"))
{
    QHBoxLayout *hBoxLayout = new QHBoxLayout(this);
    //    QPushButton *startButton = new QPushButton("Start");
    //    QPushButton *stopButton = new QPushButton("Stop");

    //    hBoxLayout->addWidget(startButton);
    //    hBoxLayout->addWidget(stopButton);

    hBoxLayout->addWidget(mLabel);
    QObject::connect(&AI::sharedInstance(), SIGNAL(gameStarted()), this, SLOT(start()));
    QObject::connect(&AI::sharedInstance(), SIGNAL(steppedOnAMine(Cell*)), this, SLOT(stop()));
    QObject::connect(&AI::sharedInstance(), SIGNAL(waitingForTheTime()), this, SLOT(stop()));
    QObject::connect(&AI::sharedInstance(), SIGNAL(newWindowPopped()), this, SLOT(pause()));
    QObject::connect(&AI::sharedInstance(), SIGNAL(topViewDismissed()), this, SLOT(resume()));
    QObject::connect(this, SIGNAL(watchStopped(QString)), &AI::sharedInstance(), SLOT(receivedTime(QString)));
    //connect(stopButton, SIGNAL(clicked()), SLOT(stop()));

    startTimer(0);
}


void StopWatch::start(void) {
    mStartTime = QDateTime::currentDateTime();
    mRunning = true;
}


void StopWatch::stop() {
    mRunning = false;
    disconnect(&AI::sharedInstance(), SIGNAL(steppedOnAMine(Cell*)), this, SLOT(stop()));
    disconnect(&AI::sharedInstance(), SIGNAL(waitingForTheTime()), this, SLOT(stop()));
    emit watchStopped(this->mLabel->text());
}

void StopWatch::pause() {
    //This does not stop timing because the timerEvent is still running in the background.
    //It just stops refreshing the UI
    //[FIXME]: to really stop the timing
    mRunning = false;
}

void StopWatch::resume() {
    //[FIXME]: to really resume
    mRunning = true;
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

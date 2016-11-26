#include "stopwatch.h"
#include <QHBoxLayout>
#include <QPushButton>


StopWatch::StopWatch(QWidget *parent) :
    QWidget(parent),
    mRunning(false),
    mStartTime(),
    mLabel(new QLabel("0:0:0:0"))
{
    QHBoxLayout *hBoxLayout = new QHBoxLayout(this);
    QPushButton *startButton = new QPushButton("Start");
    QPushButton *stopButton = new QPushButton("Stop");

    hBoxLayout->addWidget(startButton);
    hBoxLayout->addWidget(stopButton);
    hBoxLayout->addWidget(mLabel);

    connect(startButton, SIGNAL(clicked()), SLOT(start()));
    connect(stopButton, SIGNAL(clicked()), SLOT(stop()));

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
        QString diff = QString("%1:%2:%3:%4").arg(h).arg(m).arg(s).arg(ms);
        mLabel->setText(diff);
    }
}

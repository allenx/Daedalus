#include "timer.h"

Timer::Timer(QWidget *parent) : QLCDNumber(parent)
{
    setSegmentStyle(Filled);
    QTimer *timer = new QTimer(this);

}

void Timer::stopTiming() {

}

void Timer::pauseTiming() {

}

void Timer::startTiming() {

}

void Timer::resumeTiming() {

}

void Timer::showTime() {

}

#ifndef TIMER_H
#define TIMER_H
#include <QTimer>

class Timer : public QTimer
{
public:
    Timer();

public slots:
    void startTiming();
    void pauseTiming();
    void stopTiming();
    void resumeTiming();
};

#endif // TIMER_H

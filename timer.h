#ifndef TIMER_H
#define TIMER_H
#include <QLCDNumber>
#include <QTimer>

class Timer : public QLCDNumber
{
    Q_OBJECT
public:
    Timer(QWidget *parent = 0);

public slots:
    void startTiming();
    void pauseTiming();
    void stopTiming();
    void resumeTiming();
    void showTime();
};

#endif // TIMER_H

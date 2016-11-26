#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QWidget>
#include <QTimerEvent>
#include <QLabel>
#include <QDateTime>

class StopWatch : public QWidget
{
    Q_OBJECT
public:
    explicit StopWatch(QWidget *parent = 0);

public slots:
    void start(void);
    void stop(void);

protected:
    void timerEvent(QTimerEvent *);

private:
    bool mRunning;
    QDateTime mStartTime;
    QLabel *mLabel;
};

#endif // STOPWATCH_H

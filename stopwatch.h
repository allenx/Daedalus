#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QWidget>
#include <QTimerEvent>
#include <QLabel>
#include <QDateTime>
#include "adobeocrlabel.h"

class StopWatch : public QWidget
{
    Q_OBJECT
public:
    explicit StopWatch(QWidget *parent = 0);

signals:
    void watchStopped(QString);

public slots:
    void start(void);
    void stop(void);
    void pause(void);
    void resume(void);

protected:
    void timerEvent(QTimerEvent *);

private:
    bool mRunning;
    QDateTime mStartTime;
    ADOBEOCRLabel *mLabel;
};

#endif // STOPWATCH_H

#ifndef SOUNDHANDLER_H
#define SOUNDHANDLER_H

#include <QObject>
#include <QSound>
#include <QSoundEffect>
#include "resources.h"

class SoundHandler : public QObject
{
    Q_OBJECT



public:
    explicit SoundHandler(QObject *parent = 0);
    QSound * qsound;
signals:

public slots:
    void pauseMusic();
    void resumeMusic();
    void playBGM();
    void playLeftClickMusic();
    void playRightClickMusic();
    void playExplosionMusic();
    void playWinningMusic();
};

#endif // SOUNDHANDLER_H

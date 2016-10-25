#ifndef SOUNDHANDLER_H
#define SOUNDHANDLER_H

#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "resources.h"

class SoundHandler : public QObject
{
    Q_OBJECT

    QMediaPlayer *bgm;
    QMediaPlayer *leftClickMusic;
    QMediaPlayer *rightClickMusic;
    QMediaPlayer *explosionMusic;
    QMediaPlayer *winningMusic;
    QMediaPlaylist *playList;

public:
    explicit SoundHandler(QObject *parent = 0);

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

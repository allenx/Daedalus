#include "soundhandler.h"
#include <QDebug>

SoundHandler::SoundHandler(QObject *parent) :
    QObject(parent),
    bgm(new QMediaPlayer),
    leftClickMusic(new QMediaPlayer),
    rightClickMusic(new QMediaPlayer),
    explosionMusic(new QMediaPlayer),
    winningMusic(new QMediaPlayer),
    playList(new QMediaPlaylist)

{
    bgm->setMedia(QUrl::fromLocalFile(bgmSound));
    leftClickMusic->setMedia(QUrl::fromLocalFile(leftClickSound));
    rightClickMusic->setMedia(QUrl::fromLocalFile(rightClickSound));
    explosionMusic->setMedia(QUrl::fromLocalFile(explosionSound));
    winningMusic->setMedia(QUrl::fromLocalFile(winningSound));

}


void SoundHandler::playBGM() {
    //if statement

    bgm->play();
    qDebug("played");
}

void SoundHandler::playLeftClickMusic() {
    leftClickMusic->play();
}

void SoundHandler::playRightClickMusic() {
    rightClickMusic->play();
}

void SoundHandler::playWinningMusic() {

}

void SoundHandler::playExplosionMusic() {

}

void SoundHandler::pauseMusic() {

}

void SoundHandler::resumeMusic() {

}

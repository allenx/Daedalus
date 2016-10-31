#include "soundhandler.h"
#include <QDebug>
#include <QSoundEffect>
#include <QTimer>


SoundHandler::SoundHandler(QObject *parent) :
    QObject(parent)
{
    //qsound = QSound(bgmSound);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(playBGM())); // ***就是你所说的响应函数
    timer->start(6*60*1000+15*1000);

}

void SoundHandler::playBGM() {
    QSound::play(bgmSound);
}

void SoundHandler::playLeftClickMusic() {
    QSound::play(leftClickSound);
}

void SoundHandler::playRightClickMusic() {
    QSound::play(rightClickSound);
}

void SoundHandler::playWinningMusic() {
    QSound::play(explosionSound);
}

void SoundHandler::playExplosionMusic() {
    QSound::play(explosionSound);
}

void SoundHandler::pauseMusic() {

}

void SoundHandler::resumeMusic() {

}

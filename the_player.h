//
// Created by twak on 11/11/2019.
//

#ifndef CW2_THE_PLAYER_H
#define CW2_THE_PLAYER_H


#include <QApplication>
#include <QMediaPlayer>
#include <QSlider>
#include "mainwindow.h"
#include "the_button.h"
#include <vector>
#include <QTimer>

class ThePlayer : public QMediaPlayer {

Q_OBJECT

private:
    std::vector<TheButtonInfo>* infos;
    std::vector<TheButton*>* buttons;
    QTimer* mTimer;
    MainWindow *window;
    int storedVolume = 50;
    long updateCount = 0;
    int duration = 0;
    float minPlaybackRate = 0.5f;
    float maxPlaybackRate = 2.0f;
    float playbackRateIncrement = 0.5f;
    void setSpeedButtonLabel(double speedValue);

public:
    ThePlayer() : QMediaPlayer(NULL) {
        setVolume(storedVolume); // be slightly less annoying
        connect (this, SIGNAL (stateChanged(QMediaPlayer::State)), this, SLOT (playStateChanged(QMediaPlayer::State)) );

        mTimer = new QTimer(NULL);
        mTimer->setInterval(100); // 100ms is not one second between ...
        mTimer->start();
        connect( mTimer, SIGNAL (timeout()), SLOT ( updateProgressBar() ) ); // ...running shuffle method
    }

    // all buttons have been setup, store pointers here
    void setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i);
    void SetWindow(MainWindow *window);

private slots:

    // change the image and video for one button every one second
    void shuffle();
    void updateProgressBar();
    void playStateChanged (QMediaPlayer::State ms);
    void pauseOrPlay();
    void changePlaybackSpeed();
public slots:

    // start playing this ButtonInfo
    void jumpTo (TheButtonInfo* button);
    void changePalette();
    void mute();
};

#endif //CW2_THE_PLAYER_H

//
// Created by twak on 11/11/2019.
//

#include "mainwindow.h"
#include "the_player.h"
#include <iostream>

// all buttons have been setup, store pointers here
void ThePlayer::setContent(std::vector<TheButton*>* b, std::vector<TheButtonInfo>* i) {

    this->setPlaybackRate(1);
    window->speedButton->setText("x1.0");
    buttons = b;
    infos = i;
    jumpTo(buttons -> at(0) -> info);
}

// change the image and video for one button every one second
void ThePlayer::shuffle() {
    TheButtonInfo* i = & infos -> at (rand() % infos->size() );
    //setMedia(*i->url);
    buttons -> at( updateCount++ % buttons->size() ) -> init( i );
}

void ThePlayer::playStateChanged (QMediaPlayer::State ms) {
    switch (ms) {
        case QMediaPlayer::State::StoppedState:
            play(); // starting playing again...
            break;
    default:
        break;
    }
}

void ThePlayer::jumpTo (TheButtonInfo* button) {
    QMediaPlayer::connect(this, &QMediaPlayer::durationChanged, this, [&](qint64 dur) {
        duration = dur;});
    setMedia(*button -> url);
    play();
}

void ThePlayer::updateProgressBar()
{
    int time, minutes, seconds;
    time = this->position();
    minutes = time / 1000 / 60;
    seconds = (time / 1000) % 60;
    std::string middle = seconds >= 10 ? ":" : ":0";
    std::string currentTime = std::to_string(minutes) + middle + std::to_string(seconds);

    time = duration;
    minutes = time / 1000 / 60;
    seconds = (time / 1000) % 60;
    middle = seconds >= 10 ? ":" : ":0";
    std::string totalTime = std::to_string(minutes) + middle + std::to_string(seconds);

    std::string progressBarText = currentTime + " / " + totalTime;
    int ratio = 100 * static_cast<float>(this->position()) / static_cast<float>(duration);
    window->progressBar->setFormat(QString::fromStdString(progressBarText));
    window->progressBar->setValue(ratio);
}

void ThePlayer::changePlaybackSpeed()
{
    //calculate and set speed value
    double speed = this->playbackRate();
    if(speed >= maxPlaybackRate)
        this->setPlaybackRate(minPlaybackRate);
    else
        this->setPlaybackRate(speed + playbackRateIncrement);

    //reload video
    bool playOnRestart = true;
    if(this->state() != QMediaPlayer::PlayingState)
        playOnRestart = false;
    int position = this->position();
    setMedia(this->media());
    this->setPosition(position);
    if(!playOnRestart)
        pause();

    //update buttonLabel
    setSpeedButtonLabel(this->playbackRate());
}

void ThePlayer::setSpeedButtonLabel(double speedValue)
{
    std::string speedStr = std::to_string(speedValue);
    std::string speedButtonText = "x";
    int speedDp = 1;
    for(int i = 0; i < (int)speedStr.size() && i < speedDp+2; i++)
        speedButtonText += speedStr[i];
    window->speedButton->setText(QString::fromStdString(speedButtonText));
}

void ThePlayer::pauseOrPlay () {
    if(this->state() == QMediaPlayer::PlayingState)
        pause();
    else
        play();
}

void ThePlayer::mute()
{
    if(window == nullptr)
        return;
    if(this->volume() == 0)
        window->volumeSlider->setValue(storedVolume);
    else
    {
        storedVolume = this->volume();
        window->volumeSlider->setValue(0);
    }
}

void ThePlayer::changePalette()
{
    if(window->isNightThemeOn)
        window->SetDayPalette();
    else
        window->SetNightPalette();
    window->isNightThemeOn = !(window->isNightThemeOn);
}

void ThePlayer::SetWindow(MainWindow *otherWindow)
{
    window = otherWindow;
}
//k end

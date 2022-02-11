#ifndef QUEUE_H
#define QUEUE_H

#include "mainwindow.h"
#include "the_button.h"
#include "the_player.h"
#include <vector>



class queue : public QObject
{
Q_OBJECT
public:
    queue(std::vector<TheButton*>* buttons, QWidget* queueWidget, ThePlayer* player, MainWindow* window);
    ~queue();
//    virtual ~queue();
    TheButtonInfo* getVideo(int i);
    void removeVideo(int i);
    int getLength();
private:
    std::vector<TheButtonInfo> videoQueue;
    std::vector<TheButton*>* buttonsQueue;
    QWidget* queueWidget;
    ThePlayer* videoPlayer;
    MainWindow* window;

public slots:
    void addToQueue(TheButtonInfo* video);
};

#endif // QUEUE_H

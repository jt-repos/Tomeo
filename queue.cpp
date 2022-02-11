#include "queue.h"

queue::queue(std::vector<TheButton*>* buttons, QWidget* queueWidget, ThePlayer* player, MainWindow* window)
{
    buttonsQueue = buttons;
    this->queueWidget = queueWidget;
    videoPlayer = player;
    this->window = window;
}

queue::~queue()
{
    videoQueue.clear();
}

TheButtonInfo* queue::getVideo(int i)
{
//    TheButtonInfo* button = &videoQueue.front();
//    videoQueue.erase(videoQueue.begin());

    return &videoQueue.at(i);

}

void queue::removeVideo(int i)
{

    videoQueue.erase(videoQueue.begin()+i);
}

int queue::getLength()
{
    return videoQueue.size();
}
void queue::addToQueue(TheButtonInfo* video)
{
    videoQueue.push_back(*video);

    TheButton* button = new TheButton(queueWidget);
    button->connect(button, SIGNAL(jumpTo(TheButtonInfo*)), videoPlayer, SLOT (jumpTo(TheButtonInfo*))); // when clicked, tell the player to play.
    button->init(video);
    button->setMinimumSize(button->width, button->height);
    button->setMaximumSize(button->width, button->height);
    buttonsQueue->push_back(button);

    window->thumbnailsLayout -> addWidget(button);
    window->thumbnailButtonsWidget->setMinimumWidth(this->getLength()* button->width - 5);
    window->scrollHLayoutWidget->setMinimumWidth(this->getLength()* button->width - 5);

}

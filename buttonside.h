//
// Created by twak on 11/11/2019.
//


#ifndef CW2_THE_BUTTON_SIDE_H
#define CW2_THE_BUTTON_SIDE_H

#include <QPushButton>
#include <QUrl>
#include "the_button.h"

class TheButtonSide : public QPushButton {
    Q_OBJECT

public:
    TheButtonInfo* info;
    int iconHeight = 110;
    int iconWidth = 200;
     TheButtonSide(QWidget *parent) :  QPushButton(parent) {
         setIconSize(QSize(iconWidth, iconHeight));
         connect(this, SIGNAL(released()), this, SLOT (clicked() )); // if QPushButton clicked...then run clicked() below
    }

    void init(TheButtonInfo* i);

private slots:
    void clicked();

signals:
    void jumpTo(TheButtonInfo*);
//     void addToQ(TheButtonInfo* i);

};

#endif //CW2_THE_BUTTON_H

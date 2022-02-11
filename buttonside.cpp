//
// Created by twak on 11/11/2019.
//

#include "buttonside.h"
#include <QDir>
#include <string>
#include <iostream>
using namespace std;

void TheButtonSide::init(TheButtonInfo* i) {
    //setIcon( *(i->icon) );0
    int width = 150;
    int height = 30;
    this->setMinimumSize(width, height);
    QString subString = QDir(i->url->toString()).dirName();
    setText(subString);
    info =  i;
}

void TheButtonSide::clicked() {
//    emit addToQ(info);
    emit jumpTo(info);
}

//void TheButtonSide::addToQ(TheButtonInfo* i) {
//   cout << i->url;
//}

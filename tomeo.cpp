//    ______
//   /_  __/___  ____ ___  ___  ____
//    / / / __ \/ __ `__ \/ _ \/ __ \
//   / / / /_/ / / / / / /  __/ /_/ /
//  /_/  \____/_/ /_/ /_/\___/\____/
//              video for sports enthusiasts...
//
//  2811 cw3 : twak 11/11/2021
//

#include <iostream>
#include <QApplication>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlaylist>
#include <string>
#include <vector>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtCore/QFileInfo>
#include <QtWidgets/QFileIconProvider>
#include <QDesktopServices>
#include <QImageReader>
#include <QSlider>
#include <QMessageBox>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QScrollArea>
#include <string>
#include <string>
#include "the_player.h"
#include "the_button.h"
#include "mainwindow.h"
#include "queue.h"

#include "buttonside.h"

// read in videos and thumbnails to this directory
std::vector<TheButtonInfo> getInfoIn (std::string loc) {

    std::vector<TheButtonInfo> out =  std::vector<TheButtonInfo>();
    QDir dir(QString::fromStdString(loc) );
    QDirIterator it(dir);

    while (it.hasNext()) { // for all files

        QString f = it.next();

            if (f.contains("."))

#if defined(_WIN32)
            if (f.contains(".wmv"))  { // windows
#else
            if (f.contains(".mp4") || f.contains("MOV"))  { // mac/linux
#endif

            QString thumb = f.left( f .length() - 4) +".png";
            if (QFile(thumb).exists()) { // if a png thumbnail exists
                QImageReader *imageReader = new QImageReader(thumb);
                    QImage sprite = imageReader->read(); // read the thumbnail
                    if (!sprite.isNull()) {
                        QIcon* ico = new QIcon(QPixmap::fromImage(sprite)); // voodoo to create an icon for the button
                        QUrl* url = new QUrl(QUrl::fromLocalFile( f )); // convert the file location to a generic url
                        out . push_back(TheButtonInfo( url , ico  ) ); // add to the output list
                    }
                    else
                        qDebug() << "warning: skipping video because I couldn't process thumbnail " << thumb << endl;
            }
            else
                qDebug() << "warning: skipping video because I couldn't find thumbnail " << thumb << endl;
        }
    }

    return out;
}

int main(int argc, char *argv[]) {

    // let's just check that Qt is operational first
    qDebug() << "Qt version: " << QT_VERSION_STR << endl;

    // create the Qt Application
    QApplication app(argc, argv);

    // collect all the videos in the folder
    std::vector<TheButtonInfo> videos;



    if (argc == 2)
        videos = getInfoIn( std::string(argv[1]) );

    if (videos.size() == 0) {

        const int result = QMessageBox::question(
                    NULL,
                    QString("Tomeo"),
                    QString("no videos found! download, unzip, and add command line argument to \"quoted\" file location. Download videos from Tom's OneDrive?"),
                    QMessageBox::Yes |
                    QMessageBox::No );

        switch( result )
        {
        case QMessageBox::Yes:
          QDesktopServices::openUrl(QUrl("https://leeds365-my.sharepoint.com/:u:/g/personal/scstke_leeds_ac_uk/EcGntcL-K3JOiaZF4T_uaA4BHn6USbq2E55kF_BTfdpPag?e=n1qfuN"));
          break;
        default:
            break;
        }
        exit(-1);
    }
    MainWindow window;

    // the QMediaPlayer which controls the playback
    ThePlayer *player = new ThePlayer;
    player->setVideoOutput(window.videoWidget);
    player->SetWindow(&window);
    // a row of buttons
    QWidget *buttonWidget = new QWidget();
    // a list of the buttons
    std::vector<TheButton*> buttons;
    // the buttons are arranged horizontally
    QHBoxLayout *layout = new QHBoxLayout();
    buttonWidget->setLayout(layout);

    queue* vidQueue = new queue(&buttons, buttonWidget, player, &window);
    std::vector<TheButtonSide*> sidebuttons;

    // collect all the videos in the folder

    for(int i = 0; i < (int)videos.size(); i++) {
        TheButtonSide *videoButton = new TheButtonSide(buttonWidget);
        videoButton->connect(videoButton, SIGNAL(jumpTo(TheButtonInfo*)), vidQueue, SLOT (addToQueue(TheButtonInfo*))); // when clicked, add video to queue
        sidebuttons.push_back(videoButton);
        videoButton->init(&videos.at(i));
    }
    for(int i = 0; i < (int)videos.size(); i++)
        window.allVideos -> addWidget(sidebuttons[i]);
    window.scrollVLayoutWidget->setMinimumHeight(sidebuttons[0]->height()*videos.size());
    window.videoButtonsWidget->setMinimumHeight(sidebuttons[0]->height()*videos.size());

    window.volumeSlider->setValue(50); //make sure this is equal to initial stored volume
    QSlider::connect(window.volumeSlider, SIGNAL(valueChanged(int)), player, SLOT(setVolume(int)));
    QPushButton::connect(window.pausePlayButton, SIGNAL(clicked()), player, SLOT(pauseOrPlay()));
    QPushButton::connect(window.muteButton, SIGNAL(clicked()), player, SLOT(mute()));
    QPushButton::connect(window.speedButton, SIGNAL(clicked()), player, SLOT(changePlaybackSpeed()));
    QPushButton::connect(window.themeButton, SIGNAL(clicked()), player, SLOT(changePalette()));
    window.setWindowTitle("tomeo");
    window.setMinimumSize(800, 680);

    // showtime!
    window.show();
    // wait for the app to terminate
    return app.exec();
}

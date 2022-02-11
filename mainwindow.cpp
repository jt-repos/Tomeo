#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    videoWidget = ui->player;
    pausePlayButton = ui->pausePlay;
    volumeSlider = ui->volumeSlider;
    thumbnailsLayout = ui->thumbnailsLayout;
    muteButton = ui->mute;
    thumbnailButtonsWidget = ui->scrollAreaWidgetContents;
    videoButtonsWidget = ui->scrollAreaWidgetContents_2;
    scrollHLayoutWidget = ui->horizontalLayoutWidget;
    scrollVLayoutWidget = ui->verticalLayoutWidget;
    allVideos = ui->allVideos;
    progressBar = ui->progressBar;
    speedButton = ui->speedButton;
    themeButton = ui->themeButton;
}

void MainWindow::SetDayPalette()
{
    QPalette palette;
    QBrush brush(QColor(255, 255, 255, 255));
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
    QBrush brush1(QColor(48, 140, 198, 255));
    brush1.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Button, brush1);
    QBrush brush2(QColor(0, 0, 0, 255));
    brush2.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Text, brush2);
    palette.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
    QBrush brush3(QColor(238, 238, 236, 255));
    brush3.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Base, brush3);
    QBrush brush4(QColor(243, 243, 243, 255));
    brush4.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Window, brush4);
    palette.setBrush(QPalette::Active, QPalette::Shadow, brush3);
    QBrush brush5(QColor(35, 78, 163, 255));
    brush5.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Highlight, brush5);
    palette.setBrush(QPalette::Active, QPalette::HighlightedText, brush3);
    QBrush brush6(QColor(0, 0, 0, 128));
    brush6.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
    palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush6);
#endif
    palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
    palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
    palette.setBrush(QPalette::Inactive, QPalette::Text, brush2);
    palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
    palette.setBrush(QPalette::Inactive, QPalette::Base, brush3);
    palette.setBrush(QPalette::Inactive, QPalette::Window, brush4);
    palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush3);
    palette.setBrush(QPalette::Inactive, QPalette::Highlight, brush5);
    palette.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush3);
    QBrush brush7(QColor(255, 255, 255, 128));
    brush7.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
    palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush7);
#endif
    palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
    palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
    palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Base, brush4);
    palette.setBrush(QPalette::Disabled, QPalette::Window, brush4);
    palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush3);
    QBrush brush8(QColor(145, 145, 145, 255));
    brush8.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Disabled, QPalette::Highlight, brush8);
    palette.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush3);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
    palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush6);
#endif
    this->setPalette(palette);
}

void MainWindow::SetNightPalette()
{
    QPalette palette;
    QBrush brush(QColor(255, 255, 255, 255));
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
    QBrush brush1(QColor(245, 121, 0, 255));
    brush1.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Button, brush1);
    palette.setBrush(QPalette::Active, QPalette::Text, brush);
    QBrush brush2(QColor(0, 0, 0, 255));
    brush2.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
    QBrush brush3(QColor(46, 52, 54, 255));
    brush3.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Base, brush3);
    palette.setBrush(QPalette::Active, QPalette::Window, brush3);
    QBrush brush4(QColor(244, 116, 42, 255));
    brush4.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::Highlight, brush4);
    QBrush brush5(QColor(34, 34, 34, 255));
    brush5.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Active, QPalette::HighlightedText, brush5);
    QBrush brush6(QColor(0, 0, 0, 128));
    brush6.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
    palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush6);
#endif
    palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
    palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
    palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
    palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
    palette.setBrush(QPalette::Inactive, QPalette::Base, brush3);
    palette.setBrush(QPalette::Inactive, QPalette::Window, brush3);
    palette.setBrush(QPalette::Inactive, QPalette::Highlight, brush4);
    palette.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush5);
    QBrush brush7(QColor(255, 255, 255, 128));
    brush7.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
    palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush7);
#endif
    palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
    palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
    palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Base, brush3);
    palette.setBrush(QPalette::Disabled, QPalette::Window, brush3);
    QBrush brush8(QColor(145, 145, 145, 255));
    brush8.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::Disabled, QPalette::Highlight, brush8);
    palette.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush5);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
    palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush6);
#endif
    this->setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
}

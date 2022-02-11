#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVideoWidget>
#include <QHBoxLayout>
#include <QSlider>
#include <QPushButton>
#include <qprogressbar.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool isNightThemeOn = true;
    void SetDayPalette();
    void SetNightPalette();
    QVideoWidget *videoWidget;
    QHBoxLayout *thumbnailsLayout;
    QSlider *volumeSlider;
    QPushButton *pausePlayButton;
    QPushButton *muteButton;
    QWidget *thumbnailButtonsWidget;
    QWidget *videoButtonsWidget;
    QWidget* scrollHLayoutWidget;
    QWidget* scrollVLayoutWidget;
    QVBoxLayout *allVideos;
    QProgressBar *progressBar;
    QPushButton *speedButton;
    QPushButton *themeButton;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

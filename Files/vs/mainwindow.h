#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <direct.h>
#include "dirent.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fstream>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <QMainWindow>
#include <qfiledialog.h>
#include <QColorDialog>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <stdlib.h>
#include "threadd.h"
#include "controlthread.h"
using namespace std;
using namespace cv;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_starp_clicked();



    void on_Browse1_clicked();

    void on_Browse2_clicked();

    void on_color_clicked();

    void on_Browse3_clicked();

    void on_Browse4_clicked();

    void on_ploting_clicked();

    void on_pushButton_clicked();

    void on_PauseButton_clicked();

private:



    Ui::MainWindow *ui;
    VideoCapture a;

    void getValues();//read data from gui

    void clearData();//clear data values got from gui
    void readFile(); //read file to recreate plots
    bool sleepThread;
    //data to get from gui
    string path;
    string outPath;
    int dots;
    int tilt;
    string filepath;
    int fps;
    string mode,reference,filePath;
    int red,green,blue;
    //pointers to send to thread
    QLabel *rightRatio;
    QLabel *leftRatio;
    QLabel *stats;
    QCustomPlot *LeftGap,*RightGap,*LeftNoGap,*RightNoGap;
    QTextEdit *information;
    vector <QColor> colores;
    //led and dots variables
    Scalar lowNew;
    Scalar highNew;
    Scalar lowNewLED;
    Scalar highNewLED;

    vector<bool> gaps;
    int windowsOffset;


//thread to run all in background
    threadd th;




};

#endif // MAINWINDOW_H

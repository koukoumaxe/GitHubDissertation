#ifndef THREAD_H
#define THREAD_H

#include <QtCore>
#include <iostream>
#include <string>
#include <QLabel>
#include "qcustomplot.h"
#include <fstream>
#include <opencv2\opencv.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <direct.h>
#include "dirent.h"

using namespace std;
using namespace cv;
class threadd: public QThread
{

public:
    threadd();
   //variables from the gui
    bool isOn;
    QLabel *stats;
    QLabel *rightRatio;
    QLabel *leftRatio;
    QTextEdit*information;
    string textTofiles;
    string mode,reference,path,outPath,filePath;
    int windowsOffset,blue,red,green;
    QCustomPlot *LeftGap,*RightGap,*LeftNoGap,*RightNoGap;
    string filepath;
    vector<QColor>colores;
    bool *sleepThread;
    int dots;
    int tilt;

    //strutcs for the reading files
    struct dirent *dirp;
    struct stat filestat;

    //Dots and led values
    Scalar lowNew, highNew;
    Scalar LEDlow;
    Scalar LEDhigh;

    //vectors to keep track of data
    vector<bool> gaps;
    vector <int> LEDonoff;

vector<double> areasLeft[20];
vector<double> areas3Left[20];
vector<double> areas3Center[20];
vector<double> areasCenter[20];
vector<double> areasRight[20];
vector<double> areas3Right[20];
vector<double> diameterLeftOld;
vector<double> diameterCenterOld;
vector<double> diameterRightOld;
vector<double> diameterLeftNew;
vector<double> diameterCenterNew;
vector<double> diameterRightNew;
vector <double>averageLeft;
vector <double>averageRight;
vector <double>averageCenter;
vector <double> stdevLeft;
vector <double> stdevRight;
vector <double> stdevCenter;
vector<bool>tiltVector;
vector<double>tiltRate;

 static int const COLOR_SPOT_AREA_MIN=100;
 int contador,dif;
 //struct to keep values of dots
    struct CoordinateData
    {
   std:: vector<float> x0;
   std:: vector<float> y0;
    std::vector<float> x1;
    std::vector<float> y1;
    std::vector<float> x2;
    std::vector<float> y2;
    std::vector<float> magnitude0;
    std::vector<float> magnitude1;
    std::vector<float> magnitude2;
    std::vector<float> normalized0;
    std::vector<float> normalized2;
    };


    //recover values from main
    void setValues(string mode,string reference,string path,string outPath,string filePath,int windowsOffset,int blue,int red,int green, QCustomPlot *RightGap, QCustomPlot *LeftGap, QCustomPlot *RightNoGap, QCustomPlot *LeftNoGap,QLabel *stats,QTextEdit*information,vector<QColor>&colores,bool &sleepThread,QLabel *leftRatio,QLabel *rightRatio,int dots,int tilt);
    void run();//classic run
    void pause();//pause
    void readFile();//read the gaps-nogaps file
    void clearData();
    int process(VideoCapture& capture);
    int processWithWindows(VideoCapture& capture);
    bool isLED(Mat &matOriginalLED);
    bool isLEDWithWindows(Mat &matOriginalLED);
    void writeToFile(CoordinateData &coordData);//analisis of data not writing probably should be a good idea to change its name
    void findHigherValues(CoordinateData &coordData);//more analisis, ploting and writting to files
    ofstream csvOutput3;
    };

#endif // THREAD_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <list>
#include <stdlib.h>
#include<QVector>
#include <math.h>

//constants older colors
cv::Scalar const LOW_HSV_BLUE(60, 80, 40);
cv::Scalar const HIGH_HSV_BLUE(125, 255, 255);

cv::Scalar const LOW_HSV_PINK(170, 100, 100);
cv::Scalar const HIGH_HSV_PINK(179, 255, 255);
cv::Scalar const LOW_HSV_YELLOW(20, 100, 100);
cv::Scalar const HIGH_HSV_YELLOW(30, 255, 255);

cv::Scalar const LOW = LOW_HSV_BLUE;
cv::Scalar const HIGH = HIGH_HSV_BLUE;


Scalar LEDlow=Scalar(165,100,208);
Scalar LEDhigh=Scalar(179,255,255);
int const COLOR_SPOT_AREA_MIN = 100;


MainWindow::MainWindow(QWidget *parent) :   QMainWindow(parent),  ui(new Ui::MainWindow)
{
sleepThread =false;
    ui->setupUi(this);
   //example values
  /*  ui->path->setText("D:/videos");
    ui->outPath->setText("D:/");
    ui->txtPath->setText("D:/fileTest.txt");
    QPalette as;
    QColor color;
    color.setRgb(0,255,255);
    as.setColor(QPalette::Base,color);
    ui->areaColor->setPalette(as);*/

	/*
	Loizos Comments :
		These colours are the colours used for the "Trial Colour " board
	*/
    //colors lines for graphs

    QPalette arrPalettes[20];
    colores.push_back(QColor(255,0,0));
    colores.push_back(QColor(170,0,255));
    colores.push_back(QColor(0,85,255));
    colores.push_back(QColor(85,85,0));
    colores.push_back(QColor(85,0,255));
    colores.push_back(QColor(0,85,0));
    colores.push_back(QColor(255,170,0));
    colores.push_back(QColor(255,85,255));
    colores.push_back(QColor(0,170,0));
    colores.push_back(QColor(170,170,255));
    colores.push_back(QColor(0,255,0));
    colores.push_back(QColor(0,255,255));
    colores.push_back(QColor(255,255,0));
    colores.push_back(QColor(170,85,0));
    colores.push_back(QColor(255,170,127));
    colores.push_back(QColor(170,255,0));
    colores.push_back(QColor(80,80,127));
    colores.push_back(QColor(85,170,255));
    colores.push_back(QColor(81,170,184));
    colores.push_back(QColor(150,150,150));

    for (int i=0;i<20;i++)
        arrPalettes[i].setColor(QPalette::Base,colores[i]);
    ui->color0->setPalette(arrPalettes[0]);
    ui->color1->setPalette(arrPalettes[1]);
    ui->color2->setPalette(arrPalettes[2]);
    ui->color3->setPalette(arrPalettes[3]);
    ui->color4->setPalette(arrPalettes[4]);
    ui->color5->setPalette(arrPalettes[5]);
    ui->color6->setPalette(arrPalettes[6]);
    ui->color7->setPalette(arrPalettes[7]);
    ui->color8->setPalette(arrPalettes[8]);
    ui->color9->setPalette(arrPalettes[9]);
    ui->color10->setPalette(arrPalettes[10]);
    ui->color11->setPalette(arrPalettes[11]);
    ui->color12->setPalette(arrPalettes[12]);
    ui->color13->setPalette(arrPalettes[13]);
    ui->color14->setPalette(arrPalettes[14]);
    ui->color15->setPalette(arrPalettes[15]);
    ui->color16->setPalette(arrPalettes[16]);
    ui->color17->setPalette(arrPalettes[17]);
    ui->color18->setPalette(arrPalettes[18]);
    ui->color19->setPalette(arrPalettes[19]);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//read values from gui
void MainWindow::getValues(){
    dots=ui->dots->text().toInt();
    tilt=ui->tilt->text().toInt();
    RightGap=ui->RightGap;
    LeftGap =ui->LeftGap;
    RightNoGap=ui->RightNoGap;
    LeftNoGap=ui->LeftNoGap;
    information=ui->Information;
    stats=ui->problems;
    rightRatio=ui->RightRatio;
    leftRatio=ui->LeftRatio;

    if(ui->fps3->text().toInt()!=0){
    fps=ui->fps3->text().toInt();

    }else{

    fps=ui->fps->currentText().toInt();}
    int ratio=fps/420;
    windowsOffset=30*ratio;
    mode=ui->mode->currentText().toStdString();

    reference="Center";
    path=ui->path->text().toStdString();
    outPath=ui->outPath->text().toStdString();

    blue=ui->areaColor->palette().base( ).color().blue();
    red=ui->areaColor->palette().base( ).color().red();
    green=ui->areaColor->palette().base( ).color().green();
    filePath=ui->txtPath->text().toStdString();


}

void MainWindow::clearData(){

    gaps.clear();
    blue,red,green=0;
    mode,reference,path,outPath="";



}
void MainWindow::readFile()throw (invalid_argument){
    ifstream data_file;
    int temp;

    data_file.open(filePath.c_str());

    if(data_file.fail())
        throw invalid_argument("no file exists " + filePath);

    while(data_file >> temp)
        gaps.push_back(temp);

    data_file.close();
}

void MainWindow::on_starp_clicked()
{
    //get values and clear graphs
    getValues();
    information->clear();
    RightNoGap->clearGraphs();
    RightGap->clearGraphs();
    LeftGap->clearGraphs();
    LeftNoGap->clearGraphs();
    RightNoGap->replot();
    RightGap->replot();
    LeftGap->replot();
    LeftNoGap->replot();
    //Check if there are missing values if ok send parameters to thread and start it
    if(path==""||outPath==""||filePath==""||dots==0){
        information->append("Missing values");
    }else{
    th.setValues(mode,reference,path,outPath,filePath,windowsOffset,blue,red,green,RightGap,LeftGap,RightNoGap,LeftNoGap,stats,information,colores,sleepThread,leftRatio,rightRatio,dots,tilt);
    cout<<"1"<<endl;
    th.start();}



}




//brwosing buttons
void MainWindow::on_Browse1_clicked()
{
    QString fileNames = QFileDialog::getExistingDirectory(this,
                                                          tr("Choose Or Create Directory"),"/home",  QFileDialog::DontResolveSymlinks);
    ui->path->setText(fileNames);
}

void MainWindow::on_Browse2_clicked()
{
    QString fileNames = QFileDialog::getExistingDirectory(this,
                                                          tr("Choose Or Create Directory"),"/home",  QFileDialog::DontResolveSymlinks);
    ui->outPath->setText(fileNames);
}

void MainWindow::on_color_clicked()
{
    QPalette pa;
    QColor color=QColorDialog::getColor(Qt::white,this);
    pa.setColor(QPalette::Base,color);
    ui->areaColor->setPalette(pa);

}



void MainWindow::on_Browse3_clicked()
{
    QString fileNames = QFileDialog::getOpenFileName(this,
                                                     tr("Open file"),"/home", tr( "Text files (*.txt)"));
    ui->txtPath->setText(fileNames);
}

void MainWindow::on_Browse4_clicked()
{
    QString fileNames = QFileDialog::getOpenFileName(this,
                                                     tr("Open file"),"/home", tr( "CSV files (*.csv)"));
    ui->plotPath->setText(fileNames);
}

//recreate plots
void MainWindow::on_ploting_clicked()
{
    int offSet;
    QVector <double> nox(0); //x axis
    QVector<double>biggestGraphValue; //highest peak serie
    //arrays containing the color for gaps and no gaps
    vector<int>colorGap;
    vector<int>colorNoGap;
    QColor Color;
    //qvectors for the values (series)
    QVector<double> GraphValuesLeftGapQVector[20];
    QVector<double> GraphValuesLeftNoGapQVector[20];
    QVector<double> GraphValuesRightGapQVector[20];
    QVector<double> GraphValuesRightNoGapQVector[20];
    //reading the charts from gui and cleaning
    RightGap=ui->RightGap;
    LeftGap =ui->LeftGap;
    RightNoGap=ui->RightNoGap;
    LeftNoGap=ui->LeftNoGap;
    RightNoGap->clearGraphs();
    RightGap->clearGraphs();
    LeftGap->clearGraphs();
    LeftNoGap->clearGraphs();
    RightNoGap-> replot();
    RightGap-> replot();
    LeftGap-> replot();
    LeftNoGap-> replot();
    //open file
    ifstream data_file;
    string path=ui->plotPath->text().toStdString();
    data_file.open(path.c_str());
    string temp;
    if(data_file.fail())
        ui->problems->setText("fail open");
    int a=0;


    while(data_file >> temp){
        vector<string> arr;

        size_t pos = 0;
        string token;
        //read lines separing by commas until first item of the line is an integer
        while ((pos = temp.find(",")) != std::string::npos) {
            token = temp.substr(0, pos);

            arr.push_back(token);
            temp.erase(0, pos + 1);
        }

        string s=arr[0];

        QString line=s.c_str();
        int k=line.toInt();
        //if is integer read that number of lines to put the values in vectors and add to graph but first add the biggest value
        //first iteration highest peak, the last iteration of each is avg
        if(k){
            a++;
            for(int i=0;i<k;i++){
                data_file>>temp;
                vector<string> arr2;

                pos = 0;
                while ((pos = temp.find(",")) != std::string::npos) {
                    token = temp.substr(0, pos);

                    arr2.push_back(token);
                    temp.erase(0, pos + 1);
                }

                if(a==1&&i==0){
                    for(int j=0;j<arr2.size();j++){
                        nox.append(j);
                    }
                }

                if(a==1){
                    for(int j=1;j<arr2.size();j++){
                        string otherTemp=arr2[j];
                        QString otherTemp2=otherTemp.c_str();
                        biggestGraphValue.push_back(otherTemp2.toDouble());
                    }

                }
                if(a==2){


                    if(i<k-1)
                        colorNoGap.push_back(stod(arr2[0]));
                    for(int j=1;j<arr2.size();j++){
                        string otherTemp=arr2[j];
                        QString otherTemp2=otherTemp.c_str();
                        GraphValuesLeftNoGapQVector[i].push_back(otherTemp2.toDouble());


                    }

                    Color.setRgb(rand() % 100 + 100,rand() % 100 + 100,rand() % 100 + 100);

                    if(i==k-1)
                        Color.setRgb(0,0,0);
                    if(i==0){
                        LeftNoGap->addGraph();
                        LeftNoGap->graph(0)->setPen(colores[colorNoGap[i]]);
                        LeftNoGap->graph(0)->setData(nox,biggestGraphValue);
                        LeftNoGap->graph(0)->rescaleAxes();
                        LeftNoGap->graph(i)->setData(nox, GraphValuesLeftNoGapQVector[i]);
                        LeftNoGap->graph(i)->rescaleAxes(true);

                    }
                    if(i!=k-1&&i>0){
                        LeftNoGap->addGraph();
                        LeftNoGap->graph(i)->setPen(colores[colorNoGap[i]]);
                        LeftNoGap->graph(i)->setData(nox, GraphValuesLeftNoGapQVector[i]);
                        LeftNoGap->graph(i)->rescaleAxes(true);
                    }
                    if(i==k-1){
                        LeftNoGap->addGraph();
                        QPen pen;
                        pen.setColor(Color);
                        pen.setWidth(3);
                        LeftNoGap->graph(i)->setPen(pen);
                        LeftNoGap->graph(i)->setData(nox, GraphValuesLeftNoGapQVector[i]);
                        LeftNoGap->graph(i)->rescaleAxes(true);}





                }

                if(a==3){

                    for(int j=1;j<arr2.size();j++){

                        string otherTemp=arr2[j];
                        QString otherTemp2=otherTemp.c_str();
                        GraphValuesRightNoGapQVector[i].push_back(otherTemp2.toDouble());
                    }

                    Color.setRgb(rand() % 100 + 100,rand() % 100 + 100,rand() % 100 + 100);


                    if(i==k-1)
                        Color.setRgb(0,0,0);
                    if(i==0){
                        RightNoGap->addGraph();
                        RightNoGap->graph(0)->setPen(colores[colorNoGap[i]]);
                        RightNoGap->graph(0)->setData(nox,biggestGraphValue);
                        RightNoGap->graph(0)->rescaleAxes();
                        RightNoGap->graph(i)->setData(nox, GraphValuesRightNoGapQVector[i]);
                        RightNoGap->graph(i)->rescaleAxes(true);

                    }
                    if(i!=k-1&&i>0){
                        RightNoGap->addGraph();
                        RightNoGap->graph(i)->setPen(colores[colorNoGap[i]]);
                        RightNoGap->graph(i)->setData(nox, GraphValuesRightNoGapQVector[i]);
                        RightNoGap->graph(i)->rescaleAxes(true);
                    }
                    if(i==k-1){
                        RightNoGap->addGraph();
                        QPen pen;
                        pen.setColor(Color);
                        pen.setWidth(3);
                        RightNoGap->graph(i)->setPen(pen);
                        RightNoGap->graph(i)->setData(nox, GraphValuesRightNoGapQVector[i]);
                        RightNoGap->graph(i)->rescaleAxes(true);}

                }
                if(a==4){

                    if(i<k-1)
                        colorGap.push_back(stod(arr2[0]));
                    for(int j=1;j<arr2.size();j++){
                        string otherTemp=arr2[j];
                        QString otherTemp2=otherTemp.c_str();
                        GraphValuesLeftGapQVector[i].push_back(otherTemp2.toDouble());
                    }
                    Color.setRgb(rand() % 100 + 100,rand() % 100 + 100,rand() % 100 + 100);

                    if(i==k-1)
                        Color.setRgb(0,0,0);
                    if(i==0){
                        LeftGap->addGraph();
                        LeftGap->graph(0)->setPen(colores[colorGap[i]]);
                        LeftGap->graph(0)->setData(nox,biggestGraphValue);
                        LeftGap->graph(0)->rescaleAxes();
                        LeftGap->graph(i)->setData(nox, GraphValuesLeftGapQVector[i]);
                        LeftGap->graph(i)->rescaleAxes(true);

                    }
                    if(i!=k-1&&i>0){
                        LeftGap->addGraph();
                        LeftGap->graph(i)->setPen(colores[colorGap[i]]);
                        LeftGap->graph(i)->setData(nox, GraphValuesLeftGapQVector[i]);
                        LeftGap->graph(i)->rescaleAxes(true);
                    }
                    if(i==k-1){
                        LeftGap->addGraph();
                        QPen pen;
                        pen.setColor(Color);
                        pen.setWidth(3);
                        LeftGap->graph(i)->setPen(pen);
                        LeftGap->graph(i)->setData(nox, GraphValuesLeftGapQVector[i]);
                        LeftGap->graph(i)->rescaleAxes(true);}

                }
                if(a==5){
                    for(int j=1;j<arr2.size();j++){
                        string otherTemp=arr2[j];
                        QString otherTemp2=otherTemp.c_str();
                        GraphValuesRightGapQVector[i].push_back(otherTemp2.toDouble());
                    }
                    Color.setRgb(rand() % 100 + 100,rand() % 100 + 100,rand() % 100 + 100);

                    if(i==k-1)
                        Color.setRgb(0,0,0);
                    if(i==0){
                        RightGap->addGraph();
                        RightGap->graph(0)->setPen(colores[colorGap[i]]);
                        RightGap->graph(0)->setData(nox,biggestGraphValue);
                        RightGap->graph(0)->rescaleAxes();
                        RightGap->graph(i)->setData(nox, GraphValuesRightGapQVector[i]);
                        RightGap->graph(i)->rescaleAxes(true);

                    }
                    if(i!=k-1&&i>0){
                        RightGap->addGraph();
                        RightGap->graph(i)->setPen(colores[colorGap[i]]);
                        RightGap->graph(i)->setData(nox, GraphValuesRightGapQVector[i]);
                        RightGap->graph(i)->rescaleAxes(true);
                    }
                    if(i==k-1){
                        RightGap->addGraph();
                        QPen pen;
                        pen.setColor(Color);
                        pen.setWidth(3);
                        RightGap->graph(i)->setPen(pen);
                        RightGap->graph(i)->setData(nox, GraphValuesRightGapQVector[i]);
                        RightGap->graph(i)->rescaleAxes(true);}
                }

            }

        }
    }
    //replot
    LeftNoGap->xAxis2->setVisible(true);
    LeftNoGap->xAxis2->setTickLabels(false);
    LeftNoGap->yAxis2->setVisible(true);
    LeftNoGap->yAxis2->setTickLabels(false);
    LeftNoGap->replot();
    LeftGap->xAxis2->setVisible(true);
    LeftGap->xAxis2->setTickLabels(false);
    LeftGap->yAxis2->setVisible(true);
    LeftGap->yAxis2->setTickLabels(false);
    LeftGap->replot();
    RightNoGap->xAxis2->setVisible(true);
    RightNoGap->xAxis2->setTickLabels(false);
    RightNoGap->yAxis2->setVisible(true);
    RightNoGap->yAxis2->setTickLabels(false);
    RightNoGap->replot();
    RightGap->xAxis2->setVisible(true);
    RightGap->xAxis2->setTickLabels(false);
    RightGap->yAxis2->setVisible(true);
    RightGap->yAxis2->setTickLabels(false);
    RightGap->replot();


    data_file.close();

}

void MainWindow::on_pushButton_clicked()
{
sleepThread=true;

}
//pause button change the value of the bool that is accessed by thread also
void MainWindow::on_PauseButton_clicked()
{
sleepThread=!sleepThread;
if(sleepThread)
    ui->PauseButton->setText("Unpause");
if(!sleepThread)
    ui->PauseButton->setText("Pause");
}

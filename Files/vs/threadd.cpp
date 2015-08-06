#include "threadd.h"

threadd::threadd()
{

}
//set values including LEDs
void threadd::setValues(string mode, string reference, string path, string outPath, string filePath, int windowsOffset, int blue, int red, int green, QCustomPlot *RightGap, QCustomPlot *LeftGap, QCustomPlot *RightNoGap, QCustomPlot *LeftNoGap, QLabel* stats, QTextEdit*information, vector<QColor>&colores, bool &sleepThread, QLabel *leftRatio, QLabel *rightRatio, int dots, int tilt){

	LEDlow = Scalar(165, 100, 208);
	//     LEDlow=Scalar(120,0,70);//work kinda square
	LEDhigh = Scalar(179, 255, 255);
	//   LEDhigh=Scalar(179,186,255);//work kinda square
	this->mode = mode;
	this->reference = reference;
	this->path = path;
	this->outPath = outPath;
	this->filePath = filePath;
	this->windowsOffset = windowsOffset;
	this->blue = blue;
	this->red = red;
	this->green = green;
	this->RightNoGap = RightNoGap;
	this->RightGap = RightGap;
	this->LeftGap = LeftGap;
	this->LeftNoGap = LeftNoGap;
	this->stats = stats;
	this->information = information;
	this->colores = colores;
	this->sleepThread = &sleepThread;
	this->rightRatio = rightRatio;
	this->leftRatio = leftRatio;
	this->dots = dots;
	this->tilt = tilt;
}

//read gaps-nogaps file
void threadd::readFile(){
	ifstream data_file;
	int temp;

	data_file.open(filePath.c_str());

	if (data_file.fail())
		throw invalid_argument("no file exists " + filePath);

	while (data_file >> temp)
		gaps.push_back(temp);
	data_file.close();

}
void threadd::clearData(){
	gaps.clear();
	blue, red, green = 0;
	mode, reference, path, outPath = "";
}

void threadd::run(){

	readFile();
	Mat a(100, 100, CV_8UC3);
	Mat b;
	//set mat to color then transpose to hsv
	a.setTo(Scalar(red, green, blue));
	cvtColor(a, b, COLOR_RGB2HSV);
	Vec3b hsv = b.at<Vec3b>(50, 50);
	//set ranges
	lowNew = Scalar(hsv.val[0] - 10, 100, 100);

	if (hsv.val[0] > 70 && hsv.val[0] < 100)
		lowNew = Scalar(hsv.val[0] - 10, 80, 40);

	highNew = Scalar(hsv.val[0] + 20, 255, 255);
	cout << "2" << endl;

	//validate if paths exist
	if (path == ""){
		stats->setText("Couldn't find in path");

	}
	else   if (outPath == ""){
		stats->setText("Couldn't find out path");

	}
	else{
		//open dir and search for files
		DIR *dp;
		dp = opendir(path.c_str());
		if (dp == NULL)
		{


		}
		else{


		}
		while ((dirp = readdir(dp)))
		{   //reset thing for next file
			cout << "7" << endl;
			contador = 0;
			textTofiles = "";
			dif = 0;
			for (int i = 0; i < 20; i++){
				areasLeft[i].clear();
				areasCenter[i].clear();
				areas3Center[i].clear();
				areas3Left[i].clear();
				areasRight[i].clear();
				areas3Right[i].clear();
				averageLeft.clear();
				averageRight.clear();
				stdevLeft.clear();
				stdevRight.clear();
				tiltRate.clear();
				tiltVector.clear();
			}
			isOn = false;
			filepath = path + "/" + dirp->d_name;
			//if it is a directory or invalid
			if (stat(filepath.c_str(), &filestat)) continue;
			if (S_ISDIR(filestat.st_mode))         continue;

			//open files



			cv::VideoCapture capture(filepath); //try to open string, this will attempt to open it as a video file
			if (!capture.isOpened()) {
				QString a = filepath.c_str();
				information->append("Couldn't open file " + a);
				//if cant open file go to next
				continue;

			}
			else{
				//print in file relevant information about the cconfig
				string  s = outPath + "/" + dirp->d_name + "Info.txt";
				cout << s.c_str() << endl;
				csvOutput3.open(s.c_str());
				QString a = filepath.c_str();
				cout << "opening file" << endl;
				information->append("Opened file " + a);
				cout << "opening file" << endl;
				Sleep(10);
				csvOutput3 << "Opened file" << a.toStdString().c_str() << endl;
				Sleep(10);
				cout << "opening file" << endl;
				csvOutput3 << "Output directory:" << outPath << endl;
				Sleep(10);
				cout << "opening file" << endl;
				csvOutput3 << "Color RGB set:(" << red << "," << green << "," << blue << ")" << endl;
				cout << "opening file" << endl;
				csvOutput3 << "FPS:" << windowsOffset * 14 << endl;
				Sleep(10);
				csvOutput3 << "Gaps File:" << this->filePath << endl;
				Sleep(10);
				cout << "opening file" << endl;
				//depending the mode the function to call
				if (mode == "No Windows"){
					cout << "mode" << endl;
					process(capture);
				}


				if (mode == "Windows")
					processWithWindows(capture);

			}
		}

	}

	clearData();


}
/*
Loizos comments:
LED detection
*/
bool threadd::isLED(Mat &matOriginalLED){
	Mat imgHSV;
	cvtColor(matOriginalLED, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

	Mat imgThresholded;

	inRange(imgHSV, LEDlow, LEDhigh, imgThresholded); //Threshold the image

	//morphological opening (remove small objects from the foreground)
	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

	//morphological closing (fill small holes in the foreground)
	dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

	vector<vector<cv::Point> > vecContours;
	findContours(imgThresholded, vecContours, RETR_EXTERNAL, CHAIN_APPROX_NONE);



	for (int i = 0; i < vecContours.size(); i++)
	{
		cout << "isLED" << endl;
		//check if there is a LED
		if (contourArea(vecContours[i]) > 10) {
			if (isOn == false){
				cout << "before returning" << endl;
				contador++;
				dif = 0;
			}
			isOn = true;
			cout << "before returning" << endl;
			return isOn;

		}
	}
	//have a 10 frames slack to avoid the problems of 1 frame is not seeing then next would count as a new led
	if (vecContours.size() == 0){
		if (dif > 10)
			isOn = false;
		dif++;
	}

	return isOn;
}

bool threadd::isLEDWithWindows(Mat &matOriginalLED){
	Mat imgHSV;
	cvtColor(matOriginalLED, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

	Mat imgThresholded;

	inRange(imgHSV, LEDlow, LEDhigh, imgThresholded); //Threshold the image

	//morphological opening (remove small objects from the foreground)
	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

	//morphological closing (fill small holes in the foreground)
	dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	Mat matDrawContoursLED = Mat::zeros(imgThresholded.size(), CV_8UC3);
	vector<vector<cv::Point> > vecContours;
	findContours(imgThresholded, vecContours, RETR_EXTERNAL, CHAIN_APPROX_NONE);



	for (int i = 0; i < vecContours.size(); i++)
	{
		//check if there is a LED
		if (contourArea(vecContours[i]) > 10) {
			if (isOn == false){
				contador++;
				dif = 0;
			}
			isOn = true;
			//draw the led in the windows
			drawContours(matDrawContoursLED, vecContours, i, Scalar(0, 255, 0), -1, 8);
			imshow("LED Image", matDrawContoursLED); //show the thresholded image
			return isOn;


		}
	}
	//have a 10 frames slack to avoid the problems of 1 frame is not seeing then next would count as a new led
	if (vecContours.size() == 0){
		if (dif > 10)
			isOn = false;
		dif++;
	}

	imshow("LED Image", matDrawContoursLED); //show the thresholded image



	return isOn;
}

//put the thread to sleep
void threadd::pause(){
	while (*sleepThread){
		Sleep(1);

	}
}

//Vectors for the radious
vector<vector<Point>> contours_poly(100);
vector<Point2f>center2(100);
vector<float>radius(100);
int threadd::process(VideoCapture& capture){
	cout << "3" << endl;
	CoordinateData coordData;
	bool wasLED = false;
	coordData.magnitude0.push_back(0); coordData.magnitude1.push_back(0);
	coordData.magnitude2.push_back(0);
	Mat matOriginal;
	Mat matHsv;
	Mat matColourRange;

	Mat matContours;

	int frame = 0;
	int numberLED = 0;
	vector<vector<cv::Point> > vecContours;
	bool found;
	while (true) {
		vector <float> tempCentreCoord;
		pause();
		//   vector <float> tempCentreCoord2;
		cout << "3" << endl;
		// Take the next frame and store it in the Matrix matOriginal
		capture >> matOriginal;
		if (matOriginal.empty()){ break; }

		//if no led found continue if there was a led previous frame keep track of the frame
		if (!isLED(matOriginal)){
			cout << "before is led" << endl;
			if (wasLED == true){
				LEDonoff.push_back(frame);
				wasLED = false;
			}
			continue;
		}
		else{
			//there is a frame and if last frame there wasnt track it  put there is a led now
			if (wasLED == false){
				LEDonoff.push_back(frame);
				wasLED = true;
				found = false;
				//   cout<<"frame"<<  frame<<endl;
				numberLED++;

				information->append("     Found LED: " + QString::number(numberLED));
				/*int frameCapt = capture.get(CV_CAP_PROP_POS_FRAMES);
				information->append("Frame : " + QString::number(frameCapt));*/
				cout << "hii" << endl;
				Sleep(10);
				csvOutput3 << "     Found LED: " << (numberLED) << endl;
				cout << "hii" << endl;
				Sleep(10);


			}
			//increase value this tells which frames has led and where each trial is
			frame++;


		}
		// Convert the frame stored in matOriginal convert to HSV and store in matHsv
		cvtColor(matOriginal, matHsv, COLOR_BGR2HSV);

		// Blur the frame stored in matHsv using Gaussian Kernal
		GaussianBlur(matHsv, matHsv, Size(5, 5), 1.5);

		// Convert the image to binary and show anything that is in the HSV range provided as white, store in matYellowRange
		inRange(matHsv, lowNew, highNew, matContours);
		inRange(matHsv, lowNew, highNew, matColourRange);

		// Perform findContours using the binary image in matContours, store the contours in vecContours,
		// retrieve external contours only disregard child contours, dont disregard and make approximations with the contours.
		findContours(matContours, vecContours, RETR_EXTERNAL,
			CHAIN_APPROX_NONE);
		vector<Moments> vecMoments(vecContours.size());
		for (int i = 0; i < vecContours.size(); i++)
		{
			vecMoments[i] = moments(vecContours[i], false);
		}

		// Get the centre point of the contours, store in a vector
		vector<Point2f> vecCentreContours(vecContours.size());
		for (int i = 0; i < vecContours.size(); i++)
		{
			// Works out centre point of contour by taking left/right top/bottom
			vecCentreContours[i] = Point2f(vecMoments[i].m10 /
				vecMoments[i].m00, vecMoments[i].m01 / vecMoments[i].m00);
		}
		//area of a circle= pi*r^2 diameter =(area/pi^1/2)*2 use vecmoments[1].m00(middle dot) as area
		// array to index the i so we can know which vecContours are being used
		vector<int> index;
		for (int i = 0; i < vecContours.size(); i++)
		{
			if (contourArea(vecContours[i]) > COLOR_SPOT_AREA_MIN) {

				index.push_back(i);
				tempCentreCoord.push_back(vecCentreContours[i].x);
				tempCentreCoord.push_back(vecCentreContours[i].y);
			}
		}

		if (tempCentreCoord.size() == 6) {
			//old way to get areas
			diameterLeftOld.push_back(contourArea(vecContours[index[0]]));
			diameterCenterOld.push_back(contourArea(vecContours[index[1]]));
			diameterRightOld.push_back(contourArea(vecContours[index[2]]));

			//new way

			/*
			Loizos Comments:
			approxPolyDP is a method for finding the contour. Then using the contours, it calculates the diameter and with that the area of the circle.
			*/

			//For the Left Ear
			approxPolyDP(Mat(vecContours[index[0]]), contours_poly[index[0]], 3, true);
			minEnclosingCircle((Mat)contours_poly[index[0]], center2[index[0]], radius[index[0]]);
			diameterLeftNew.push_back(radius[index[0]] * 2);

			//For the Center(head)
			approxPolyDP(Mat(vecContours[index[1]]), contours_poly[index[1]], 3, true);
			minEnclosingCircle((Mat)contours_poly[index[1]], center2[index[1]], radius[index[1]]);
			diameterCenterNew.push_back(radius[index[1]] * 2);

			//For the Right Ear
			approxPolyDP(Mat(vecContours[index[2]]), contours_poly[index[2]], 3, true);
			minEnclosingCircle((Mat)contours_poly[index[2]], center2[index[2]], radius[index[2]]);
			diameterRightNew.push_back(radius[index[2]] * 2);

			//get axis x vs y of middle dot
			double x = abs(boundingRect(vecContours[index[1]]).tl().x - boundingRect(vecContours[index[1]]).br().x);
			double y = abs(boundingRect(vecContours[index[1]]).tl().y - boundingRect(vecContours[index[1]]).br().y);
			if (x > y){
				tiltRate.push_back(y / x);

			}
			else{
				tiltRate.push_back(x / y);
			}
			/*
						if(areasLeft[numberLED-1].size()<100){

						areasLeft[numberLED-1].push_back(contourArea(vecContours[index[0]]));
						approxPolyDP( Mat(vecContours[index[0]]), contours_poly[index[0]], 3, true );
						minEnclosingCircle( (Mat)contours_poly[index[0]], center2[index[0]], radius[index[0]] );
						areas3Left[numberLED-1].push_back(radius[index[0]]*2);
						/*   double x=abs(boundingRect(vecContours[index[0]]).tl().x-boundingRect(vecContours[index[0]]).br().x);
						double y=abs(boundingRect(vecContours[index[0]]).tl().y-boundingRect(vecContours[index[0]]).br().y);
						if(x>y){
						areas2Left[numberLED-1].push_back(x);
						}
						else{areas2Left[numberLED-1].push_back(y);}

						}*/
			/*  if(areasCenter[numberLED-1].size()<100){

				  areasCenter[numberLED-1].push_back(contourArea(vecContours[index[1]]));
				  approxPolyDP( Mat(vecContours[index[1]]), contours_poly[index[1]], 3, true );
				  minEnclosingCircle( (Mat)contours_poly[index[1]], center2[index[1]], radius[index[1]] );
				  areas3Center[numberLED-1].push_back(radius[index[1]]*2);
				  /*   double x=abs(boundingRect(vecContours[index[0]]).tl().x-boundingRect(vecContours[index[0]]).br().x);
				  double y=abs(boundingRect(vecContours[index[0]]).tl().y-boundingRect(vecContours[index[0]]).br().y);
				  if(x>y){
				  areas2Left[numberLED-1].push_back(x);
				  }
				  else{areas2Left[numberLED-1].push_back(y);}

				  }
				  if(areasRight[numberLED-1].size()<100){

				  areasRight[numberLED-1].push_back(contourArea(vecContours[index[2]]));
				  approxPolyDP( Mat(vecContours[index[2]]), contours_poly[index[2]], 3, true );
				  minEnclosingCircle( (Mat)contours_poly[index[2]], center2[index[2]], radius[index[2]] );
				  areas3Right[numberLED-1].push_back(radius[index[2]]*2);
				  /*    double x=abs(boundingRect(vecContours[index[2]]).tl().x-boundingRect(vecContours[index[2]]).br().x);
				  double y=abs(boundingRect(vecContours[index[2]]).tl().y-boundingRect(vecContours[index[2]]).br().y);
				  if(x>y){
				  areas2Right[numberLED-1].push_back(x);
				  }
				  else{areas2Right[numberLED-1].push_back(y);}

				  }*/
			found = true;
			coordData.x0.push_back(tempCentreCoord[0]);
			coordData.y0.push_back(tempCentreCoord[1]);
			coordData.x1.push_back(tempCentreCoord[2]);
			coordData.y1.push_back(tempCentreCoord[3]);
			coordData.x2.push_back(tempCentreCoord[4]);
			coordData.y2.push_back(tempCentreCoord[5]);
		}
		else { /////
			if (found == false)
			{//if dots havent been found add 0s
				//  string l="couldn't find dots in file"+ filepath;
				//  stats->setText(l.c_str());
				coordData.x0.push_back(0);
				coordData.y0.push_back(0);
				coordData.x1.push_back(0);
				coordData.y1.push_back(0);
				coordData.x2.push_back(0);
				coordData.y2.push_back(0);
				diameterLeftOld.push_back(0);
				diameterCenterOld.push_back(0);
				diameterRightOld.push_back(0);
				diameterLeftNew.push_back(0);
				diameterCenterNew.push_back(0);
				diameterRightNew.push_back(0);
				tiltRate.push_back(0);

				continue;

			}
			//is they have been found before add last value as it should not variate that much
			tiltRate.push_back(tiltRate.back());
			coordData.x0.push_back(coordData.x0.back());
			coordData.y0.push_back(coordData.y0.back());
			coordData.x1.push_back(coordData.x1.back());
			coordData.y1.push_back(coordData.y1.back());
			coordData.x2.push_back(coordData.x2.back());
			coordData.y2.push_back(coordData.y2.back());
			diameterLeftOld.push_back(diameterLeftOld.back());
			diameterCenterOld.push_back(diameterCenterOld.back());
			diameterRightOld.push_back(diameterRightOld.back());
			diameterLeftNew.push_back(diameterLeftNew.back());
			diameterCenterNew.push_back(diameterCenterNew.back());
			diameterRightNew.push_back(diameterRightNew.back());

		}


		cout << "4" << endl;

	}
	//if there are values continue to analyse and write
	if (LEDonoff.size() > 0){

		writeToFile(coordData);

		if (coordData.x0.size() > 0){
			findHigherValues(coordData);

		}
	}
	else{

		information->append("Can not find LED");
		csvOutput3 << ("Can not find LED") << endl;
		Sleep(10);
		csvOutput3.close();
	}
	LEDonoff.clear();
	return 1;
}
int threadd::processWithWindows(VideoCapture& capture){
	Mat matOriginal;
	Mat matHsv;
	Mat matColourRange;
	Mat matEdges;
	Mat matContours;
	

	bool wasLED = false;
	int frameCount = 0;
	bool found;
	int frame = 0;
	int numberLED = 0;
	// 64 bit value passed to generate random sequence
	RNG rng(12345);
	// Vector of contours, each element is a vector of points
	vector<vector<Point> > vecContours = vector<vector<Point> >();

	CoordinateData coordData;
	coordData.magnitude0.push_back(0); coordData.magnitude1.push_back(0);
	coordData.magnitude2.push_back(0);
	//windows  to show
	string windowName[] = { "Original", "HSV", "ColourRange", "Edges", "Contours" };
	namedWindow(windowName[0], WINDOW_NORMAL); moveWindow(windowName[0], 600, 100);
	namedWindow(windowName[1], WINDOW_NORMAL); moveWindow(windowName[1], 1000, 100);
	namedWindow(windowName[2], WINDOW_NORMAL); moveWindow(windowName[2], 200, 500);
	namedWindow(windowName[3], WINDOW_NORMAL); moveWindow(windowName[3], 600, 500);
	namedWindow(windowName[4], WINDOW_NORMAL); moveWindow(windowName[4], 1000, 500);
	namedWindow("Rects", WINDOW_NORMAL); moveWindow("Rects", 200, 100);

	// Every loop is a new frame
	while (true) {
		vector<int> index;
		frameCount++;
		vector <float> tempCentreCoord;
		// Generate a random Color
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255),
			rng.uniform(0, 255));
		// Take the next frame and store it in the Matrix matOriginal
		capture >> matOriginal;
		if (matOriginal.empty()){ break; }
		if (!isLEDWithWindows(matOriginal)){
			if (wasLED == true){
				LEDonoff.push_back(frame);
				wasLED = false;
			}
			continue;
		}
		else{

			if (wasLED == false){
				LEDonoff.push_back(frame);
				wasLED = true;
				found = false;
				cout << "frame" << frame << endl;
				numberLED++;

				int frameCapt = capture.get(CV_CAP_PROP_POS_FRAMES);
				information->append("Frame : " + QString::number(frameCapt));

				information->append("Found LED: " + QString::number(numberLED));
				csvOutput3 << "Found LED: " << (numberLED) << endl;
				
				


			}
			frame++;
		}
		// Convert the frame stored in matOriginal convert to HSV and store in matHsv
		cvtColor(matOriginal, matHsv, COLOR_BGR2HSV);
		//cvtColor(matOriginal, matHsv, COLOR_RGB2HSV);


		// Blur the frame stored in matHsv using Gaussian Kernal
		GaussianBlur(matHsv, matHsv, Size(5, 5), 1.5);
		// Convert the image to binary and show anything that is in the HSV range provided as white, store in matYellowRange
		inRange(matHsv, lowNew, highNew, matColourRange);
		inRange(matHsv, lowNew, highNew, matContours);



		// Perform Canny edge detection and output the results to matEdges
		Canny(matColourRange, matEdges, 0, 30, 3);
		// Perform findContours using the binary image in matContours, store the contours in vecContours,
		// retrieve external contours only disregard child contours, dont disregard and make approximations with the contours.
		findContours(matContours, vecContours, RETR_EXTERNAL,
			CHAIN_APPROX_NONE);

		// Fill matDrawContours with zeros
		Mat matDrawContours = Mat::zeros(matContours.size(), CV_8UC3);
		Mat boundingCircles = Mat::zeros(matContours.size(), CV_8UC3);
		// Get the moments of each contour (number of white pixels), store in a vector
		vector<Moments> vecMoments(vecContours.size());
		for (int i = 0; i < vecContours.size(); i++)
		{
			vecMoments[i] = moments(vecContours[i], false);
		}
		// Get the centre point of the contours, store in a vector
		vector<Point2f> vecCentreContours(vecContours.size());
		for (int i = 0; i < vecContours.size(); i++)
		{
			// Works out centre point of contour by taking left/right top/bottom
			vecCentreContours[i] = Point2f(vecMoments[i].m10 /
				vecMoments[i].m00, vecMoments[i].m01 / vecMoments[i].m00);
		}

		cout << "Frame: " << frameCount << endl;
		cout << "vecContours: " << vecContours.size() << endl;
		for (int i = 0; i < vecContours.size(); i++)
		{
			if (contourArea(vecContours[i]) > COLOR_SPOT_AREA_MIN) {
				index.push_back(i);
				cout << "Are" << i << contourArea(vecContours[i]) << endl;
				tempCentreCoord.push_back(vecCentreContours[i].x);
				tempCentreCoord.push_back(vecCentreContours[i].y);
				drawContours(matDrawContours, vecContours, i,
					color, 2, 8);
				circle(matDrawContours, vecCentreContours[i], 3,
					color, -1, 8, 0);
			}
		}
		//if there is 6 datas
		cout << "tempCentreCoord" << tempCentreCoord.size() << endl;
		if (tempCentreCoord.size() == 6) {
			found = true;
			//get old and new methods for diameter
			diameterLeftOld.push_back(contourArea(vecContours[index[0]]));
			diameterCenterOld.push_back(contourArea(vecContours[index[1]]));
			diameterRightOld.push_back(contourArea(vecContours[index[2]]));
			approxPolyDP(Mat(vecContours[index[0]]), contours_poly[index[0]], 3, true);
			minEnclosingCircle((Mat)contours_poly[index[0]], center2[index[0]], radius[index[0]]);
			diameterLeftNew.push_back(radius[index[0]] * 2);
			approxPolyDP(Mat(vecContours[index[1]]), contours_poly[index[1]], 3, true);
			minEnclosingCircle((Mat)contours_poly[index[1]], center2[index[1]], radius[index[1]]);
			diameterCenterNew.push_back(radius[index[1]] * 2);
			approxPolyDP(Mat(vecContours[index[2]]), contours_poly[index[2]], 3, true);
			minEnclosingCircle((Mat)contours_poly[index[2]], center2[index[2]], radius[index[2]]);
			diameterRightNew.push_back(radius[index[2]] * 2);
			//get the x and y axis to get the tilt
			//draw rect
			rectangle(boundingCircles, boundingRect(vecContours[index[1]]).tl(), boundingRect(vecContours[index[1]]).br(), Scalar(255, 255, 0), 2, 8, 0);
			double x = abs(boundingRect(vecContours[index[1]]).tl().x - boundingRect(vecContours[index[1]]).br().x);
			double y = abs(boundingRect(vecContours[index[1]]).tl().y - boundingRect(vecContours[index[1]]).br().y);
			if (x > y){
				tiltRate.push_back(y / x);

			}
			else{
				tiltRate.push_back(x / y);
			}

			/*     if(areasLeft[numberLED-1].size()<100){

					   areasLeft[numberLED-1].push_back(contourArea(vecContours[index[0]]));
					   approxPolyDP( Mat(vecContours[index[0]]), contours_poly[index[0]], 3, true );
					   minEnclosingCircle( (Mat)contours_poly[index[0]], center2[index[0]], radius[index[0]] );
					   areas3Left[numberLED-1].push_back(radius[index[0]]*2);
					   /*   double x=abs(boundingRect(vecContours[index[0]]).tl().x-boundingRect(vecContours[index[0]]).br().x);
					   double y=abs(boundingRect(vecContours[index[0]]).tl().y-boundingRect(vecContours[index[0]]).br().y);
					   if(x>y){
					   areas2Left[numberLED-1].push_back(x);
					   }
					   else{areas2Left[numberLED-1].push_back(y);}

					   }*/
			/* if(areasCenter[numberLED-1].size()<100){

				 areasCenter[numberLED-1].push_back(contourArea(vecContours[index[1]]));
				 approxPolyDP( Mat(vecContours[index[1]]), contours_poly[index[1]], 3, true );
				 minEnclosingCircle( (Mat)contours_poly[index[1]], center2[index[1]], radius[index[1]] );
				 areas3Center[numberLED-1].push_back(radius[index[1]]*2);
				 /*   double x=abs(boundingRect(vecContours[index[0]]).tl().x-boundingRect(vecContours[index[0]]).br().x);
				 double y=abs(boundingRect(vecContours[index[0]]).tl().y-boundingRect(vecContours[index[0]]).br().y);
				 if(x>y){
				 areas2Left[numberLED-1].push_back(x);
				 }
				 else{areas2Left[numberLED-1].push_back(y);}
				 }*/


			/* if(areasRight[numberLED-1].size()<100){

				 areasRight[numberLED-1].push_back(contourArea(vecContours[index[2]]));
				 approxPolyDP( Mat(vecContours[index[2]]), contours_poly[index[2]], 3, true );
				 minEnclosingCircle( (Mat)contours_poly[index[2]], center2[index[2]], radius[index[2]] );
				 areas3Right[numberLED-1].push_back(radius[index[2]]*2);
				 /*    double x=abs(boundingRect(vecContours[index[2]]).tl().x-boundingRect(vecContours[index[2]]).br().x);
				 double y=abs(boundingRect(vecContours[index[2]]).tl().y-boundingRect(vecContours[index[2]]).br().y);
				 if(x>y){
				 areas2Right[numberLED-1].push_back(x);
				 }
				 else{areas2Right[numberLED-1].push_back(y);}

				 }*/
			coordData.x0.push_back(tempCentreCoord[0]);
			coordData.y0.push_back(tempCentreCoord[1]);
			coordData.x1.push_back(tempCentreCoord[2]);
			coordData.y1.push_back(tempCentreCoord[3]);
			coordData.x2.push_back(tempCentreCoord[4]);
			coordData.y2.push_back(tempCentreCoord[5]);
			printf(" Contour 1 - Centre X:%.2f - Centre Y:%.2f \n",
				tempCentreCoord[0], tempCentreCoord[1]);
			printf(" Contour 2 - Centre X:%.2f - Centre Y:%.2f \n",
				tempCentreCoord[2], tempCentreCoord[3]);
			printf(" Contour 3 - Centre X:%.2f - Centre Y:%.2f \n",
				tempCentreCoord[4], tempCentreCoord[5]);
		}
		//if there is a circle missing
		else { /////
			if (found == false)
			{
				string l = "couldn't find dots in file" + filepath;

				coordData.x0.push_back(0);
				coordData.y0.push_back(0);
				coordData.x1.push_back(0);
				coordData.y1.push_back(0);
				coordData.x2.push_back(0);
				coordData.y2.push_back(0);

				continue;
			}
			coordData.x0.push_back(coordData.x0.back());
			coordData.y0.push_back(coordData.y0.back());
			coordData.x1.push_back(coordData.x1.back());
			coordData.y1.push_back(coordData.y1.back());
			coordData.x2.push_back(coordData.x2.back());
			coordData.y2.push_back(coordData.y2.back());

			diameterLeftOld.push_back(0);
			diameterCenterOld.push_back(0);
			diameterRightOld.push_back(0);
			diameterLeftNew.push_back(0);
			diameterCenterNew.push_back(0);
			diameterRightNew.push_back(0);
			continue;
			printf("No Data recorded this frame");
			coordData.x0.push_back(coordData.x0.back());
			coordData.y0.push_back(coordData.y0.back());
			coordData.x1.push_back(coordData.x1.back());
			coordData.y1.push_back(coordData.y1.back());
			coordData.x2.push_back(coordData.x2.back());
			coordData.y2.push_back(coordData.y2.back());
		}

		//draw enclosing circles
		drawContours(boundingCircles, vecContours, index[0],
			Scalar(255, 255, 255), 1, 8);
		drawContours(boundingCircles, vecContours, index[1],
			Scalar(255, 255, 255), 1, 8);
		drawContours(boundingCircles, vecContours, index[2],
			Scalar(255, 255, 255), 1, 8);
		circle(boundingCircles, vecCentreContours[index[0]], radius[index[0]] + 1, Scalar(0, 255, 0), 1, 8, 0);
		circle(boundingCircles, vecCentreContours[index[1]], radius[index[1]] + 1, Scalar(0, 255, 0), 1, 8, 0);
		circle(boundingCircles, vecCentreContours[index[2]], radius[index[2]] + 1, Scalar(0, 255, 0), 1, 8, 0);

		// Show all windows and update the contents for each new frame
		imshow(windowName[0], matOriginal);
		imshow(windowName[1], matHsv);
		imshow(windowName[2], matColourRange);
		imshow(windowName[3], matEdges);
		imshow(windowName[4], matDrawContours);
		imshow("Rects", boundingCircles);

		// Wait for keyboard input before moving to next frame if scape go to next file

		char k = waitKey(0);
		if (k == 27){
			destroyWindow(windowName[0]);
			destroyWindow(windowName[1]);
			destroyWindow(windowName[2]);
			destroyWindow(windowName[3]);
			destroyWindow(windowName[4]);
			destroyWindow("Rects");
			LEDonoff.clear();
			diameterLeftOld.clear();
			diameterCenterOld.clear();
			diameterRightOld.clear();
			diameterLeftNew.clear();
			diameterCenterNew.clear();
			diameterRightNew.clear();
			return 0;

		}
	}
	destroyWindow(windowName[0]);
	destroyWindow(windowName[1]);
	destroyWindow(windowName[2]);
	destroyWindow(windowName[3]);
	destroyWindow(windowName[4]);
	destroyWindow("Rects");
	if (LEDonoff.size() > 2){
		cout << "previous write to file" << endl;
		writeToFile(coordData);
		cout << "after write to file" << endl;
		if (coordData.x0.size() > 0){
			findHigherValues(coordData);
			cout << "after find values" << endl;
		}
	}
	else{
		information->append("Can not find LED");
		csvOutput3 << ("Can not find LED") << endl;
		Sleep(10);
		csvOutput3.close();
	}
	LEDonoff.clear();
	diameterLeftOld.clear();
	diameterCenterOld.clear();
	diameterRightOld.clear();
	diameterLeftNew.clear();
	diameterCenterNew.clear();
	diameterRightNew.clear();
	return 1;
}

void threadd::writeToFile(CoordinateData &coordData){
	information->append("           Processing...");
	csvOutput3 << ("           Processing...") << endl;
	Sleep(10);
	if (coordData.x0.size() > 0){
		float startX0 = coordData.x0[0];
		float startX1 = coordData.x1[0];
		float startX2 = coordData.x2[0];
		float startY0 = coordData.y0[0];
		float startY1 = coordData.y1[0];
		float startY2 = coordData.y2[0];
		pause();
		for (int i = 1; i < coordData.x0.size(); i++)
		{
			//depending on reference frame=according to previous frame first frame substracting to the first and center acording to center dot
			if (reference == "Frame"){
				if (i == 0){
					coordData.magnitude0.push_back(sqrt(((coordData.x1[i] - coordData.x0[i])
						* (coordData.x1[i] - coordData.x0[i])) +
						((coordData.y1[i] - coordData.y0[i]) * (coordData.y1[i] -
						coordData.y0[i]))));
					coordData.magnitude1.push_back(sqrt(((startX1 - coordData.x1[i])
						* (startX1 - coordData.x1[i])) +
						((startY1 - coordData.y1[i]) * (startY1 -
						coordData.y1[i]))));
					coordData.magnitude2.push_back(sqrt(((coordData.x1[i] - coordData.x2[i])
						* (coordData.x1[i] - coordData.x2[i])) +
						((coordData.y1[i] - coordData.y2[i]) * (coordData.y1[i] -
						coordData.y2[i]))));
				}
				else{
					coordData.magnitude0.push_back(sqrt(((coordData.x0[i - 1] - coordData.x0[i])
						* (coordData.x0[i - 1] - coordData.x0[i])) +
						((coordData.y0[i - 1] - coordData.y0[i]) * (coordData.y0[i - 1] -
						coordData.y0[i]))));
					coordData.magnitude1.push_back(sqrt(((coordData.x1[i - 1] - coordData.x1[i])
						* (coordData.x1[i - 1] - coordData.x1[i])) +
						((coordData.y1[i - 1] - coordData.y1[i]) * (coordData.y1[i - 1] -
						coordData.y1[i]))));
					coordData.magnitude2.push_back(sqrt(((coordData.x2[i - 1] - coordData.x2[i])
						* (coordData.x2[i - 1] - coordData.x2[i])) +
						((coordData.y2[i - 1] - coordData.y2[i]) * (coordData.y2[i - 1] -
						coordData.y2[i]))));
				}
			}
			if (reference == "First Frame"){

				coordData.magnitude0.push_back(sqrt(((startX0 - coordData.x0[i])
					* (startX0 - coordData.x0[i])) +
					((startY0 - coordData.y0[i]) * (startY0 -
					coordData.y0[i]))));
				coordData.magnitude1.push_back(sqrt(((startX1 - coordData.x1[i])
					* (startX1 - coordData.x1[i])) +
					((startY1 - coordData.y1[i]) * (startY1 -
					coordData.y1[i]))));
				coordData.magnitude2.push_back(sqrt(((startX2 - coordData.x2[i])
					* (startX2 - coordData.x2[i])) +
					((startY2 - coordData.y2[i]) * (startY2 -
					coordData.y2[i]))));

			}
			if (reference == "Center"){


				coordData.magnitude0.push_back((sqrt(((coordData.x1[i] - coordData.x0[i])
					* (coordData.x1[i] - coordData.x0[i])) +
					((coordData.y1[i] - coordData.y0[i]) * (coordData.y1[i] -
					coordData.y0[i])))));
				coordData.magnitude1.push_back((sqrt(((startX1 - coordData.x1[i])
					* (startX1 - coordData.x1[i])) +
					((startY1 - coordData.y1[i]) * (startY1 -
					coordData.y1[i])))));

				coordData.magnitude2.push_back((sqrt(((coordData.x1[i] - coordData.x2[i])
					* (coordData.x1[i] - coordData.x2[i])) +
					((coordData.y1[i] - coordData.y2[i]) * (coordData.y1[i] -
					coordData.y2[i])))));
				//  coordData.magnitude1.push_back(sqrt(coordData.magnitude0[i]*coordData.magnitude0[i]+coordData.magnitude2[i]*coordData.magnitude2[i]));
			}
		}
		float dot0, dot2;

		pause();
		//get values according to first dot FOUND in that trial
		for (int c = 0; c < LEDonoff.size(); c = c + 2){
			dot0 = 0;
			dot2 = 0;
			for (int i = LEDonoff[c]; i < LEDonoff[c + 1]; i++){
				if (coordData.magnitude0[i] == 0 || coordData.magnitude2[i] == 0){
					coordData.normalized0.push_back(0);
					coordData.normalized2.push_back(0);
				}
				else{
					if (dot0 == 0 && dot2 == 0){
						dot0 = coordData.magnitude0[i];
						dot2 = coordData.magnitude2[i];
						coordData.normalized0.push_back(0);
						coordData.normalized2.push_back(0);
					}
					else{
						coordData.normalized0.push_back(abs(dot0 - coordData.magnitude0[i]));
						coordData.normalized2.push_back(abs(dot2 - coordData.magnitude2[i]));
					}
				}
			}
		}
	}
	//if size is 0 means no dots found
	else{
		information->append("           Can not find Dots...");
		csvOutput3 << ("           Can not find Dots...") << endl;
		Sleep(10);
		csvOutput3.close();
	}
}

void threadd::findHigherValues(CoordinateData &coordData){

	//left and right gap and no gap containers
	vector<double> GraphValuesLeftNoGap[20];
	vector<double> GraphValuesRightNoGap[20];
	vector<double> GraphValuesLeftGap[20];
	vector<double> GraphValuesRightGap[20];
	//vectors for the diameters old new
	vector<double> diameterLeftOldBig[20];
	vector<double> diameterCenterOldBigLeft[20];
	vector<double> diameterCenterOldBigRight[20];
	vector<double> diameterRightOldBig[20];
	vector<double> diameterLeftNewBig[20];
	vector<double> diameterCenterNewBigLeft[20];
	vector<double> diameterCenterNewBigRight[20];
	vector<double> diameterRightNewBig[20];

	//peak values at each trial
	vector<float> GapValueLeft, NoGapValueLeft;
	vector <float> GapValueRight, NoGapValueRight;
	//floats for avgs
	float GapAvgLeft = 0;
	float NoGapAvgLeft = 0;
	float GapAvgRight = 0;
	float NoGapAvgRight = 0;
	//number of values left and right
	vector <float> valuesLeft;
	vector <float> valuesRight;

	list <float> listOfValuesLeft;
	list <float> listOfValuesRight;
	//to know which color according to if it is gap or no gap
	vector<int>colorGap;
	vector<int>colorNoGap;


	for (int c = 0; c < LEDonoff.size(); c = c + 2){
		pause();
		//find highest value
		float highestValue = 0;
		int frame = 0;

		for (int i = LEDonoff[c]; i < LEDonoff[c + 1]; i++){
			if (coordData.normalized0[i] > highestValue){
				highestValue = coordData.normalized0[i];
				frame = i;
			}
		}
		valuesLeft.push_back(highestValue);
		//if is 0 output
		if (highestValue == 0){
			information->append("              Left ear, couldn't find dots. Trial" + QString::number((c / 2) + 1));
			csvOutput3 << "              Left ear, couldn't find dots. Trial" << ((c / 2) + 1) << endl;

			Sleep(10);
			//once peak value is found get the +-15 if they are 0 push 0s and 0.1 in peak so the graph shows from 0 and not -2
			for (int start = frame - (windowsOffset / 2); start < frame + (windowsOffset / 2) + 1; start++){
				if (start == frame){
					listOfValuesLeft.push_back(0.1);
				}
				else{
					listOfValuesLeft.push_back(0);
				}
			}
			//get +-50 for diameters for left old
			for (int start = frame - (50); start < frame + (50) + 1; start++){
				if (start == frame){
					diameterLeftOldBig[c / 2].push_back(0);
					diameterCenterOldBigLeft[c / 2].push_back(0);
					diameterLeftNewBig[c / 2].push_back(0);
					diameterCenterNewBigLeft[c / 2].push_back(0);

				}
				else{
					diameterLeftOldBig[c / 2].push_back(0);
					diameterCenterOldBigLeft[c / 2].push_back(0);
					diameterLeftNewBig[c / 2].push_back(0);
					diameterCenterNewBigLeft[c / 2].push_back(0);
				}

			}
			tiltVector.push_back(false);

		}
		else{
			tiltVector.push_back(false);
			//if there are values retrieve them
			for (int start = frame - (windowsOffset / 2); start < frame + (windowsOffset / 2) + 1; start++){


				listOfValuesLeft.push_back(coordData.normalized0[start]);
			}
			for (int start = frame - (50); start < frame + (50) + 1; start++){
				diameterLeftOldBig[c / 2].push_back(sqrt(diameterLeftOld[start] / 3.14159) * 2);
				diameterCenterOldBigLeft[c / 2].push_back(sqrt(diameterCenterOld[start] / 3.14159) * 2);
				diameterLeftNewBig[c / 2].push_back(diameterLeftNew[start]);
				diameterCenterNewBigLeft[c / 2].push_back(diameterCenterNew[start]);
				//if tilt value is < tilt and dif of 0
				if (tiltRate[start] < tilt / 100 && tiltRate[start] != 0){
					tiltVector[c / 2] = true;
				}
			}

		}


		highestValue = 0;
		frame = 0;

		for (int i = LEDonoff[c]; i < LEDonoff[c + 1]; i++){

			if (coordData.normalized2[i] > highestValue){
				highestValue = coordData.normalized2[i];
				frame = i;
			}
		}
		valuesRight.push_back(highestValue);
		//same as before but with right ear
		if (highestValue == 0){
			information->append("              Right ear, couldn't find dots. Trial" + QString::number((c / 2) + 1));
			csvOutput3 << "              Right ear, couldn't find dots. Trial" << ((c / 2) + 1) << endl;

			Sleep(10);
			for (int start = frame - (windowsOffset / 2); start < frame + (windowsOffset / 2) + 1; start++){
				if (start == frame){
					listOfValuesRight.push_back(0.1);
				}
				else{
					listOfValuesRight.push_back(0);
				}
			}
			for (int start = frame - (50); start < frame + (50) + 1; start++){
				if (start == frame){
					diameterRightOldBig[c / 2].push_back(0);
					diameterCenterOldBigRight[c / 2].push_back(0);
					diameterRightNewBig[c / 2].push_back(0);
					diameterCenterNewBigRight[c / 2].push_back(0);

				}
				else{
					diameterRightOldBig[c / 2].push_back(0);
					diameterCenterOldBigRight[c / 2].push_back(0);
					diameterRightNewBig[c / 2].push_back(0);
					diameterCenterNewBigRight[c / 2].push_back(0);
				}
			}
		}
		else{
			for (int start = frame - (windowsOffset / 2); start < frame + (windowsOffset / 2) + 1; start++){
				listOfValuesRight.push_back(coordData.normalized2[start]);

			}
			for (int start = frame - (50); start < frame + (50) + 1; start++){
				diameterRightOldBig[c / 2].push_back(sqrt(diameterRightOld[start] / 3.14159) * 2);
				diameterCenterOldBigRight[c / 2].push_back(sqrt(diameterCenterOld[start] / 3.14159) * 2);
				diameterRightNewBig[c / 2].push_back(diameterRightNew[start]);
				diameterCenterNewBigRight[c / 2].push_back(diameterCenterNew[start]);
			}
		}
	}
	//release the data
	diameterRightOld.clear();
	diameterRightNew.clear();
	diameterCenterOld.clear();
	diameterCenterNew.clear();
	diameterLeftOld.clear();
	diameterLeftNew.clear();

	/////////put it here


	vector<int>num0sLeftOld;
	vector<int>num0sRightOld;
	vector<int>num0sCenterLeftOld;
	vector<int>num0sCenterRightOld;
	vector<int>num0sLeftNew;
	vector<int>num0sRightNew;
	vector<int>num0sCenterLeftNew;
	vector<int>num0sCenterRightNew;
	vector<double>avgsLeftOld;
	vector<double>avgsRightOld;
	vector<double>avgsCenterLeftOld;
	vector<double>avgsCenterRightOld;
	vector<double>avgsLeftNew;
	vector<double>avgsRightNew;
	vector<double>avgsCenterLeftNew;
	vector<double>avgsCenterRightNew;
	vector<double>stdevLeftOld;
	vector<double>stdevRightOld;
	vector<double>stdevCenterLeftOld;
	vector<double>stdevCenterRightOld;
	vector<double>stdevLeftNew;
	vector<double>stdevRightNew;
	vector<double>stdevCenterLeftNew;
	vector<double>stdevCenterRightNew;
	for (int i = 0; i < LEDonoff.size() / 2; i++){
		num0sLeftOld.push_back(0);
		num0sRightOld.push_back(0);
		num0sCenterLeftOld.push_back(0);
		num0sCenterRightOld.push_back(0);
		num0sLeftNew.push_back(0);
		num0sCenterLeftNew.push_back(0);
		num0sRightNew.push_back(0);
		num0sCenterRightNew.push_back(0);
		avgsLeftOld.push_back(0);
		avgsRightOld.push_back(0);
		avgsCenterLeftOld.push_back(0);
		avgsCenterRightOld.push_back(0);
		avgsLeftNew.push_back(0);
		avgsRightNew.push_back(0);
		avgsCenterLeftNew.push_back(0);
		avgsCenterRightNew.push_back(0);
		//get sum of 0s
		for (int j = 0; j < 101; j++){
			if (diameterLeftNewBig[i][j] == 0)
				num0sLeftNew[i]++;
			if (diameterCenterNewBigLeft[i][j] == 0)
				num0sCenterLeftNew[i]++;
			if (diameterRightNewBig[i][j] == 0)
				num0sRightNew[i]++;
			if (diameterCenterNewBigRight[i][j] == 0)
				num0sCenterRightNew[i]++;
			if (diameterLeftOldBig[i][j] == 0)
				num0sLeftOld[i]++;
			if (diameterCenterOldBigLeft[i][j] == 0)
				num0sCenterLeftOld[i]++;
			if (diameterRightOldBig[i][j] == 0)
				num0sRightOld[i]++;
			if (diameterCenterOldBigRight[i][j] == 0)
				num0sCenterRightOld[i]++;
			//sum values
			avgsLeftOld[i] += diameterLeftOldBig[i][j];
			avgsRightOld[i] += diameterRightOldBig[i][j];
			avgsCenterLeftOld[i] += diameterCenterOldBigLeft[i][j];
			avgsCenterRightOld[i] += diameterCenterOldBigRight[i][j];

			avgsLeftNew[i] += diameterLeftNewBig[i][j];
			avgsRightNew[i] += diameterRightNewBig[i][j];
			avgsCenterLeftNew[i] += diameterCenterNewBigLeft[i][j];
			avgsCenterRightNew[i] += diameterCenterNewBigRight[i][j];
		}

		//make the division
		if (num0sLeftOld[i] == 101){
			avgsLeftOld[i] = 0;
		}
		else{
			avgsLeftOld[i] /= 101 - num0sLeftOld[i];
		}

		if (num0sRightOld[i] == 101){
			avgsRightOld[i] = 0;
		}
		else{
			avgsRightOld[i] /= 101 - num0sRightOld[i];
		}

		if (num0sCenterLeftOld[i] == 101){
			avgsCenterLeftOld[i] = 0;
		}
		else{
			avgsCenterLeftOld[i] /= 101 - num0sCenterLeftOld[i];
		}

		if (num0sCenterRightOld[i] == 101){
			avgsCenterRightOld[i] = 0;
		}
		else{
			avgsCenterRightOld[i] /= 101 - num0sCenterRightOld[i];
		}

		if (num0sLeftNew[i] == 101){
			avgsLeftNew[i] = 0;
		}
		else{
			avgsLeftNew[i] /= 101 - num0sLeftNew[i];
		}

		if (num0sRightNew[i] == 101){
			avgsRightNew[i] = 0;
		}
		else{
			avgsRightNew[i] /= 101 - num0sRightNew[i];
		}

		if (num0sCenterLeftNew[i] == 101){
			avgsCenterLeftNew[i] = 0;
		}
		else{
			avgsCenterLeftNew[i] /= 101 - num0sCenterLeftNew[i];
		}

		if (num0sCenterRightNew[i] == 101){
			avgsCenterRightNew[i] = 0;
		}
		else{
			avgsCenterRightNew[i] /= 101 - num0sCenterRightNew[i];
		}
	}







	//sort them in their corresponding area gap or no gap
	//Left gaps and no gaps
	pause();
	for (int i = 0; i < valuesLeft.size(); i++){
		if (gaps[i] == 0){
			NoGapValueLeft.push_back(valuesLeft[i]);
			colorNoGap.push_back(i);
		}
		if (gaps[i] == 1){
			GapValueLeft.push_back(valuesLeft[i]);
			colorGap.push_back(i);
		}
	}
	//Right gaps and no gaps
	for (int i = 0; i < valuesRight.size(); i++){
		if (gaps[i] == 0){
			NoGapValueRight.push_back(valuesRight[i]);
		}
		if (gaps[i] == 1){
			GapValueRight.push_back(valuesRight[i]);
		}
	}

	//sum of values

	for (int i = 0; i < NoGapValueLeft.size(); i++){
		NoGapAvgLeft += NoGapValueLeft[i];

	}

	for (int i = 0; i < NoGapValueRight.size(); i++){
		NoGapAvgRight += NoGapValueRight[i];
	}

	for (int i = 0; i < GapValueLeft.size(); i++){
		GapAvgLeft += GapValueLeft[i];
	}

	for (int i = 0; i < GapValueRight.size(); i++){
		GapAvgRight += GapValueRight[i];
	}


	//put the +-15 in their corresponding vectors and look for the biggest value of the peaks
	float highestValueOfAll = 0;
	int c = 0;
	int d = 0;
	int l = 0;
	vector<double> biggestGraphValue;



	double convertingRatio = 0;
	for (int i = 0; i < valuesLeft.size(); i++){
		if (avgsCenterRightNew[l] == 0){
			convertingRatio = 0;
		}
		else{
			convertingRatio = dots / avgsCenterRightNew[l];
		}
		if (gaps[i] == 0){
			for (int j = 0; j < windowsOffset + 1; j++){
				GraphValuesLeftNoGap[c].push_back(listOfValuesLeft.front()*convertingRatio);
				if (valuesLeft[i] * convertingRatio >= highestValueOfAll){
					if (j == 0)
						biggestGraphValue.clear();
					highestValueOfAll = valuesLeft[i] * convertingRatio;
					biggestGraphValue.push_back(listOfValuesLeft.front()*convertingRatio);

				}

				listOfValuesLeft.pop_front();


			}

			c++;
		}

		if (gaps[i] == 1){
			for (int j = 0; j < windowsOffset + 1; j++){
				GraphValuesLeftGap[d].push_back(listOfValuesLeft.front()*convertingRatio);

				if (valuesLeft[i] * convertingRatio >= highestValueOfAll){

					if (j == 0)
						biggestGraphValue.clear();
					highestValueOfAll = valuesLeft[i] * convertingRatio;

					biggestGraphValue.push_back(listOfValuesLeft.front()*convertingRatio);


				}
				listOfValuesLeft.pop_front();

			}
			d++;
		}

		l++;
	}
	pause();


	//same as before but with right side
	int a = 0;
	int b = 0;
	l = 0;

	for (int i = 0; i < valuesRight.size(); i++){
		if (avgsCenterRightNew[l] == 0){
			convertingRatio = 0;
		}
		else{
			convertingRatio = dots / avgsCenterRightNew[l];
		}

		if (gaps[i] == 0){
			for (int j = 0; j < windowsOffset + 1; j++){
				GraphValuesRightNoGap[a].push_back(listOfValuesRight.front()* convertingRatio);
				if (valuesRight[i] * convertingRatio >= highestValueOfAll){
					if (j == 0)
						biggestGraphValue.clear();
					highestValueOfAll = valuesRight[i] * convertingRatio;
					biggestGraphValue.push_back(listOfValuesRight.front()* convertingRatio);

				}
				listOfValuesRight.pop_front();

			}
			a++;
		}

		if (gaps[i] == 1){
			for (int j = 0; j < windowsOffset + 1; j++){
				GraphValuesRightGap[b].push_back(listOfValuesRight.front()* convertingRatio);
				if (valuesRight[i] * convertingRatio >= highestValueOfAll){

					if (j == 0)
						biggestGraphValue.clear();
					highestValueOfAll = valuesRight[i] * convertingRatio;
					biggestGraphValue.push_back(listOfValuesRight.front()* convertingRatio);


				}
				listOfValuesRight.pop_front();

			}
			b++;
		}
		l++;
	}

	//get avgs
	pause();
	int nullValuesNoGapLeft = 0;
	int nullValuesGapLeft = 0;
	int nullValuesNoGapRight = 0;
	int nullValuesGapRight = 0;
	//get number of 0s to decrease to the avgs as they shouldnt be counted in trials
	for (int i = 0; i < GapValueLeft.size(); i++){
		if (GapValueLeft[i] == 0)
			nullValuesGapLeft++;
	}

	for (int i = 0; i < NoGapValueLeft.size(); i++){
		if (NoGapValueLeft[i] == 0)
			nullValuesNoGapLeft++;
	}
	for (int i = 0; i < GapValueRight.size(); i++){
		if (GapValueRight[i] == 0)
			nullValuesGapRight++;
	}
	for (int i = 0; i < NoGapValueRight.size(); i++){
		if (NoGapValueRight[i] == 0)
			nullValuesNoGapRight++;
	}
	NoGapAvgLeft = NoGapAvgLeft / (NoGapValueLeft.size() - nullValuesNoGapLeft);

	GapAvgLeft = GapAvgLeft / (GapValueLeft.size() - nullValuesGapLeft);

	NoGapAvgRight = NoGapAvgRight / (NoGapValueRight.size() - nullValuesNoGapRight);
	GapAvgRight = GapAvgRight / (GapValueRight.size() - nullValuesGapRight);


	//get values for x axis
	QVector<double> x(windowsOffset + 1);
	for (int i = 0; i < windowsOffset + 1; i++){
		x[i] = i;

	}

	// Vectors for graphs x,GraphValuesLeftGap,GraphValuesLeftNoGap, GraphValuesRightGap, GraphValuesRightNoGap
	//create qvectors
	QVector<double> GraphValuesLeftGapQVector[20];
	QVector<double> GraphValuesLeftNoGapQVector[20];
	QVector<double> GraphValuesRightGapQVector[20];
	QVector<double> GraphValuesRightNoGapQVector[20];

	QColor Color;
	//Set Graphs
	QVector<double> avgGraphValuesLeftGap(windowsOffset + 1);
	QVector<double> avgGraphValuesLeftNoGap(windowsOffset + 1);
	QVector<double> avgGraphValuesRightGap(windowsOffset + 1);
	QVector<double> avgGraphValuesRightNoGap(windowsOffset + 1);
	//this can be done in one for if lenghts are the same

	//get the avg graphs values
	for (int j = 0; j < windowsOffset + 1; j++){
		for (int i = 0; i < GapValueLeft.size(); i++){
			avgGraphValuesLeftGap[j] += GraphValuesLeftGap[i][j];
		}
		if (j == windowsOffset / 2){
			avgGraphValuesLeftGap[j] = (avgGraphValuesLeftGap[j] - (nullValuesGapLeft*0.1)) / (GapValueLeft.size() - nullValuesGapLeft);
		}
		else{
			avgGraphValuesLeftGap[j] = (avgGraphValuesLeftGap[j]) / (GapValueLeft.size() - nullValuesGapLeft);
		}
		for (int i = 0; i < NoGapValueLeft.size(); i++){
			avgGraphValuesLeftNoGap[j] += GraphValuesLeftNoGap[i][j];
		}
		if (j == windowsOffset / 2){
			avgGraphValuesLeftNoGap[j] = (avgGraphValuesLeftNoGap[j] - (nullValuesNoGapLeft*0.1)) / (NoGapValueLeft.size() - nullValuesNoGapLeft);
		}
		else{
			avgGraphValuesLeftNoGap[j] = (avgGraphValuesLeftNoGap[j]) / (NoGapValueLeft.size() - nullValuesNoGapLeft);
		}

		for (int i = 0; i < GapValueRight.size(); i++){

			avgGraphValuesRightGap[j] += GraphValuesRightGap[i][j];
		}
		if (j == windowsOffset / 2){
			avgGraphValuesRightGap[j] = (avgGraphValuesRightGap[j] - (nullValuesGapRight*0.1)) / (GapValueRight.size() - nullValuesGapRight);
		}
		else{
			avgGraphValuesRightGap[j] = (avgGraphValuesRightGap[j]) / (GapValueRight.size() - nullValuesGapRight);
		}

		for (int i = 0; i < NoGapValueRight.size(); i++){

			avgGraphValuesRightNoGap[j] += GraphValuesRightNoGap[i][j];
		}
		if (j == windowsOffset / 2){
			avgGraphValuesRightNoGap[j] = (avgGraphValuesRightNoGap[j] - (nullValuesNoGapRight*0.1)) / (NoGapValueRight.size() - nullValuesNoGapRight);
		}
		else{
			avgGraphValuesRightNoGap[j] = (avgGraphValuesRightNoGap[j]) / (NoGapValueRight.size() - nullValuesNoGapRight);
		}

	}

	//clear graphs
	RightNoGap->clearGraphs();
	RightGap->clearGraphs();
	LeftGap->clearGraphs();
	LeftNoGap->clearGraphs();
	RightNoGap->replot();
	RightGap->replot();
	LeftGap->replot();
	LeftNoGap->replot();


	QVector<double> biggestGraphValue2(windowsOffset + 1);
	biggestGraphValue2 = QVector<double>::fromStdVector(biggestGraphValue);
	//this can be done in one for if lenghts are the same
	for (int i = 0; i < GapValueLeft.size(); i++){
		Color.setRgb(rand() % 100 + 100, rand() % 100 + 100, rand() % 100 + 100);
		//translate vector to qvector
		GraphValuesLeftGapQVector[i] = QVector<double>::fromStdVector(GraphValuesLeftGap[i]);
		LeftGap->addGraph();
		LeftGap->graph(i)->setPen(colores[colorGap[i]]);
		//add first the biggest and first
		if (i == 0){
			LeftGap->graph(i)->setData(x, biggestGraphValue2);
			LeftGap->graph(i)->rescaleAxes();
			LeftGap->graph(i)->setData(x, GraphValuesLeftGapQVector[i]);
			LeftGap->graph(i)->rescaleAxes(true);
		}
		else{//add others
			LeftGap->graph(i)->setData(x, GraphValuesLeftGapQVector[i]);
			LeftGap->graph(i)->rescaleAxes(true);
		}


	}
	//add the avgs
	Color.setRgb(0, 0, 0);
	LeftGap->addGraph();
	QPen pen;
	pen.setColor(Color);
	//bigger size
	pen.setWidth(3);
	LeftGap->graph(GapValueLeft.size())->setPen(pen);
	LeftGap->graph(GapValueLeft.size())->setData(x, avgGraphValuesLeftGap);
	LeftGap->graph(GapValueLeft.size())->rescaleAxes(true);


	//same as before
	for (int i = 0; i < NoGapValueLeft.size(); i++){
		Color.setRgb(rand() % 100 + 100, rand() % 100 + 100, rand() % 100 + 100);

		GraphValuesLeftNoGapQVector[i] = QVector<double>::fromStdVector(GraphValuesLeftNoGap[i]);
		LeftNoGap->addGraph();
		LeftNoGap->graph(i)->setPen(colores[colorNoGap[i]]);
		if (i == 0){
			LeftNoGap->graph(i)->setData(x, biggestGraphValue2);
			LeftNoGap->graph(i)->rescaleAxes();
			LeftNoGap->graph(i)->setData(x, GraphValuesLeftNoGapQVector[i]);
			LeftNoGap->graph(i)->rescaleAxes(true);
		}
		else{
			LeftNoGap->graph(i)->setData(x, GraphValuesLeftNoGapQVector[i]);
			LeftNoGap->graph(i)->rescaleAxes(true);
		}

	}
	Color.setRgb(0, 0, 0);
	LeftNoGap->addGraph();

	pen.setColor(Color);
	pen.setWidth(3);
	LeftNoGap->graph(NoGapValueLeft.size())->setPen(pen);
	LeftNoGap->graph(NoGapValueLeft.size())->setData(x, avgGraphValuesLeftNoGap);
	LeftNoGap->graph(NoGapValueLeft.size())->rescaleAxes(true);

	//same as before
	for (int i = 0; i < GapValueRight.size(); i++){
		Color.setRgb(rand() % 100 + 100, rand() % 100 + 100, rand() % 100 + 100);
		GraphValuesRightGapQVector[i] = QVector<double>::fromStdVector(GraphValuesRightGap[i]);
		RightGap->addGraph();
		RightGap->graph(i)->setPen(colores[colorGap[i]]);
		if (i == 0){
			RightGap->graph(i)->setData(x, biggestGraphValue2);
			RightGap->graph(i)->rescaleAxes();
			RightGap->graph(i)->setData(x, GraphValuesRightGapQVector[i]);
			RightGap->graph(i)->rescaleAxes(true);
		}
		else{
			RightGap->graph(i)->setData(x, GraphValuesRightGapQVector[i]);
			RightGap->graph(i)->rescaleAxes(true);
		}
	}
	Color.setRgb(0, 0, 0);
	RightGap->addGraph();

	pen.setColor(Color);
	pen.setWidth(3);
	RightGap->graph(GapValueRight.size())->setPen(pen);
	RightGap->graph(GapValueRight.size())->setData(x, avgGraphValuesRightGap);
	RightGap->graph(GapValueRight.size())->rescaleAxes(true);
	//same as before
	for (int i = 0; i < NoGapValueRight.size(); i++){
		Color.setRgb(rand() % 100 + 100, rand() % 100 + 100, rand() % 100 + 100);

		GraphValuesRightNoGapQVector[i] = QVector<double>::fromStdVector(GraphValuesRightNoGap[i]);
		RightNoGap->addGraph();
		RightNoGap->graph(i)->setPen(colores[colorNoGap[i]]);
		if (i == 0){
			RightNoGap->graph(i)->setData(x, biggestGraphValue2);
			RightNoGap->graph(i)->rescaleAxes();
			RightNoGap->graph(i)->setData(x, GraphValuesRightNoGapQVector[i]);
			RightNoGap->graph(i)->rescaleAxes(true);
		}
		else{
			RightNoGap->graph(i)->setData(x, GraphValuesRightNoGapQVector[i]);
			RightNoGap->graph(i)->rescaleAxes(true);
		}

	}
	Color.setRgb(0, 0, 0);
	RightNoGap->addGraph();
	pen.setColor(Color);
	pen.setWidth(3);
	RightNoGap->graph(NoGapValueRight.size())->setPen(pen);
	RightNoGap->graph(NoGapValueRight.size())->setData(x, avgGraphValuesRightNoGap);
	RightNoGap->graph(NoGapValueRight.size())->rescaleAxes(true);
	//draw graphics
	LeftGap->xAxis2->setVisible(true);
	LeftGap->xAxis2->setTickLabels(false);
	LeftGap->yAxis2->setVisible(true);
	LeftGap->yAxis2->setTickLabels(false);

	LeftGap->replot();

	LeftNoGap->xAxis2->setVisible(true);
	LeftNoGap->xAxis2->setTickLabels(false);
	LeftNoGap->yAxis2->setVisible(true);
	LeftNoGap->yAxis2->setTickLabels(false);

	LeftNoGap->replot();

	RightGap->xAxis2->setVisible(true);
	RightGap->xAxis2->setTickLabels(false);
	RightGap->yAxis2->setVisible(true);
	RightGap->yAxis2->setTickLabels(false);

	RightGap->replot();

	RightNoGap->xAxis2->setVisible(true);
	RightNoGap->xAxis2->setTickLabels(false);
	RightNoGap->yAxis2->setVisible(true);
	RightNoGap->yAxis2->setTickLabels(false);

	RightNoGap->replot();

	//printing to file
	//csvoutput normal big file
	//csvoutput3 = txt file
	//csvoutput2= ploting
	ofstream csvOutput;
	string s = outPath + "/" + dirp->d_name + reference + ".csv";
	csvOutput.open(s.c_str());

	QString a1 = (QString::number(GapAvgRight / NoGapAvgRight));
	QString a2 = (QString::number(GapAvgLeft / NoGapAvgLeft));
	rightRatio->setText(a1);
	leftRatio->setText(a2);

	csvOutput << "Diameter 100 frames" << endl;
	for (int i = 0; i < 20; i++){
		averageLeft.push_back(0);
		averageRight.push_back(0);
		int countavg = 0;
		for (int j = 0; j < areas3Left[i].size(); j++){
			averageLeft[i] += areas3Left[i][j];
			countavg++;
		}
		if (averageLeft[i]>0)
			averageLeft[i] /= countavg;
		countavg = 0;
		for (int j = 0; j < areas3Right[i].size(); j++){
			averageRight[i] += areas3Right[i][j];
			countavg++;
		}
		if (averageRight[i]>0)
			averageRight[i] /= countavg;
	}


	for (int i = 0; i < 20; i++){
		stdevLeft.push_back(0);
		stdevRight.push_back(0);
		for (int j = 0; j < areas3Right[i].size(); j++){
			stdevRight[i] += pow((areas3Right[i][j] - averageRight[i]), 2);

		}
		stdevRight[i] /= areas3Right[i].size();

		stdevRight[i] = sqrt(stdevRight[i]);
		for (int j = 0; j < areas3Left[i].size(); j++){
			stdevLeft[i] += pow((areas3Left[i][j] - averageLeft[i]), 2);
		}

		stdevLeft[i] /= areas3Left[i].size();
		stdevLeft[i] = sqrt(stdevLeft[i]);
	}
	//get averages but first find number of 0s
	//stdes and avgs from +-50

	csvOutput3 << "                   Diameter data old method(Areas)" << endl;
	for (int i = 0; i < LEDonoff.size() / 2; i++){

		if (num0sLeftOld[i]>30 || num0sRightOld[i] > 30 || num0sCenterLeftOld[i] > 30 || num0sCenterRightOld[i] > 30){
			csvOutput3 << "                        Trial " << i + 1 << " more than 30 ceros" << endl;
		}

	}
	csvOutput3 << "                   Diameter data new method(Enclosing circle)" << endl;
	for (int i = 0; i < LEDonoff.size() / 2; i++){

		if (num0sLeftNew[i]>30 || num0sRightNew[i] > 30 || num0sCenterLeftNew[i] > 30 || num0sCenterRightNew[i] > 30){
			csvOutput3 << "                        Trial " << i + 1 << " more than 30 ceros" << endl;
		}


	}
	for (int i = 0; i < LEDonoff.size() / 2; i++){
		if (tiltVector[i] == true){
			csvOutput3 << "                             Trial" << i + 1 << "Tilted more than expected" << endl;
		}
	}
	//time to get stdev  =each sum(element-avg)^2 /total elements pow((areas3Left[i][j]-averageLeft[i]),2);
	for (int i = 0; i < LEDonoff.size() / 2; i++){
		stdevLeftOld.push_back(0);
		stdevRightOld.push_back(0);
		stdevCenterLeftOld.push_back(0);
		stdevCenterRightOld.push_back(0);
		stdevLeftNew.push_back(0);
		stdevRightNew.push_back(0);
		stdevCenterLeftNew.push_back(0);
		stdevCenterRightNew.push_back(0);
		for (int j = 0; j < 101; j++){
			if (diameterLeftOldBig[i][j] == 0){}
			else{
				stdevLeftOld[i] += pow((diameterLeftOldBig[i][j] - avgsLeftOld[i]), 2);
			}
			if (diameterRightOldBig[i][j] == 0){}
			else{
				stdevRightOld[i] += pow((diameterRightOldBig[i][j] - avgsRightOld[i]), 2);
			}
			if (diameterCenterOldBigLeft[i][j] == 0){}
			else{
				stdevCenterLeftOld[i] += pow((diameterCenterOldBigLeft[i][j] - avgsCenterLeftOld[i]), 2);
			}
			if (diameterCenterOldBigRight[i][j] == 0){}
			else{
				stdevCenterRightOld[i] += pow((diameterCenterOldBigRight[i][j] - avgsCenterRightOld[i]), 2);
			}
			if (diameterLeftNewBig[i][j] == 0){}
			else{
				stdevLeftNew[i] += pow((diameterLeftNewBig[i][j] - avgsLeftNew[i]), 2);
			}
			if (diameterRightNewBig[i][j] == 0){}
			else{
				stdevRightNew[i] += pow((diameterRightNewBig[i][j] - avgsRightNew[i]), 2);
			}
			if (diameterCenterNewBigLeft[i][j] == 0){}
			else{
				stdevCenterLeftNew[i] += pow((diameterCenterNewBigLeft[i][j] - avgsCenterLeftNew[i]), 2);
			}
			if (diameterCenterNewBigRight[i][j] == 0){}
			else{
				stdevCenterRightNew[i] += pow((diameterCenterNewBigRight[i][j] - avgsCenterRightNew[i]), 2);
			}

		}
		//make the division
		if (num0sLeftOld[i] == 101){
			stdevLeftOld[i] = 0;
		}
		else{
			stdevLeftOld[i] /= 101 - num0sLeftOld[i];
		}

		if (num0sRightOld[i] == 101){
			stdevRightOld[i] = 0;
		}
		else{
			stdevRightOld[i] /= 101 - num0sRightOld[i];
		}

		if (num0sCenterLeftOld[i] == 101){
			stdevCenterLeftOld[i] = 0;
		}
		else{
			stdevCenterLeftOld[i] /= 101 - num0sCenterLeftOld[i];
		}

		if (num0sCenterRightOld[i] == 101){
			stdevCenterRightOld[i] = 0;
		}
		else{
			stdevCenterRightOld[i] /= 101 - num0sCenterRightOld[i];
		}

		if (num0sLeftNew[i] == 101){
			stdevLeftNew[i] = 0;
		}
		else{
			stdevLeftNew[i] /= 101 - num0sLeftNew[i];
		}

		if (num0sRightNew[i] == 101){
			stdevRightNew[i] = 0;
		}
		else{
			stdevRightNew[i] /= 101 - num0sRightNew[i];
		}

		if (num0sCenterLeftNew[i] == 101){
			stdevCenterLeftNew[i] = 0;
		}
		else{
			stdevCenterLeftNew[i] /= 101 - num0sCenterLeftNew[i];
		}

		if (num0sCenterRightNew[i] == 101){
			stdevCenterRightNew[i] = 0;
		}
		else{
			stdevCenterRightNew[i] /= 101 - num0sCenterRightNew[i];
		}
		stdevCenterLeftNew[i] = sqrt(stdevCenterLeftNew[i]);
		stdevCenterLeftOld[i] = sqrt(stdevCenterLeftOld[i]);
		stdevCenterRightNew[i] = sqrt(stdevCenterRightNew[i]);
		stdevCenterRightOld[i] = sqrt(stdevCenterRightOld[i]);
		stdevLeftNew[i] = sqrt(stdevLeftNew[i]);
		stdevLeftOld[i] = sqrt(stdevLeftOld[i]);
		stdevRightNew[i] = sqrt(stdevRightNew[i]);
		stdevRightOld[i] = sqrt(stdevRightOld[i]);

	}

	//output to files
	for (int i = 0; i < LEDonoff.size() / 2; i++){
		if (num0sLeftOld[i]>30 || num0sRightOld[i] > 30 || num0sCenterLeftOld[i] > 30 || num0sCenterRightOld[i] > 30 ||
			num0sLeftNew[i] > 30 || num0sCenterLeftNew[i] > 30 || num0sRightNew[i] > 30 || num0sCenterRightNew[i] > 30){
			csvOutput << "Averages,,,,Not viable more than 30 ceros" << endl;
		}
		else{ csvOutput << "Averages" << endl; }
		csvOutput << "LeftOld,LeftCenterOld,RightOld,RightCenterOld,LeftNew,LefCenterNew,RightNew,RightCenterNew" << endl;

		csvOutput << avgsLeftOld[i] << "," << avgsCenterLeftOld[i] << "," << avgsRightOld[i] << "," << avgsCenterRightOld[i] << "," <<
			avgsLeftNew[i] << "," << avgsCenterLeftNew[i] << "," << avgsRightNew[i] << "," << avgsCenterRightNew[i] << endl;

		csvOutput << "Stdev" << endl;
		csvOutput << "LeftOld,LeftCenterOld,RightOld,RightCenterOld,LeftNew,LefCenterNew,RightNew,RightCenterNew" << endl;
		csvOutput << stdevLeftOld[i] << "," << stdevCenterLeftOld[i] << "," << stdevRightOld[i] << "," << stdevCenterRightOld[i] << "," <<
			stdevLeftNew[i] << "," << stdevCenterLeftNew[i] << "," << stdevRightNew[i] << "," << stdevCenterRightNew[i] << endl;

		csvOutput << "leftOld,LeftCenterOld,RightOld,RightCenterOld,LeftNew,LeftCenterNew,RightNew,RightCenterNew" << endl;
		for (int j = 0; j < 101; j++){
			csvOutput << diameterLeftOldBig[i][j] << "," << diameterCenterOldBigLeft[i][j] << "," << diameterRightOldBig[i][j] << "," << diameterCenterOldBigRight[i][j] <<
				"," << diameterLeftNewBig[i][j] << "," << diameterCenterNewBigLeft[i][j] << "," << diameterRightNewBig[i][j] << "," << diameterCenterNewBigRight[i][j] << endl;
		}

	}



	for (int i = 0; i < coordData.x0.size(); i++)
	{

		if (i == 0){

			csvOutput << "Left Ear X Pos," << "Left Ear Y Pos," << "Left Ear Magnitud,"
				<< "Center X Pos," << "Center Y Pos," << "Center Magnitud,"
				<< "Right Ear X Pos," << "Right Ear Y Pos," << "Right Ear Magnitud,,"
				<< "Left Ear Normalized Value," << "Right Ear Normalized Value,,Left in mms.,Right in mms.,Tilt rate" << endl;
		}


		double convertingRatio;
		for (int x = 0; x < LEDonoff.size(); x = x + 2){
			if (i == LEDonoff[x])
				csvOutput << "TRIAL #" << (x / 2) + 1 << endl << endl;
			if (i >= LEDonoff[x]){
				if (avgsCenterRightNew[x / 2] == 0){
					convertingRatio = 0;
				}
				else{
					convertingRatio = dots / avgsCenterRightNew[x / 2];
				}
			}
		}
		csvOutput << coordData.x0[i] << "," << coordData.y0[i] << "," <<
			coordData.magnitude0[i] << "," << coordData.x1[i] <<
			"," << coordData.y1[i] << "," << coordData.magnitude1[i]
			<< "," << coordData.x2[i] << "," << coordData.y2[i] <<
			"," << coordData.magnitude2[i];

		if (i < 2){
			csvOutput << ",," << 0 << "," << 0 << ",," << 0 << "," << 0 << "," << 0;
		}
		else{
			csvOutput << ",," << coordData.normalized0[i] << "," << coordData.normalized2[i] << ",," << coordData.normalized0[i] * convertingRatio << "," << coordData.normalized2[i] * convertingRatio << "," << tiltRate[i];
		}
		csvOutput << endl;

	}
	cout << "4" << endl;
	csvOutput.close();
	ofstream csvOutput2;
	s = outPath + "/" + dirp->d_name + "Plots.csv";
	csvOutput2.open(s.c_str());

	//writting the file
	//csvOutput2<<endl<<endl;

	//Here change from pixel to mmls

	csvOutput2 << ",LeftNoGap,RightNoGap,LeftGap,RightGap" << endl;
	int maxvalue;
	int minvalue;
	int isGap = 1;
	maxvalue = GapValueLeft.size();
	minvalue = NoGapValueLeft.size();
	if (GapValueLeft.size() < NoGapValueLeft.size()){
		maxvalue = NoGapValueLeft.size();
		minvalue = GapValueLeft.size();
		isGap = 0;
	}
	for (int i = 0; i < minvalue; i++){
		csvOutput2 << "," << NoGapValueLeft[i] << "," << NoGapValueRight[i] << "," << GapValueLeft[i] << "," << GapValueRight[i] << endl;
	}
	if (isGap == 1){
		for (int i = minvalue; i < maxvalue; i++){
			csvOutput2 << ",0,0," << GapValueLeft[i] << "," << GapValueRight[i] << endl;
		}

	}
	else{
		for (int i = minvalue; i < maxvalue; i++){
			csvOutput2 << "," << NoGapValueLeft[i] << "," << NoGapValueRight[i] << ",0,0," << endl;
		}
	}
	csvOutput2 << "Avg," << NoGapAvgLeft << "," << NoGapAvgRight << "," << GapAvgLeft << "," << GapAvgRight << endl;
	csvOutput2 << "Ratio,,,Left,Right" << endl;
	csvOutput2 << ",,," << GapAvgLeft / NoGapAvgLeft << "," << GapAvgRight / NoGapAvgRight << endl;

	csvOutput2 << "1," << endl;
	csvOutput2 << ",";
	for (int i = 0; i < biggestGraphValue.size(); i++)
		csvOutput2 << biggestGraphValue[i] << ",";
	csvOutput2 << endl;

	cout << "5" << endl;

	csvOutput2 << "LeftNoGap," << endl;
	csvOutput2 << NoGapValueLeft.size() + 1 << "," << endl;
	for (int i = 0; i < NoGapValueLeft.size(); i++){
		csvOutput2 << colorNoGap[i] << ",";
		for (int j = 0; j < GraphValuesLeftNoGap[i].size(); j++)
			csvOutput2 << GraphValuesLeftNoGap[i][j] << ",";
		csvOutput2 << endl;
	}
	csvOutput2 << ",";
	for (int i = 0; i < avgGraphValuesLeftNoGap.size(); i++){
		csvOutput2 << avgGraphValuesLeftNoGap[i] << ",";
	}
	csvOutput2 << endl;

	csvOutput2 << "RightNoGap," << endl;
	csvOutput2 << NoGapValueRight.size() + 1 << "," << endl;
	for (int i = 0; i < NoGapValueRight.size(); i++){
		csvOutput2 << colorNoGap[i] << ",";
		for (int j = 0; j < GraphValuesRightNoGap[i].size(); j++)
			csvOutput2 << GraphValuesRightNoGap[i][j] << ",";
		csvOutput2 << endl;
	}
	csvOutput2 << ",";
	for (int i = 0; i < avgGraphValuesRightNoGap.size(); i++){
		csvOutput2 << avgGraphValuesRightNoGap[i] << ",";
	}
	csvOutput2 << endl;

	csvOutput2 << "LeftGap," << endl;
	csvOutput2 << GapValueLeft.size() + 1 << "," << endl;
	for (int i = 0; i < GapValueLeft.size(); i++){
		csvOutput2 << colorGap[i] << ",";
		for (int j = 0; j < GraphValuesLeftGap[i].size(); j++)
			csvOutput2 << GraphValuesLeftGap[i][j] << ",";
		csvOutput2 << endl;
	}
	csvOutput2 << ",";
	for (int i = 0; i < avgGraphValuesLeftGap.size(); i++){
		csvOutput2 << avgGraphValuesLeftGap[i] << ",";
	}
	csvOutput2 << endl;

	csvOutput2 << "RightGap," << endl;
	csvOutput2 << GapValueRight.size() + 1 << "," << endl;
	for (int i = 0; i < GapValueRight.size(); i++){
		csvOutput2 << colorGap[i] << ",";
		for (int j = 0; j < GraphValuesRightGap[i].size(); j++)
			csvOutput2 << GraphValuesRightGap[i][j] << ",";
		csvOutput2 << endl;
	}
	csvOutput2 << ",";
	for (int i = 0; i < avgGraphValuesRightGap.size(); i++){
		csvOutput2 << avgGraphValuesRightGap[i] << ",";
	}
	csvOutput2 << endl;
	csvOutput2.close();
	csvOutput3.close();
}


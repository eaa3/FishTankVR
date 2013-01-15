#pragma once

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;

const string FACE_DETECTOR_CONFIG_FILE = "haarcascade_frontalface_alt.xml";

class FaceDetector
{
private:

	CascadeClassifier face_cascade;

public:

	vector<Rect> detectionResult;
	bool isOk;

	FaceDetector( string filename );
	
	FaceDetector( );

	void init( string filename );

	void detect( Mat& img );

};


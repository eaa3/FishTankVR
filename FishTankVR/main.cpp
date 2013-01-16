#include <opencv2/opencv.hpp>
#include "HeadTracker.h"


using namespace cv;
using namespace tld;


int main()
{

	Mat frame;

	VideoCapture cap(0);

	HeadTracker ht;

	while( !ht.inited) {


	while( waitKey(1) < 0 ) 
	{

		cap >> frame;





		imshow("lol",frame);
	}

	return 0;
}



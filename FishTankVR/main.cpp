#include <opencv2/opencv.hpp>
#include "Predator.h"


using namespace cv;
using namespace tld;


int main()
{

	Mat frame;

	VideoCapture cap(0);

	Predator p(TLD_CONFIG_FILE);


	while( waitKey(1) < 0 ) 
	{

		cap >> frame;


		imshow("lol",frame);
	}

	return 0;
}



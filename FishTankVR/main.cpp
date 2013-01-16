#include <opencv2/opencv.hpp>
#include "HeadTracker.h"


using namespace cv;
using namespace tld;

float estimator(const BoundingBox& bb){

	return -0.3756*bb.w + 126.73;
}

int main()
{

	Mat frame;

	VideoCapture cap(0);

	HeadTracker ht;

	do{

		cap >> frame;

		ht.init(frame);

	}while( !ht.isInited() );


	while( waitKey(1) < 0 ) 
	{

		cap >> frame;


		BoundingBox bb = ht.track(frame);

		draw_box(bb,frame,Scalar(255,0,0));

		Vector3 v = ht.estimateSpacePosition(bb,640,57.61f,480,37.5f,estimator);

		printf("\r(%.2f,%.2f,%.2f)",v[0],v[1],v[2]);


		imshow("lol",frame);
	}

	return 0;
}



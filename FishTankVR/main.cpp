#include <opencv2/opencv.hpp>
#include "HeadTracker.h"
#include "FishTank.h"

using namespace cv;
using namespace tld;

Mat frame;

VideoCapture cap(0);

HeadTracker ht;

FishTank ft;

float W = 640.0f;
float H = 480.0f;
float realW = 57.61f;
float realH = 37.5f;

float estimator(const BoundingBox& bb){

	return -0.3756*bb.w + 126.73;
}

void init()
{

	do{

		cap >> frame;

		ht.init(frame);

	}while( !ht.isInited() );


	ft.setInitialFrustum(-0.5f,0.5f,-0.5f,0.5f,1,10, W/H);

}



void display()
{
	glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	cap >> frame;

	BoundingBox bb = ht.track(frame);

	draw_box(bb,frame,Scalar(255,0,0));

	imshow("lol",frame);



	Vec3f v = ht.estimateSpacePosition(bb,W,realW,H,realH,estimator);
	v[0] = v[0]/(realW/2);
	v[1] = v[1]/(realH/2);
	v[2] = v[2]/60.0f;

	Vector3 eyepos(v[0],v[1],v[2] );

	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();

	ft.setFrustum( eyepos );

	cout << eyepos << endl;

	glMultMatrixf(ft.proj.getTranspose());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();



	//ft.setView( eyepos );

	
	gluLookAt(eyepos.x,eyepos.y,-eyepos.z,eyepos.x,eyepos.y,0,0,1,0);
	
	
	glTranslatef(0,0,2);
	glRotatef(30,1,1,0);
	
	//glColor3f(0.7,0.7,0.7);
	glutSolidTorus(.5f,0.3, 10, 10);
	//glutSolidCube(0.2f);

	glutSwapBuffers();
	glutPostRedisplay();
	

}

void idleFunc()
{
	glutPostRedisplay();
}



int main(int argc, char** argv)
{
	
	



	


	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (640, 480);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Test");
	
	
	init();	
	
	glutDisplayFunc(display);


	glutIdleFunc(idleFunc);	

	//atexit(deinit);

	glutMainLoop();

	/*
	while( waitKey(1) < 0 ) 
	{

		cap >> frame;


		BoundingBox bb = ht.track(frame);

		draw_box(bb,frame,Scalar(255,0,0));

		Vec3f v = ht.estimateSpacePosition(bb,640,57.61f,480,37.5f,estimator);

		printf("\r(%.2f,%.2f,%.2f)",v[0],v[1],v[2]);


		imshow("lol",frame);
	}
	*/

	return 0;
}



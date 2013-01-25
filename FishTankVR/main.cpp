
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
float angle = 0;

float estimator(const BoundingBox& bb){

	return -0.3756*bb.w + 126.73;
}

void init()
{

	do{

		cap >> frame;

		ht.init(frame);

	}while( !ht.isInited() );


	ft.setInitialFrustum(-realW/2,realW/2,-realH/2,realH/2,1.0f,400, 1);

	glEnable(GL_DEPTH_TEST);

}

void drawQuad(float angle, Vec3f t, Vec3f rot_axis, Vec4f color = Vec4f(0.8f,0.8f,0.8f,0.5f))
{
	glPushMatrix();
	glColor4f(color[0],color[1], color[2], color[3]);
	glTranslatef(t[0], t[1], t[2]);
	glRotatef(angle, rot_axis[0],rot_axis[1],rot_axis[2]);	
	glBegin(GL_QUADS);
	{
		glVertex3f(ft.l, ft.b, 0);
		glVertex3f(ft.r, ft.b, 0);
		glVertex3f(ft.r, ft.t, 0);
		glVertex3f(ft.l, ft.t, 0);

	}
	glEnd();
	glPopMatrix();

}
	




void display()
{
	glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	cap >> frame;

	BoundingBox bb = ht.track(frame);

	draw_box(bb,frame,Scalar(255,0,0));

	imshow("lol",frame);



	Vec3f v = ht.estimateSpacePosition(bb,W,realW,H,realH,estimator);
	//v[0] = v[0]/(realW/2);
	//v[1] = v[1]/(realH/2);
	//v[2] = v[2]/60.0f;

	Vector3 eyepos(v[0],v[1],v[2] );

	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();

	ft.setFrustum( eyepos );

	
	//glFrustum(ft.l,ft.r,ft.b,ft.t, ft.n, ft.f);
	
	glMultMatrixf(ft.proj.getTranspose());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_BLEND);	

	//ft.setView( eyepos );
	//glMultMatrixf( ft.rt.getTranspose() );
	gluLookAt(-eyepos.x,eyepos.y,-eyepos.z,eyepos.x,eyepos.y,0,0,1,0);

	
	//drawQuad(90, Vec3f(ft.r,0,0), Vec3f(0,0,1), Vec4f(0.8,0.2,0.2,0.1)); //right quad
	//drawQuad(90, Vec3f(ft.l,0,0), Vec3f(0,0,1), Vec4f(0.8,0.2,0.2,0.1)); //left quad
	drawQuad(90, Vec3f(0,ft.b,0), Vec3f(1,0,0), Vec4f(0.8,0.2,0.2,0.8)); // bottom quad
	drawQuad(90, Vec3f(0,ft.t,0), Vec3f(1,0,0), Vec4f(0.8,0.2,0.2,0.8)); // bottom quad
	//drawQuad(0, Vec3f(0,0,-50), Vec3f(1,0,0), Vec4f(0.3,0.3,0.3,0.1)); 
	

	Matrix4 modelview;
	glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*) modelview.get());

	
	

	//glLoadMatrixf(ft.rt.getTranspose());
	
	cout << "\r" << "eyepos = " << eyepos << "\nModelView_A\n" << modelview << "\nModelview_B" << "--------------------\n" << ft.rt.transpose() << "--------------------\n";

	
	
	glTranslatef(5,-5, -20);
	//angle = (int(angle)+1)%360;
	
	glColor3f(0.7,0.7,0.7);
	
	glutSolidCube(10.0f);
	glColor3f(0,0,0);
	glutWireCube(10.2f);

	glTranslatef(-10,10, -10);
	//angle = (int(angle)+1)%360;
	
	glColor3f(0.7,0.7,0.7);
	
	glutSolidCube(10.0f);
	glColor3f(0,0,0);
	glutWireCube(10.2f);

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

	
	

	return 0;
}


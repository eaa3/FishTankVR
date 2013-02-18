
#include <opencv2/opencv.hpp>
#include "HeadTracker.h"
#include "FishTank.h"
#include <GL/glext.h>
#include <cstdlib>
#include <math.h>

using namespace cv;
using namespace tld;

Mat frame;

VideoCapture cap(0);

HeadTracker ht;

FishTank ft;

float W = 640.0f;
float H = 480.0f;
float realW = 0.275f; //0.4761f;//0.02f;//57.61f;
float realH = 0.275f; //0.02f;//37.5f;
float aspectRatio = 16.0f/9.0f;
float angle = 0;
Vector3 eyepos;
GLfloat size = 0.053f;//5.0f;

GLuint tex1, tex2, tex3, tex4, tex5;
bool activated = false;
bool fullScreen = false;

void setFishTankVRPerspective( Vector3 eyepos = Vector3(0,0,0.5) )
{
	//Setting up Fish Tank VR Frustum and Camera Extrinsic Params
	ft.setFrustum( eyepos );
	ft.setView( eyepos );

	glMatrixMode(GL_PROJECTION);	
	glLoadIdentity();

	glMultMatrixf(ft.proj.getTranspose());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glMultMatrixf( ft.rt.getTranspose() );
	//End of FTVR Setup
}

float estimator(const BoundingBox& bb){

	float a1 = bb.w*bb.h;
	float pi = atanf(1.0f)*4;
	float radiansPerPixel = (0.484f*2/W);

	float alpha = (bb.w*radiansPerPixel)/2;

	//float h = 0.59f*(320.0f*0.15f)/(bb.w*0.31f);
	float h = 0.15f/(2*tanf(alpha));
	float h2 = 0.59f*(320.0f*0.15f)/(bb.w*0.31f);

	printf("\nRadiansPP = %0.2f PI = %0.2f ALPHA = %0.2f OTHER_H = %.2f ERROR = %.2f\n", radiansPerPixel, pi, alpha, h2, (h-h2));
	return h;
	//return sqrtf(float(ht.originalBB.getArea())/a1);

	//return -0.3756*bb.w + 126.73;
}

void keyOp(unsigned char key, int x, int y)
{

	if( key == '+' ) eyepos[2] += 0.1;
	if( key == '-' ) eyepos[2] -= 0.1;

	if( key == '\r' ) activated = !activated;

	if( key == 'f' ) {

		glutPositionWindow(100,100); 

		fullScreen? glutReshapeWindow(800, 600)  : glutFullScreen();

		fullScreen = !fullScreen;

	}

	if( key == 'r' ) {

		ht.reset();

	}
}

GLuint loadTexture(string filename)
{
	Mat img = imread(filename);

	GLuint texture_id;


	glGenTextures(1, &texture_id);

	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	// Edit the texture object's image data using the information SDL_Surface gives us
	glTexImage2D( GL_TEXTURE_2D, 0, 4, img.cols, img.rows, 0, GL_BGR, GL_UNSIGNED_BYTE, img.data );

	img.release();


	return texture_id;
}

void drawQuad(float angle, Vec3f t, Vec3f rot_axis, Vec4f color = Vec4f(0.8f,0.8f,0.8f,0.5f), GLuint texture_id = 0, float w = 1, float h = 1, float aspectRatio = 1)
{
	glPushMatrix();
	glColor4f(color[0],color[1], color[2], color[3]);
	glTranslatef(t[0], t[1], t[2]);
	glRotatef(angle, rot_axis[0],rot_axis[1],rot_axis[2]);


	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture_id);

	float left = -w/2;
	float right = w/2;
	float top = h/2;
	float bottom = -h/2;

	glBegin(GL_QUADS);
	{
		glTexCoord2i(0,0);
		glVertex3f(left*aspectRatio, top, 0);

		glTexCoord2i(1,0);
		glVertex3f(right*aspectRatio, top, 0);

		glTexCoord2i(1,1);
		glVertex3f(right*aspectRatio, bottom, 0);

		glTexCoord2i(0,1);
		glVertex3f(left*aspectRatio, bottom, 0);
		
		
		

	}
	glEnd();


	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

}

void drawCube(float size, Vec3f pos, Vec4f color, bool wire_form = false)
{

	glPushMatrix();

	glTranslatef(pos[0], pos[1], pos[2]);

	glColor4f(color[0], color[1], color[2], color[3]);

	wire_form? glutWireCube(size) : glutSolidCube(size);

	glPopMatrix();	

}

void drawBorderedCube(float size, Vec3f pos, Vec4f color, Vec4f border_color)
{
	drawCube(size, pos, color, false);
	drawCube(size+0.001, pos, border_color, true);
}


void drawTeapot(float size, Vec3f pos, Vec4f color, bool wire_form = false)
{
	glPushMatrix();

	glTranslatef(pos[0], pos[1], pos[2]);

	glColor4f(color[0], color[1], color[2], color[3]);

	wire_form? glutWireTeapot(size) : glutSolidTeapot(size);

	glPopMatrix();
}

void drawBorderedTeapot(float size, Vec3f pos, Vec4f color, Vec4f border_color)
{
	drawTeapot(size, pos, color, false);
	drawTeapot(size+0.001, pos, border_color, true);
}




void init()
{

	do{

		cap >> frame;

		ht.init(frame);

	}while( !ht.isInited() && activated );


	ft.setInitialFrustum(-realW/2,realW/2,-realH/2,realH/2,0.01f,200, aspectRatio);

	glEnable(GL_DEPTH_TEST);


	tex1 = loadTexture("brick_wall.jpg");
	tex2 = loadTexture("floor.jpg");
	tex3 = loadTexture("sky.jpg");
	tex4 = loadTexture("deep-space.jpg");
	tex5 = loadTexture("initMessage.jpg");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	

	glViewport(0,0, W, H);

	setFishTankVRPerspective();

	/*
	glEnable( GL_CLIP_PLANE1 );
	Vec3f p(0, ft.t, 0);
	Vec3f n(0,1,0);

	double equation[] = { 0, -1, 0, ft.t };
	glClipPlane( GL_CLIP_PLANE1, equation);
	*/
	//eyepos = Vector3(0,0,34.9f);


}

void deinit(void)
{
	glDeleteTextures(1,&tex1);
	glDeleteTextures(1,&tex2);
	glDeleteTextures(1,&tex3);
	glDeleteTextures(1,&tex4);
	glDeleteTextures(1,&tex5);
}




void display()
{
	glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	cap >> frame;
	
	//BoundingBox which contains the user's head.
	BoundingBox bb = ht.track(frame);

	//Drawing bb around user's head.
	draw_box(bb,frame,Scalar(255,0,0));

	//Drawing lines to divide the video screen into four quadrants
	line(frame, Point2i(W/2,0), Point2i(W/2,H), Scalar(255,255,0), 2); 
	line(frame, Point2i(0,H/2), Point2i(W,H/2), Scalar(255,255,0), 2);

	//Drawing detected eye estimated position inside bounding box surrounding user's head
	Vec2f eye2D = ht.get2DEyePixelSpacePosition(bb, 0.3f);
	Point2f eye2DPosPixelSpace(eye2D);

	circle(frame, eye2DPosPixelSpace , 5, Scalar(0,255,0), 2);

	imshow("VoxarLabs - FTVR Eye Seeker",frame);

	if(activated){

		if( !ht.isInited() ) {

			ht.init(frame);

		}else if ( bb.valid ) {			

		Vec3f v = ht.estimateSpacePosition(bb,W,realW,H,realH,estimator, 0.3f);
		v[1] += realH*0.25f;

		eyepos = Vector3(v[0]*aspectRatio,v[1],v[2] );
		
		setFishTankVRPerspective( eyepos );
		}

	}
	else
	{
		drawQuad(0, Vec3f(-0.10f,0.05f,0.0f), Vec3f(1,0,0), Vec4f(1,1,1,1), tex5, 0.10, 0.10, aspectRatio); // front quad
	}


	drawQuad(90, Vec3f(ft.r*aspectRatio,0,0), Vec3f(0,1,0), Vec4f(1,1,1,1), tex1, realW, realH, aspectRatio); //right quad
	drawQuad(90, Vec3f(ft.l*aspectRatio,0,0), Vec3f(0,1,0), Vec4f(1,1,1,1), tex1, realW, realH, aspectRatio); //left quad
	drawQuad(90, Vec3f(0,ft.b,0), Vec3f(1,0,0), Vec4f(1,1,1,1), tex2, realW, 1, aspectRatio); // bottom quad
	drawQuad(90, Vec3f(0,ft.t,-0.20f), Vec3f(1,0,0), Vec4f(1,1,1,1), tex3, realW, 1, aspectRatio); // top quad
	drawQuad(0, Vec3f(0,0,-0.25), Vec3f(1,0,0), Vec4f(1,1,1,1), tex4, realW, realH, aspectRatio); // back quad


	//Matrix4 modelview;
	//glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*) modelview.get());
	//glLoadMatrixf(ft.rt.getTranspose());
	//cout << "\r" << "eyepos = " << eyepos << "\nModelView_A\n" << modelview << "\nModelview_B" << "--------------------\n" << ft.rt.transpose() << "--------------------\n";



	drawBorderedCube(size, Vec3f(0,0,size/2), Vec4f(0.8,0.3,0.3,0.1), Vec4f(0,0,0,0));

	drawBorderedCube(size, Vec3f(-0.10,-0.10, -0.05), Vec4f(0.3,0.8,0.3,0.1), Vec4f(0,0,0,0) );

	drawBorderedCube(size, Vec3f(0.20,-0.10, -0.05), Vec4f(0.3,0.3,0.8,0.3), Vec4f(0,0,0,0) );


	drawBorderedTeapot(size-0.02, Vec3f(-0.18, ft.b + 0.025, -0.10), Vec4f(0.3,0.3,0.8,0.3), Vec4f(0,0,0,0) );


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
	glutCreateWindow ("VoxarLabs - Fish Tank Virtual Reality by Ermano Arruda 14-02-2013");


	init();
	atexit(deinit);

	glutDisplayFunc(display);

	glutIdleFunc(idleFunc);

	glutKeyboardFunc(keyOp);
	
	glutMainLoop();




	return 0;
}


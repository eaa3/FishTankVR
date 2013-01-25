
#include <opencv2/opencv.hpp>
#include "HeadTracker.h"
#include "FishTank.h"
//#include <GL/glext.h>

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

GLuint tex;

float estimator(const BoundingBox& bb){

	return -0.3756*bb.w + 126.73;
}

GLuint loadTexture(string filename)
{
	Mat img = imread(filename);

	GLuint texture_id;

	
	glGenTextures(1, &texture_id);

	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // Edit the texture object's image data using the information SDL_Surface gives us

	
    //glTexImage2D( GL_TEXTURE_2D, 0, 4, img.cols, img.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.data );

	//img.release();

	
	return texture_id;
}


void init()
{

	do{

		cap >> frame;

		ht.init(frame);

	}while( !ht.isInited() );


	ft.setInitialFrustum(-realW/2,realW/2,-realH/2,realH/2,1.0f,400, 1);

	glEnable(GL_DEPTH_TEST);


	tex = loadTexture("window.png");


}

void drawQuad(float angle, Vec3f t, Vec3f rot_axis, Vec4f color = Vec4f(0.8f,0.8f,0.8f,0.5f))
{
	glPushMatrix();
	glColor4f(color[0],color[1], color[2], color[3]);
	glTranslatef(t[0], t[1], t[2]);
	glRotatef(angle, rot_axis[0],rot_axis[1],rot_axis[2]);


	//glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex);

	glBegin(GL_QUADS);
	{
		//glTexCoord2i(0,0);
		glVertex3f(ft.l, ft.b, 0);
		//glTexCoord2i(1,0);
		glVertex3f(ft.r, ft.b, 0);
		//glTexCoord2i(1,1);
		glVertex3f(ft.r, ft.t, 0);
		//glTexCoord2i(0,1);
		glVertex3f(ft.l, ft.t, 0);

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
	
	wire_form? glutWireCube(10.2f) : glutSolidCube(size);

	glPopMatrix();	

}

void drawBorderedCube(float size, Vec3f pos, Vec4f color, Vec4f border_color)
{
	drawCube(size, pos, color, false);
	drawCube(size+0.01, pos, border_color, true);
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

	
	//glFrustum((ft.l - eyepos.x)/eyepos.z,(ft.r - eyepos.x)/eyepos.z,(ft.b - eyepos.y)/eyepos.z,(ft.t - eyepos.y)/eyepos.z, ft.n, ft.f);
	
	glMultMatrixf(ft.proj.getTranspose());

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	ft.setView( eyepos );
	glMultMatrixf( ft.rt.getTranspose() );
	

	
	//drawQuad(90, Vec3f(ft.r,0,0), Vec3f(0,0,1), Vec4f(0.8,0.2,0.2,0.1)); //right quad
	//drawQuad(90, Vec3f(ft.l,0,0), Vec3f(0,0,1), Vec4f(0.8,0.2,0.2,0.1)); //left quad
	drawQuad(90, Vec3f(0,ft.b,0), Vec3f(1,0,0), Vec4f(0.8,0.2,0.2,0.8)); // bottom quad
	drawQuad(90, Vec3f(0,ft.t,0), Vec3f(1,0,0), Vec4f(0.8,0.2,0.2,0.8)); // bottom quad
	//drawQuad(0, Vec3f(0,0,-50), Vec3f(1,0,0), Vec4f(0.3,0.3,0.3,0.1)); 
	

	Matrix4 modelview;
	glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*) modelview.get());

	
	

	//glLoadMatrixf(ft.rt.getTranspose());
	
	cout << "\r" << "eyepos = " << eyepos << "\nModelView_A\n" << modelview << "\nModelview_B" << "--------------------\n" << ft.rt.transpose() << "--------------------\n";

	

	drawBorderedCube(10.0f, Vec3f(0,0,20), Vec4f(0.7,0.7,0.7,0.1), Vec4f(0,0,0,0));
	
	drawBorderedCube(10.0f, Vec3f(-10,10, -20), Vec4f(0.7,0.7,0.7,0.1), Vec4f(0,0,0,0) );

	drawBorderedCube(10.0f, Vec3f(30,10, -20), Vec4f(0.3,0.3,0.8,0.3), Vec4f(0,0,0,0) );
	

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


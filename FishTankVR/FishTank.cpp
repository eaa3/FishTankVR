#include "FishTank.h"


FishTank::FishTank(float l, float r, float b, float t, float n, float f, float aspectRatio)
{

	
	this->setInitialFrustum(l,r,b,t,n,f,aspectRatio);


}

FishTank::FishTank()
{
	this->l = this->r = this->b = this->t = this->n = this->f = 0;
	this->aspectRatio = 0;


}


FishTank::~FishTank(void)
{
}


void FishTank::setInitialFrustum(float l, float r, float b, float t, float n, float f, float aspectRatio)
{
	this->l = l;
	this->r = r;
	this->b = b;
	this->t = t;
	this->n = n;
	this->f = f;
	this->aspectRatio = aspectRatio;
}


void FishTank::setFrustum( Vector3 eyepos )
{
	float newL = (l*aspectRatio - eyepos.x*n)/eyepos.z;
	float newR = (r*aspectRatio - eyepos.x*n)/eyepos.z;
	float newB =(b - eyepos.y*n)/eyepos.z;
	float newT = (t - eyepos.y*n)/eyepos.z;
	float newN = n;
	float newF = f;




	this->proj[0]  = 2 * newN / (newR - newL);
    this->proj[2]  = (newR + newL) / (newR - newL);
    this->proj[5]  = 2 * newN / (newT - newB);
    this->proj[6]  = (newT + newB) / (newT - newB);
    this->proj[10] = -(newF + newN) / (newF - newN);
    this->proj[11] = -(2 * newF * newN) / (newF - newN);
    this->proj[14] = -1;
    this->proj[15] = 0;


	

}

void FishTank::setView( Vector3 eyepos )
{
	Vector3 target(eyepos.x,eyepos.y,0);

	Vector3 forward = target - eyepos;
	forward.normalize();

	Vector3 up(0,1,0);
	Vector3 left = forward.cross(up);
	left.normalize();

	up = left.cross(forward);
	up.normalize();

	this->rt = Matrix4(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);

	this->rt.setColumn(0, left);
    this->rt.setColumn(1, up);
    this->rt.setColumn(2, -forward);


	Vector3 t = (rt*(-eyepos));

	this->rt.setColumn(3, t);

	this->rt[15] = 1;

}

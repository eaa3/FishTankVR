#include "FishTank.h"


FishTank::FishTank(float l, float r, float b, float t, float n, float f)
{

	
	this->setInitialFrustum(l,r,b,t,n,f);


}

FishTank::FishTank(float realW, float realH, float n , float f )
{
	this->setInitialFrustum(realW,realH,n,f);
}

FishTank::FishTank()
{
	this->l = this->r = this->b = this->t = this->n = this->f = 0;
	this->aspectRatio = 0;


}


FishTank::~FishTank(void)
{
}


void FishTank::setInitialFrustum(float l, float r, float b, float t, float n, float f)
{
	this->l = l;
	this->r = r;
	this->b = b;
	this->t = t;
	this->n = n;
	this->f = f;

}

void FishTank::setInitialFrustum(float realW, float realH, float n, float f  )
{
	this->setInitialFrustum( -realW/2, realW/2, -realH/2, realH/2, n, f);
	this->aspectRatio = realW/realH;
}





void FishTank::setFrustum( Vector3 eyepos )
{
	float newL = ((l - eyepos[0])*n)/eyepos[2];
	float newR = ((r - eyepos[0])*n)/eyepos[2];
	float newB =((b - eyepos[1])*n)/eyepos[2];
	float newT = ((t - eyepos[1])*n)/eyepos[2];
	float newN = n;
	float newF = f;


	printf("\neyepos(%0.2f,%0.2f,%0.2f) \nL %0.5f R %0.5f B %0.5f T %0.5f N %0.5f F %0.5f",eyepos[0], eyepos[1], eyepos[2], newL, newR, newB, newT, newN, newF); 




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
	Vector3 l = forward.cross(up);
	l.normalize();

	up = l.cross(forward);
	up.normalize();

	this->rt = Matrix4(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0);

	this->rt.setColumn(0, l);
    this->rt.setColumn(1, up);
    this->rt.setColumn(2, -forward);


	Vector3 t = (rt*(-eyepos));

	this->rt.setColumn(3, t);

	this->rt[15] = 1;

}

void FishTank::setAll( Vector3 eyepos )
{
	this->setFrustum(eyepos);
	this->setView(eyepos);
}
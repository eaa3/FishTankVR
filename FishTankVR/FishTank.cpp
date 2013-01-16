#include "FishTank.h"


FishTank::FishTank(float l, float r, float b, float t, float n, float f)
{
}


FishTank::~FishTank(void)
{
}

void FishTank::setFrustum( Vector3 eyepos )
{
	this->proj[0]  = 2 * n / (r - l);
    this->proj[2]  = (r + l) / (r - l);
    this->proj[5]  = 2 * n / (t - b);
    this->proj[6]  = (t + b) / (t - b);
    this->proj[10] = -(f + n) / (f - n);
    this->proj[11] = -(2 * f * n) / (f - n);
    this->proj[14] = -1;
    this->proj[15] = 0;

}

void FishTank::setView( Vector3 eyepos )
{
	Vector3 target(eyepos.x,eyepos.y,0);

	Vector3 forward = target - eyepos;
	forward.normalize();

	Vector3 up(0,1,0);
	Vector3 left = up.cross(forward);
	left.normalize();

	this->rt.setColumn(0, left);
    this->rt.setColumn(1, up);
    this->rt.setColumn(2, forward);


	Vector3 t = -rt*eyepos;

	this->rt.setColumn(3, t);

	this->rt[15] = 1;

}

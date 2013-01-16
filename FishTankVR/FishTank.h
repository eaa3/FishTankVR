#pragma once

#include "Matrices.h"
#include "Vectors.h"

class FishTank
{
public:

	Matrix4 proj;
	Matrix4 rt;

	float l, r, b, t, n, f;

	FishTank(float l, float r, float b, float t, float n, float f);

	void setFrustum( Vector3 eyepos );
	void setView( Vector3 eyepos );


	~FishTank(void);
};


#pragma once

#include "Matrices.h"
#include "Vectors.h"

class FishTank
{
public:

	Matrix4 proj;
	Matrix4 rt;

	float l, r, b, t, n, f;
	float aspectRatio;

	FishTank(float l, float r, float b, float t, float n, float f, float aspectRatio);
	FishTank();

	void setInitialFrustum(float l, float r, float b, float t, float n, float f, float aspectRatio);
	void setFrustum( Vector3 eyepos );
	void setView( Vector3 eyepos );


	~FishTank(void);
};


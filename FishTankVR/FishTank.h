#pragma once

#include "Matrices.h"
#include "Vectors.h"

class FishTank
{
public:

	Matrix4 proj;
	Matrix4 rt;

	float l, r, b, t, n,f;
	float aspectRatio;

	FishTank(float l, float r, float b, float t, float n, float f);
	FishTank(float realW, float realH, float n = 0.01, float f = 200.0f );
	FishTank();

	void setInitialFrustum(float l, float r, float b, float t, float n, float f);
	void setInitialFrustum(float realW, float realH, float n = 0.01, float f = 200.0f );

	void setFrustum( Vector3 eyepos );
	void setView( Vector3 eyepos );

	void setAll( Vector3 eyepos );


	~FishTank(void);
};


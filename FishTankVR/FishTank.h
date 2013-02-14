#pragma once

#include "Matrices.h"
#include "Vectors.h"
#include "cv/opencv2/core/core.hpp"

using namespace cv;

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
	void setFrustum( Vec3f eyep );
	void setView( Vec3f eyep );


	~FishTank(void);
};


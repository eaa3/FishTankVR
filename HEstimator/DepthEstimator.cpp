#include "DepthEstimator.h"
#include <cmath>


float depthEstimator(float wResolution, float bbw, float fovw, float realW)
{
	//RadiansPerPixels
	float rpp = (fovw/(2.0f*wResolution));

	float alpha = (bbw/2)*rpp;

	float h = realW/(2*tanf(alpha));

	return h;
}


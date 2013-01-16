#pragma once

#include "Predator.h"
#include "FaceDetector.h"
#include <string>
#include <opencv2/core/core.hpp>

using std::string;
using namespace tld;

float remap(float a, float xi, float yi, float xf, float yf);


class HeadTracker
{

private:
	Predator* p;
	FaceDetector* fd;
	bool inited;
	BoundingBox originalBB;

public:
	HeadTracker(string tld_config = TLD_CONFIG_FILE, string face_detector_config = FACE_DETECTOR_CONFIG_FILE);
	~HeadTracker(void);


	bool init(Mat& frame);
	bool isInited();

	void reset();

	BoundingBox track(Mat& frame);

	Vec3f estimateSpacePosition(const BoundingBox& bb, float videoW, float realVideoW, float videoH, float realVideoH, float (*zestimator)(const BoundingBox&));



};


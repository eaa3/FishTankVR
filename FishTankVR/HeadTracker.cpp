#include "HeadTracker.h"


float remap(float a, float xi, float yi, float xf, float yf)
{
	float yp = yf + ((a - xf)/(xf-xi))*(yf - yi);

	return yp;
}

HeadTracker::HeadTracker(string tld_config, string face_detector_config )
{
	this->p = new Predator(tld_config);
	this->fd = new FaceDetector(face_detector_config);
	this->inited = false;

}


HeadTracker::~HeadTracker(void)
{
	delete this->p;
	delete this->fd;
}


bool HeadTracker::init(Mat& frame)
{
	bool ready = this->inited? true : false;
	BoundingBox selectedBB;

	if( this->fd->isOk && !ready)
	{

		this->fd->detect(frame);

		if( this->fd->detectionResult.size() > 0 )
		{

			selectedBB = BoundingBox(this->fd->detectionResult[0]);
			this->originalBB = selectedBB;

			this->p->reset();
			this->p->selectObject(frame, selectedBB);

			ready = true;
			this->inited = true;

		}

	}


	return ready;

}

bool HeadTracker::isInited()
{
	return this->inited;
}

Vector3 HeadTracker::estimateSpacePosition(const BoundingBox& bb, float videoW, float realVideoW, float videoH, float realVideoH, float (*zestimator)(const BoundingBox&))
{
	Vector3 eyepos(0,0,0);

	float x = (bb.x+bb.w)/2;
	float y = (bb.y+bb.y)/2;


	eyepos[0] = remap(x, -videoW/2, -realVideoW/2, videoW/2, realVideoW/2);
	eyepos[1] = remap(y, -videoH/2, -realVideoH/2, videoH/2, realVideoH/2);

	eyepos[2] = zestimator(bb);


	return eyepos;
}

void HeadTracker::reset()
{
	this->p->reset();
	this->inited = false;

}

BoundingBox HeadTracker::track(Mat& frame)
{
	BoundingBox trackedBB;


	if( this->inited )
	{
		this->p->processFrame(frame);

		if( !this->p->currBB.valid )
		{
			this->fd->detect(frame);

			if( this->fd->detectionResult.size() )
			{
				this->p->currBB = BoundingBox(this->fd->detectionResult[0]);
				this->p->currBB.valid = true;
			}
		}


		trackedBB = p->currBB;
	}

	return trackedBB;
}

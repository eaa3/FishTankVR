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

Vec2f HeadTracker::get2DEyePixelSpacePosition(const BoundingBox& bb, float x_rate, float y_rate)
{

	Vec2f eyepos(0,0);

	float x =  bb.x + bb.w*x_rate;
	float y =  bb.y + bb.h*y_rate;

	eyepos[0] = x;
	eyepos[1] = y;

	return eyepos;

}

Vec3f HeadTracker::estimateSpacePosition(const BoundingBox& bb, float videoW, float realVideoW, float videoH, float realVideoH, float (*zestimator)(const BoundingBox&), float x_rate, float y_rate)
{
	Vec3f eyepos(0,0,0);

	Vec2f eyepos2DPixelSpace = this->get2DEyePixelSpacePosition(bb);


	eyepos[0] = -remap(eyepos2DPixelSpace[0] - videoW/2, -videoW/2, -realVideoW/2, videoW/2, realVideoW/2);
	eyepos[1] = -remap(eyepos2DPixelSpace[1] - videoH/2, -videoH/2, -realVideoH/2, videoH/2, realVideoH/2);

	eyepos[2] = zestimator(bb);


	return eyepos;
}

void HeadTracker::reset()
{
	this->p->reset();
	this->inited = false;

}

BoundingBox HeadTracker::track(Mat& frame, bool useOld)
{
	BoundingBox trackedBB;

	if( useOld && this->inited )
	{
		trackedBB = this->p->currBB;

		return trackedBB;
	}


	if( this->inited )
	{
		this->p->processFrame(frame);

		if( !this->p->currBB.valid )
		{
			this->fd->detect(frame);

			if( this->fd->detectionResult.size() )
			{
				trackedBB = BoundingBox(this->fd->detectionResult[0]);

				float nnOpinion = p->detector->nnClassifier->classify(trackedBB.extractNormalizedPatch(frame));
				float ffOpinion = p->ffClassifier->classify(p->integralImg, trackedBB);

				if( nnOpinion >= 0.25f || ffOpinion > 0.3f )
				{
					
					trackedBB.valid = true;
					p->currBB = trackedBB;
				}
				else
				{
					trackedBB = BoundingBox();
				}
			}
		}
		else
		{
			trackedBB = p->currBB;
		}

	}

	return trackedBB;
}

Vec3f HeadTracker::track(Mat& frame, float videoW, float realVideoW, float videoH, float realVideoH, float (*zestimator)(const BoundingBox&), bool useOld)
{
	BoundingBox bb = this->track(frame, useOld);

	Vec3f position = this->estimateSpacePosition(bb, videoW, realVideoW, videoH, realVideoH, zestimator);

	return position;
}

#include "HeadTracker.h"


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
			originalBB = selectedBB;

			this->p->reset();
			this->p->selectObject(frame, selectedBB);

			ready = true;
			this->inited = true;

		}

	}


	return ready;

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

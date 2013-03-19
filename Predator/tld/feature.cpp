#include "feature.h"


namespace tld {

Feature::Feature()
{
    this->xp = this->yp = this->wp = this->hp = 0;
}

Feature::Feature(float minScale, float maxScale)
{
	float random1 = randomFloat();
	float random2 = randomFloat();

    this->wp = (maxScale - minScale)*random1+ minScale;
    this->hp = (maxScale - minScale)*random2 + minScale;

	float random3 = randomFloat();
	float random4 = randomFloat();
    this->xp = (1.0f - this->wp)*random3;
    this->yp = (1.0f - this->hp)*random4;
}

Feature::~Feature()
{
    //dtor
}


}

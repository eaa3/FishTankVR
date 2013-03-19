#ifndef FEATURE_H
#define FEATURE_H

#ifdef MATHFUNCSDLL_EXPORTS
#define MATHFUNCSDLL_API __declspec(dllexport) 
#else
#define MATHFUNCSDLL_API __declspec(dllimport) 
#endif

#include "includes.h"
#include "boundingbox.h"
#include "tld_util.h"

namespace tld {

class Feature
{
    public:
        float xp, yp, wp, hp;

        MATHFUNCSDLL_API  Feature();
        MATHFUNCSDLL_API  Feature(float minScale, float maxScale);
        MATHFUNCSDLL_API  virtual ~Feature();




        MATHFUNCSDLL_API  virtual int evaluate(Mat& integralImage, BoundingBox patch) = 0;

    protected:
    private:
};

}
#endif // FEATURE_H

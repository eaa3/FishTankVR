#pragma once

#ifdef MATHFUNCSDLL_EXPORTS
#define MATHFUNCSDLL_API __declspec(dllexport) 
#else
#define MATHFUNCSDLL_API __declspec(dllimport) 
#endif

#include "includes.h"
#include "normalizedpatch.h"
//#include "tld_util.h"

namespace tld {

class NormalizedPatch;

class BoundingBox
{
public:
    int x, y, w, h;
    int xf, yf;
    float conf;
    float post;
    bool valid;

    bool detected;

    MATHFUNCSDLL_API BoundingBox(int x = 0, int y = 0, int w = 0, int h = 0, float conf = 0.0f, bool valid = false, bool detected = false, float post = 0.0f);
    MATHFUNCSDLL_API BoundingBox( const BoundingBox& other);
    MATHFUNCSDLL_API BoundingBox( const Rect& other );

    MATHFUNCSDLL_API void setX(int x);
    MATHFUNCSDLL_API void setY(int y);
    MATHFUNCSDLL_API void setXY(int x, int y);

    MATHFUNCSDLL_API void setW(int w);
    MATHFUNCSDLL_API void setH(int h);
    MATHFUNCSDLL_API void setWH(int w, int h);

    MATHFUNCSDLL_API bool isOverlapping(  BoundingBox& other );
    MATHFUNCSDLL_API bool isOverlapping(  BoundingBox& other, float minOverlapArea );
    MATHFUNCSDLL_API bool isInside(  BoundingBox& other );
	MATHFUNCSDLL_API bool isInside( int x, int y);

    MATHFUNCSDLL_API float overlap(  BoundingBox& other );
    MATHFUNCSDLL_API void overlap(  vector<BoundingBox>& others, float* overlaps );
    MATHFUNCSDLL_API void overlap(  vector<BoundingBox*>& others, float* overlaps );

    MATHFUNCSDLL_API int getArea() ;
    MATHFUNCSDLL_API int getArea( Mat& integralImage) ;

    MATHFUNCSDLL_API Mat extractPatch( Mat& image);
    MATHFUNCSDLL_API NormalizedPatch extractNormalizedPatch( Mat& image, int dimension = NORMALIZED_PATCH_DIM);

    MATHFUNCSDLL_API ~BoundingBox();

    MATHFUNCSDLL_API operator Rect();
protected:
private:
};

}


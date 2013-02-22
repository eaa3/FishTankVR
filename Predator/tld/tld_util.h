#pragma once

#ifdef MATHFUNCSDLL_EXPORTS
#define MATHFUNCSDLL_API __declspec(dllexport) 
#else
#define MATHFUNCSDLL_API __declspec(dllimport) 
#endif

#include "includes.h"
#include  "boundingbox.h"

using tld::BoundingBox;

MATHFUNCSDLL_API float randomFloat();
MATHFUNCSDLL_API double randomDouble();
MATHFUNCSDLL_API int randomInt();

MATHFUNCSDLL_API bool gtCompf( float& a,  float& b);
MATHFUNCSDLL_API bool tldSortByOverlapDesc(pair<int,float> bb1 , pair<int,float> bb2);

MATHFUNCSDLL_API Mat get_roi(Mat& src, BoundingBox box, int padding = 0);
MATHFUNCSDLL_API void draw_box(BoundingBox& b, Mat& src, Scalar color);



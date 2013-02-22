#ifndef NORMALIZEDPATCH_H
#define NORMALIZEDPATCH_H

#ifdef MATHFUNCSDLL_EXPORTS
#define MATHFUNCSDLL_API __declspec(dllexport) 
#else
#define MATHFUNCSDLL_API __declspec(dllimport) 
#endif

#include "boundingbox.h"

namespace tld {

class BoundingBox;

class NormalizedPatch
{
    public:

        float values[NORMALIZED_PATCH_DIM*NORMALIZED_PATCH_DIM];
        bool positive;



        MATHFUNCSDLL_API NormalizedPatch( const NormalizedPatch& other);
        MATHFUNCSDLL_API NormalizedPatch( Mat& image,  BoundingBox& bb, bool positive = false);
        MATHFUNCSDLL_API NormalizedPatch();

        MATHFUNCSDLL_API void release();
        MATHFUNCSDLL_API virtual ~NormalizedPatch();

        MATHFUNCSDLL_API float ncc( NormalizedPatch& other);

        static MATHFUNCSDLL_API void extractNormalizedValues( Mat& image,  BoundingBox& bb, float* out_values);


    protected:

};

}

#endif // NORMALIZEDPATCH_H

#pragma once

#ifdef MATHFUNCSDLL_EXPORTS
#define MATHFUNCSDLL_API __declspec(dllexport) 
#else
#define MATHFUNCSDLL_API __declspec(dllimport) 
#endif

#include "includes.h"

#include "normalizedpatch.h"


namespace tld {

class NNClassifier
{
    protected:
    private:


        vector<NormalizedPatch> truePositives;
        vector<NormalizedPatch> falsePositives;


    public:

        float thetaTP, thetaFP;

        MATHFUNCSDLL_API NNClassifier(float thetaTP = THETA_TP, float thetaFP = THETA_FP);
        MATHFUNCSDLL_API virtual ~NNClassifier();


        MATHFUNCSDLL_API float classify( NormalizedPatch& patch);


        MATHFUNCSDLL_API void learn( vector<NormalizedPatch>& patches);

        MATHFUNCSDLL_API bool filter( NormalizedPatch& patch);


        MATHFUNCSDLL_API void release();

};

}


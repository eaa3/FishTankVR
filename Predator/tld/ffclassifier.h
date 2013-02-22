#ifndef FFCLASSIFIER_H
#define FFCLASSIFIER_H

#ifdef MATHFUNCSDLL_EXPORTS
#define MATHFUNCSDLL_API __declspec(dllexport) 
#else
#define MATHFUNCSDLL_API __declspec(dllimport) 
#endif

#include "fern.h"


namespace tld {

const float DEFAULT_THRESHOLD = 0.5f;

//Fern Forest Classifier
class FFClassifier
{
    public:

        vector<Fern*> ferns;
        float threshold;
        int nFerns, nNodes;
        float minScale, maxScale;


        MATHFUNCSDLL_API FFClassifier(int nFerns, int nNodes, float minScale, float maxScale, float threshold = DEFAULT_THRESHOLD);
        MATHFUNCSDLL_API virtual ~FFClassifier();


        MATHFUNCSDLL_API void train( Mat& integralImage, BoundingBox& patch, int positive);

        MATHFUNCSDLL_API float classify( Mat& integralImage,  BoundingBox& patch);

        MATHFUNCSDLL_API bool filter(Mat& integralImage,  BoundingBox& patch);

        MATHFUNCSDLL_API void init(int nFerns = 10, int nNodes = 5, float minScale = 0.1f, float maxScale = 0.5f);
        MATHFUNCSDLL_API void release();

    protected:
    private:
};


}
#endif // FFCLASSIFIER_H

#ifndef DETECTOR_H
#define DETECTOR_H

#ifdef MATHFUNCSDLL_EXPORTS
#define MATHFUNCSDLL_API __declspec(dllexport) 
#else
#define MATHFUNCSDLL_API __declspec(dllimport) 
#endif

#include <vector>
#include "includes.h"
#include "boundingbox.h"
#include "ffclassifier.h"
#include "nnclassifier.h"
#include "clusterer.h"

using namespace std;


namespace tld {


class Detector
{
    public:

        FFClassifier* ffClassifier;
        NNClassifier* nnClassifier;
        Clusterer* clusterer;

        int frameW, frameH;
        float objW, objH;
        vector<BoundingBox> windows;

        float minScale, maxScale, baseScale;
        float shift;
        int min_bb;


        bool initialized;

        MATHFUNCSDLL_API void initWindows();

        MATHFUNCSDLL_API Detector(int frameW, int frameH, FFClassifier* ffClassifier, NNClassifier* nnClassifier = NULL);

        MATHFUNCSDLL_API Detector(int frameW, int frameH, FFClassifier* ffClassifier, NNClassifier* nnClassifier = NULL, float minScale = MIN_WINDOW_SCALE, float maxScale = MAX_WINDOW_SCALE, float baseScale = BASE_WINDOW_SCALE,  float shift = SHIFT, int min_bb = MIN_BB, float cutoff = CUTOFF);
        MATHFUNCSDLL_API virtual ~Detector();

        MATHFUNCSDLL_API void init();
        MATHFUNCSDLL_API void release();


        MATHFUNCSDLL_API BoundingBox detect(Mat& img, Mat& integralImage);
    protected:
    private:
};

}

#endif // DETECTOR_H

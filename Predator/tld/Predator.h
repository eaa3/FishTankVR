#ifndef PREDATOR_H
#define PREDATOR_H

#ifdef MATHFUNCSDLL_EXPORTS
#define MATHFUNCSDLL_API __declspec(dllexport) 
#else
#define MATHFUNCSDLL_API __declspec(dllimport) 
#endif

#include "includes.h"
#include "MedianFlowTracker.h"
#include "detector.h"
#include "tld_util.h"
#include "params.h"


namespace tld
{

class Predator
{

protected:

    Params* params;
public:

    MedianFlowTracker* tracker;
    FFClassifier* ffClassifier;
    NNClassifier* nnClassifier;
    Detector* detector;

    Mat currImg;
    Mat prevImg;
    Mat integralImg;

    BoundingBox prevBB;
    BoundingBox currBB;

    BoundingBox detectedBB;
    BoundingBox trackedBB;

    MATHFUNCSDLL_API void storeData(); //done
    MATHFUNCSDLL_API void fuseHypotheses();
    MATHFUNCSDLL_API void learn();
    MATHFUNCSDLL_API void initialLearning();


    bool initialized;

    int frameW, frameH;

public:

    bool trackerEnabled;
    bool detectorEnabled;
    bool learningEnabled;

    vector<BoundingBox> detectionHistory;



    MATHFUNCSDLL_API Predator(string paramsFile); //done
    MATHFUNCSDLL_API Predator(Params* params); //done
    MATHFUNCSDLL_API ~Predator(); //done

    MATHFUNCSDLL_API void init(); //done
    MATHFUNCSDLL_API void release(); // done
    MATHFUNCSDLL_API void reset(); // done

    MATHFUNCSDLL_API void selectObject(Mat& img, BoundingBox& bb); //done
    MATHFUNCSDLL_API void processFrame(Mat& img); // done




};

}

#endif // PREDATOR_H

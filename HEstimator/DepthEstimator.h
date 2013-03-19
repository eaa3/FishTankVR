#pragma once

#ifdef MATHFUNCSDLL_EXPORTS
#define MATHFUNCSDLL_API __declspec(dllexport) 
#else
#define MATHFUNCSDLL_API __declspec(dllimport) 
#endif

//wResolution é a largura da tela em pixels
//bbw é a largura do boundingbox em pixels
//fovw é o field of view horizontal da camera, em radianos
//realW é a largura real do objeto contido no boundingbox em unidades espaciais (metros, milímetros, cm, etc...)
MATHFUNCSDLL_API float depthEstimator(float wResolution, float bbw, float fovw, float realW);
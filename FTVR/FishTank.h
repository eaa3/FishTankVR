#pragma once


#ifdef MATHFUNCSDLL_EXPORTS
#define MATHFUNCSDLL_API __declspec(dllexport) 
#else
#define MATHFUNCSDLL_API __declspec(dllimport) 
#endif


#include "Matrices.h"
#include "Vectors.h"



class FishTank
{
public:

	Matrix4 proj;
	Matrix4 rt;

	float l, r, b, t, n,f;
	float aspectRatio;

	MATHFUNCSDLL_API FishTank(float l, float r, float b, float t, float n, float f);
	MATHFUNCSDLL_API FishTank(float realW, float realH, float n = 0.01, float f = 200.0f );
	MATHFUNCSDLL_API FishTank();

	MATHFUNCSDLL_API void setInitialFrustum(float l, float r, float b, float t, float n, float f);
	MATHFUNCSDLL_API void setInitialFrustum(float realW, float realH, float n = 0.01, float f = 200.0f );

	MATHFUNCSDLL_API void setFrustum( Vector3 eyepos );
	MATHFUNCSDLL_API void setView( Vector3 eyepos );

	MATHFUNCSDLL_API void setAll( Vector3 eyepos );


	MATHFUNCSDLL_API ~FishTank(void);
};


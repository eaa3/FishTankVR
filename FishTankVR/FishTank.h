#pragma once
class FishTank
{
public:

	float proj[16];
	float rt[16];

	float l, r, b, t, n, f;

	FishTank(float l, float r, float b, float t, float n, float f);
	~FishTank(void);
};


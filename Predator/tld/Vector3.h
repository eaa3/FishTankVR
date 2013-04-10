#ifndef Vector3__H
#define Vector3__H

#include <cmath>

#define PI 3.14159265359f


#ifdef MATHFUNCSDLL_EXPORTS
#define MATHFUNCSDLL_API __declspec(dllexport) 
#else
#define MATHFUNCSDLL_API __declspec(dllimport) 
#endif

float toRad(float angle);
float toDegree(float rad);

class Vector3_
{
    public:

        static const Vector3_ ZERO;

		//Rotation type
        static const int R_X;
        static const int R_Y;
        static const int R_Z;

        MATHFUNCSDLL_API Vector3_(float x, float y, float z);
        //Vector3_(Vector3_& other);
        MATHFUNCSDLL_API Vector3_();
        MATHFUNCSDLL_API ~Vector3_();

        MATHFUNCSDLL_API operator float*();

        MATHFUNCSDLL_API float& operator[](int index);

        MATHFUNCSDLL_API void operator=(Vector3_ other);
        MATHFUNCSDLL_API float operator*(Vector3_ other);
        MATHFUNCSDLL_API Vector3_ operator*(float k);
        MATHFUNCSDLL_API Vector3_ operator/(float k);
        MATHFUNCSDLL_API Vector3_ operator+(Vector3_ other);
        MATHFUNCSDLL_API Vector3_ operator-(Vector3_ other);
        MATHFUNCSDLL_API void operator*=(float k);
        MATHFUNCSDLL_API void operator/=(float k) ;
        MATHFUNCSDLL_API void operator+=(Vector3_ other);
        MATHFUNCSDLL_API void operator-=(Vector3_ other);




        MATHFUNCSDLL_API float norm();

        MATHFUNCSDLL_API void normalize();

        MATHFUNCSDLL_API float angleBetween(Vector3_ other) ;

        MATHFUNCSDLL_API Vector3_ cross(Vector3_ other);

        MATHFUNCSDLL_API void rotate(float angle, int type);
        MATHFUNCSDLL_API void rotate(float angle, Vector3_ u);


        MATHFUNCSDLL_API void transform(Vector3_ vi, Vector3_ vj, Vector3_ vk);

        MATHFUNCSDLL_API Vector3_ proj(Vector3_ other);



    protected:
    private:

        float coord[3];


};

#endif // Vector3__H

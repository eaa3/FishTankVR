#include "Vector3.h"


float toRad(float angle){
    return (angle*PI)/180;
}

float toDegree(float rad)
{
	return (rad*180.0f)/PI;
}


const int Vector3_::R_X = 0;
const int Vector3_::R_Y = 1;
const int Vector3_::R_Z = 2;
const Vector3_ Vector3_::ZERO(0,0,0);

/*
Vector3_::Vector3_(Vector3_& other)
{
    for(int i = 0; i < 3; i++) this->coord[i] = other[i];
}
*/

Vector3_::Vector3_(float x, float y, float z)
{
    this->coord[0] = x;
    this->coord[1] = y;
    this->coord[2] = z;
}

Vector3_::Vector3_()
{
    this->coord[0] = this->coord[1] = this->coord[2] = 0;
}

Vector3_::~Vector3_()
{
    //dtor
}


Vector3_::operator float*()
{
    return this->coord;
}

float& Vector3_::operator[](int index)
{
    return this->coord[index];
}

float Vector3_::operator*(Vector3_ other)
{
    float r = 0.0f;

    for(int i = 0; i < 3; i++) r += this->coord[i]*other[i];

    return r;
}
Vector3_ Vector3_::operator*(float k)
{
    Vector3_ r;

    for(int i = 0; i < 3; i++) r[i] = this->coord[i]*k;

    return r;
}
Vector3_ Vector3_::operator/(float k)
{
    Vector3_ r;

    for(int i = 0; i < 3; i++) r[i] = this->coord[i]/k;

    return r;
}
Vector3_ Vector3_::operator+(Vector3_ other)
{
    Vector3_ r;

    for(int i = 0; i < 3; i++) r[i] = this->coord[i] + other[i];

    return r;
}
Vector3_ Vector3_::operator-(Vector3_ other)
{
    Vector3_ r;
    for(int i = 0; i < 3; i++) r[i] = this->coord[i] - other[i];

    return r;
}
void Vector3_::operator=(Vector3_ other)
{
    for(int i = 0; i < 3; i++) this->coord[i] = other[i];

}
void Vector3_::operator*=(float k)
{
    for(int i = 0; i < 3; i++) this->coord[i] = this->coord[i]*k;
}
void Vector3_::operator/=(float k)
{
    for(int i = 0; i < 3; i++) this->coord[i] = this->coord[i]/k;
}
void Vector3_::operator+=(Vector3_ other)
{
    for(int i = 0; i < 3; i++) this->coord[i] = this->coord[i] + other[i];
}
void Vector3_::operator-=(Vector3_ other)
{
    for(int i = 0; i < 3; i++) this->coord[i] = this->coord[i] - other[i];

}

float Vector3_::norm()
{
    return (float)sqrtf((*this)*(*this));
}

void Vector3_::normalize()
{
    (*this) /= this->norm();
}

float Vector3_::angleBetween(Vector3_ other)
{
    return ((*this)*other)/(this->norm()*other.norm());
}

Vector3_ Vector3_::cross(Vector3_ other)
{
    Vector3_ r;

    r[0] = this->coord[1]*other[2] - this->coord[2]*other[1];
    r[1] = this->coord[2]*other[0] - this->coord[0]*other[2];
    r[2] = this->coord[0]*other[1] - this->coord[1]*other[0];

    return r;

}

void Vector3_::rotate(float angle, int type)
{
    angle = toRad(angle);

    float x,y,z;

    x = this->coord[0];
    y = this->coord[1];
    z = this->coord[2];

    if( type == Vector3_::R_X )
    {
        this->coord[1] = y*cosf(angle) - z*sinf(angle);
        this->coord[2] = y*sinf(angle) + z*cosf(angle);
    }
    else if( type == Vector3_::R_Y )
    {
        this->coord[0] = x*cosf(angle) + z*sinf(angle);
        this->coord[2] = -x*sinf(angle) + z*cosf(angle);
    }
    else if( type == Vector3_::R_Z )
    {
        this->coord[0] = x*cosf(angle) - y*sinf(angle);
        this->coord[1] = x*sinf(angle) + y*cosf(angle);
    }
}

void Vector3_::rotate(float angle, Vector3_ u)
{
    u.normalize();
    angle = toRad(angle);

    Vector3_ r = (*this);

    float cosTeta = cosf(angle);
    float sinTeta = sinf(angle);
    float oneMinusCosTeta = 1.0f - cosTeta;

    this->coord[0] = r[0]*(cosTeta + u[0]*u[0]*oneMinusCosTeta) + r[1]*(u[0]*u[1]*oneMinusCosTeta - u[2]*sinTeta) + r[2]*(u[0]*u[2]*oneMinusCosTeta + u[1]*sinTeta);
    this->coord[1] = r[0]*(u[1]*u[0]*oneMinusCosTeta + u[2]*sinTeta) + r[1]*(cosTeta + u[1]*u[1]*oneMinusCosTeta) + r[2]*(u[1]*u[2]*oneMinusCosTeta - u[0]*sinTeta);
    this->coord[2] = r[0]*(u[2]*u[0]*oneMinusCosTeta - u[1]*sinTeta) + r[1]*(u[2]*u[1]*oneMinusCosTeta + u[0]*sinTeta) + r[2]*(cosTeta + u[2]*u[2]*oneMinusCosTeta);
}

void Vector3_::transform(Vector3_ vi, Vector3_ vj, Vector3_ vk)
{
    float x,y,z;

    x = this->coord[0];
    y = this->coord[1];
    z = this->coord[2];

    for(int i = 0; i < 3; i++)
    {
        this->coord[i] = x*vi[i] + y*vj[i] + z*vk[i];
    }
}

Vector3_ Vector3_::proj(Vector3_ other)
{
    Vector3_ r;

    r = other*(((*this)*other)/(other*other));

    return r;
}

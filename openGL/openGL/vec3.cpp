#include "stdafx.h"
#include "vec3.h"
#include <math.h>

double vec3::length()
{
	return sqrt(x*x + y*y + z*z);
}
void vec3::normalize()
{
	double d = length();
	if (d != 0.0)
	{
		x /= d;
		y /= d;
		z /= d;
	}
}
double vec3::distance(vec3 v, vec3 w)
{
	vec3 dv = v - w;
	return dv.length();
}
double vec3::dot(vec3 v, vec3 w)
{
	return (v.x * w.x + v.y * w.y + v.z * w.z);
}
vec3 vec3::cross(vec3 v, vec3 w)
{
	return vec3(v.y * w.z - v.z * w.y,
		v.z * w.x - v.x * w.z,
		v.x * w.y - w.y * w.x);
}
double vec3::angle(vec3 v, vec3 w)
{
	double arg = dot(v, w) / (v.length() * w.length());
	if (arg > 1.0) arg = 1.0;
	if (arg < -1.0) arg = -1.0;
	return acos(arg);
}


vec3::~vec3()
{
}

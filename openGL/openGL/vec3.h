#pragma once
class vec3
{
public:
	double x;
	double y;
	double z;

	vec3() { x = 0.0; y = 0.0; z = 0.0; };
	vec3(double xc, double yc, double zc) { x = xc; y = yc; z = zc; }

	vec3& operator= (const vec3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}
	vec3 operator+ (const vec3& v)
	{
		return vec3(x + v.x, y + v.y, z + v.z);
	}
	vec3 operator- (const vec3& v)
	{
		return vec3(x - v.x, y - v.y, z - v.z);
	}
	vec3 operator* (const double val)
	{
		return vec3(x * val, y * val, z * val);
	}
	double length();
	void normalize();

	static double distance(vec3 v, vec3 w);
	static double dot(vec3 v, vec3 w);
	static vec3 cross(vec3 v, vec3 w);
	static double angle(vec3 v, vec3 w);
	~vec3();
};


#include "Vector3.h"

Vector3::Vector3() {}

Vector3::Vector3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}
Vector3 Vector3::add(Vector3 v1, Vector3 v2)
{
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}
#pragma once

#include "Vector3.h"
#include <math.h>

class Quaternion
{
public:
	Quaternion();
	Quaternion(float _w, float _x, float _y, float _z);
	static Vector3 quat2Euler(Quaternion q);
	static Quaternion euler2Quat(Vector3 vector);
	static Vector3 X(Quaternion q1, Vector3 v);
	float w = 0;
	float x = 0;
	float y = 0;
	float z = 0;
};


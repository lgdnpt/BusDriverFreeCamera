#pragma once
class Vector3
{
public:
	Vector3();
	Vector3(float _x, float _y, float _z);
	static Vector3 add(Vector3 v1, Vector3 v2);
	float x = 0;
	float y = 0;
	float z = 0;
};


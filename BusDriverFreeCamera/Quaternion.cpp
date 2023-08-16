#include "Quaternion.h"

Quaternion::Quaternion(float _w, float _x, float _y, float _z)
{
	w = _w;
	x = _x;
	y = _y;
	z = _z;
}
Quaternion::Quaternion() {}

Vector3 Quaternion::quat2Euler(Quaternion q)
{
	//quaternion use w,x,y,z sequence
	//               0 1 2 3
	Vector3 result;
	//pitch
	float vz = asin(-2 * (q.w * q.y + q.x * q.z)) * 57.3f;
	//yaw
	float vy = atan2(2 * (q.x * q.y - q.w * q.z), q.w * q.w + q.x * q.x - q.y * q.y - q.z * q.z) * 57.3f;
	//roll
	float vx = -atan2(2 * (q.y * q.z - q.w * q.x), q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z) * 57.3f;
	result.x = vx;
	result.z = vy;
	result.y = vz;
	return result;
}

Quaternion Quaternion::euler2Quat(Vector3 vector)
{
	Vector3 v;
	v.x = vector.x / 57.3f;
	v.y = vector.y / 57.3f;
	v.z = vector.z / 57.3f;
	Quaternion result;
	float qw = cos(v.z / 2) * cos(v.y / 2) * cos(v.x / 2) - sin(v.z / 2) * sin(v.y / 2) * sin(v.x / 2);
	float qx = cos(v.z / 2) * cos(v.y / 2) * sin(v.x / 2) + sin(v.z / 2) * sin(v.y / 2) * cos(v.x / 2);
	float qy = cos(v.z / 2) * sin(v.y / 2) * cos(v.x / 2) - sin(v.z / 2) * cos(v.y / 2) * sin(v.x / 2);
	float qz = sin(v.z / 2) * cos(v.y / 2) * cos(v.x / 2) + cos(v.z / 2) * sin(v.y / 2) * sin(v.x / 2);
	result.w = qw;
	result.x = qx;
	result.y = qy;
	result.z = qz;
	return result;
}

Vector3 Quaternion::X(Quaternion q1, Vector3 v)
{
	Vector3 result;
	Quaternion q2(0, v.x, v.y, v.z);
	result.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	result.y = q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z;
	result.z = q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x;
	return result;
}
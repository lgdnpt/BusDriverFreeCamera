#include<stdio.h>
#include"MemoryEdit.h"


int main()
{
	if (!FindWindow(L"prism3d", NULL)) return -1;
	MemoryEdit memEdit;
	DWORD baseAddress = 0x70B3E8;
	DWORD posZaddress = memEdit.getPointer(baseAddress, 0xC, 0x8, 0x20, 0x10, 0x8, 0xB8);
	posZaddress = posZaddress + 0xA0;
	DWORD posYaddress = posZaddress - 0x4;
	DWORD posXaddress = posZaddress - 0x8;
	Vector3 vehiclePos = memEdit.getVehiclePos(posXaddress, posYaddress, posZaddress);

	baseAddress = 0x7103A0;
	DWORD rotW = memEdit.getPointer(baseAddress, 0x138, 0xD8, 0x90, 0x88, 0xB8, 0x10);
	rotW = rotW + 0x24;
	DWORD rotX = rotW + 0x4;
	DWORD rotY = rotW + 0x8;
	DWORD rotZ = rotX + 0x8;
	DWORD camPosZ = rotW - 0x4;
	DWORD camPosY = camPosZ - 0x4;
	DWORD camPosX = camPosY - 0x4;
	memEdit.cutOffCameraLink();

	float rotateYAxis = 0;
	int z = 0;
	int speed = 10;
	Vector3 v;
	Vector3 camerapos;
	Quaternion q;
	while (true)
	{
		scanf_s("%d", &z);
		if (z == 4)
			rotateYAxis -= speed;
		if (z == 6)
			rotateYAxis += speed;
		if (rotateYAxis > 360)
			rotateYAxis -= 360;
		if (rotateYAxis >= 180)
			rotateYAxis -= 360;
		if (rotateYAxis <= -180)
			rotateYAxis += 360;
		float x = sin(rotateYAxis/57.3f) * 10;
		float y = cos(rotateYAxis/57.3f) * 10;
		v.x = x;
		v.y = y;
		q = Quaternion::euler2Quat(Vector3(0, rotateYAxis, 0));
		camerapos.x = v.x + vehiclePos.x;
		camerapos.z = v.y + vehiclePos.z;
		camerapos.y = vehiclePos.y + 3.0f;
		printf("%f,%f,%f\n", camerapos.x, camerapos.y, camerapos.z);
		memEdit.writeCameraTransform(camPosX, camPosY,camPosZ,rotW,rotX,rotY,rotZ,camerapos,q);
	}
}
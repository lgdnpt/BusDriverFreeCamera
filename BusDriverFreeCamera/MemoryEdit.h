#pragma once
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <math.h>
#include "Vector3.h"
#include "Quaternion.h"

class MemoryEdit
{
public:
	HANDLE hProcess = NULL;
	DWORD gamePID = 0;
	HWND game = NULL;
	SIZE_T nSize = 0;
	MemoryEdit();
	DWORD getPointer(DWORD &baseAddress, int offset1 = 0, int offset2 = 0, int offset3 = 0, int offset4 = 0, int offset5 = 0, int offset6 = 0, int offset7 = 0);
	float readMemory(DWORD &address);
	void writeMemory(DWORD &address, float num);
	Vector3 getVehiclePos(DWORD& posXaddress, DWORD& posYaddress, DWORD& posZAddress);
	void writeCameraTransform(DWORD& px, DWORD& py, DWORD& pz, DWORD& rw, DWORD& rx, DWORD& ry, DWORD& rz, Vector3 &pos, Quaternion &rot);
	void cutOffCameraLink();
	void fixCameraLink();
private:
	void print(DWORD &dword);
};


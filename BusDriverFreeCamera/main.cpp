#include<stdio.h>
#include <iostream>
#include <Windows.h>
#include <TCHAR.h>
#include <thread>

#include"MemoryEdit.h"

HHOOK g_hHook;

Vector3 vehiclePos;
float rotateYAxis = 0;
Vector3 camerapos;
Quaternion q;
float distance = 10.0f;
float height = 2.0f;
float x, y;
DWORD camPosX, camPosY, camPosZ, rotW, rotX, rotY, rotZ, posXaddress, posYaddress, posZaddress;
MemoryEdit memEdit;

bool isOn = true;

void limitAngle(float& num)
{
	if (num > 360)
		num -= 360;
	if (num >= 180)
		num -= 360;
	if (num <= -180)
		num += 360;
}

LRESULT CALLBACK kbdProc(int code, WPARAM wParam, LPARAM lParam)
{
	if (code != HC_ACTION) 
		return CallNextHookEx(g_hHook, code, wParam, lParam);
	PKBDLLHOOKSTRUCT param = (PKBDLLHOOKSTRUCT)lParam;

	if (param->vkCode == 0x4A)
		rotateYAxis--;
	if (param->vkCode == 0x4C)
		rotateYAxis++;

	if (param->vkCode == 0x55)
		distance+=0.1f;
	if (param->vkCode == 0x4F)
		distance-=0.1f;

	if (param->vkCode == 0x49)
		height+=0.1f;
	if (param->vkCode == 0x4B)
		height-=0.1f;

	if (param->vkCode == 0x54 && isOn)
	{
		memEdit.fixCameraLink();
		isOn = false;
	}
	else if (param->vkCode == 0x59 && !isOn)
	{
		memEdit.cutOffCameraLink();
		isOn = true;
	}
	return CallNextHookEx(g_hHook, code, wParam, lParam);
}


void Update()
{
	while (true)
	{
		Sleep(16);
		if (isOn)
		{
			vehiclePos = memEdit.getVehiclePos(posXaddress, posYaddress, posZaddress);

			limitAngle(rotateYAxis);
			x = sin(rotateYAxis / 57.3f) * distance;
			y = cos(rotateYAxis / 57.3f) * distance;
			q = Quaternion::euler2Quat(Vector3(0, rotateYAxis, 0));
			camerapos.x = x + vehiclePos.x;
			camerapos.z = y + vehiclePos.z;
			camerapos.y = height + vehiclePos.y;
			memEdit.writeCameraTransform(camPosX, camPosY, camPosZ, rotW, rotX, rotY, rotZ, camerapos, q);
		}
	}
}

int main()
{
	if (!FindWindow(L"prism3d", NULL)) return -1;
	printf("ooooo         ooooooo8 ooooooooo  oooo   oooo oooooooooo  ooooooooooo \n");
	printf(" 888        o888    88  888    88o 8888o  88   888    888 88  888  88 \n");
	printf(" 888        888    oooo 888    888 88 888o88   888oooo88      888     \n");
	printf(" 888      o 888o    88  888    888 88   8888   888            888     \n");
	printf("o888ooooo88  888ooo888 o888ooo88  o88o    88  o888o          o888o    \n");
	printf("                                       巴士驾驶员自由观察视角插件V0.1.2\n");
	printf("                                                           作者: lgdnpt \n");
	printf("                                                          build20230817 \n");
	printf("                                                        QQ群: 364994963\n");
	printf("\n\n\n\n\n");
	printf("使用方法：在游戏线路载入完成以后启动本程序，J、L键旋转视角，I、K键改变距离，\nU、O键改变高度，T键关闭功能，Y键开启功能");


	DWORD baseAddress = 0x70B3E8;
	posZaddress = memEdit.getPointer(baseAddress, 0xC, 0x8, 0x20, 0x10, 0x8, 0xB8);
	posZaddress = posZaddress + 0xA0;
	posYaddress = posZaddress - 0x4;
	posXaddress = posZaddress - 0x8;
	vehiclePos = memEdit.getVehiclePos(posXaddress, posYaddress, posZaddress);

	baseAddress = 0x704C00;
	rotW = memEdit.getPointer(baseAddress, 0x14, 0x1B8, 0xA4, 0x8, 0x128);
	//printf("%x", rotW);
	rotW = rotW + 0x2C;
	rotX = rotW + 0x4;
	rotY = rotW + 0x8;
	rotZ = rotX + 0x8;
	camPosZ = rotW - 0x4;
	camPosY = camPosZ - 0x4;
	camPosX = camPosY - 0x4;
	memEdit.cutOffCameraLink();

	std::thread updateCamera(Update);
	updateCamera.detach();

	g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, kbdProc, GetModuleHandle(NULL), NULL);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

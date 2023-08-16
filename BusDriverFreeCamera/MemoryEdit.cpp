#include "MemoryEdit.h"

MemoryEdit::MemoryEdit()
{
	game = FindWindow(L"prism3d", NULL);
	if (game == NULL)
		return;
	GetWindowThreadProcessId(game, &gamePID);
	if (gamePID == 0)
		return;
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, gamePID);
	if (hProcess == NULL)
		return;
}
DWORD MemoryEdit::getPointer(DWORD &baseAddress, int offset1, int offset2, int offset3, int offset4, int offset5, int offset6, int offset7)
{
	DWORD temp1=0;
	DWORD temp2=0;
	print(baseAddress);
	ReadProcessMemory(hProcess, (void*)baseAddress, &temp1, sizeof(DWORD), &nSize);
	print(temp1);
	if (offset1 != 0)
		ReadProcessMemory(hProcess, (void*)(temp1 + offset1), &temp2, sizeof(DWORD), &nSize);
	else
		return temp1;
	print(temp2);
	if (offset2 != 0)
		ReadProcessMemory(hProcess, (void*)(temp2 + offset2), &temp1, sizeof(DWORD), &nSize);
	else
		return temp2;
	print(temp1);
	if (offset3 != 0)
		ReadProcessMemory(hProcess, (void*)(temp1 + offset3), &temp2, sizeof(DWORD), &nSize);
	else
		return temp1;
	print(temp2);
	if (offset4 != 0)
		ReadProcessMemory(hProcess, (void*)(temp2 + offset4), &temp1, sizeof(DWORD), &nSize);
	else
		return temp2;
	print(temp1);
	if (offset5 != 0)
		ReadProcessMemory(hProcess, (void*)(temp1 + offset5), &temp2, sizeof(DWORD), &nSize);
	else
		return temp1;
	print(temp2);
	if (offset6 != 0)
		ReadProcessMemory(hProcess, (void*)(temp2 + offset6), &temp1, sizeof(DWORD), &nSize);
	else
		return temp2;
	print(temp1);
	if (offset7 != 0)
		ReadProcessMemory(hProcess, (void*)(temp1 + offset7), &temp2, sizeof(DWORD), &nSize);
	else
		return temp1;
	return temp2;
}
void MemoryEdit::print(DWORD& dword)
{
	//printf("%x\n", dword);
}
float MemoryEdit::readMemory(DWORD &address)
{
	float result = 0;
	ReadProcessMemory(hProcess, (void*)address, &result, sizeof(DWORD), &nSize);
	return result;
}
void MemoryEdit::writeMemory(DWORD& address, float num)
{
	WriteProcessMemory(hProcess, (void*)address, &num, sizeof(DWORD), &nSize);
}
Vector3 MemoryEdit::getVehiclePos(DWORD& posXaddress, DWORD& posYaddress, DWORD& posZaddress)
{
	Vector3 result;
	result.x = readMemory(posXaddress);
	result.y = readMemory(posYaddress);
	result.z = readMemory(posZaddress);
	return result;
}
void MemoryEdit::writeCameraTransform(DWORD& px, DWORD& py, DWORD& pz, DWORD& rw, DWORD& rx, DWORD& ry, DWORD& rz, Vector3& pos, Quaternion& rot)
{
	writeMemory(px, pos.x);
	writeMemory(py, pos.y);
	writeMemory(pz, pos.z);
	writeMemory(rw, rot.w);
	writeMemory(rx, rot.x);
	writeMemory(ry, rot.y);
	writeMemory(rz, rot.z);
}

void MemoryEdit::cutOffCameraLink()
{
	WriteProcessMemory(hProcess, (void*)0x4DAC2E, "\x90\x90\x90", 3, NULL);
	WriteProcessMemory(hProcess, (void*)0x4DAC31, "\x90\x90\x90", 3, NULL);
	WriteProcessMemory(hProcess, (void*)0x4DAC44, "\x90\x90\x90", 3, NULL);

	WriteProcessMemory(hProcess, (void*)0x4DAC71, "\xD9\x5B\x3C", 3, NULL);
	WriteProcessMemory(hProcess, (void*)0x4DAC7A, "\xD9\x5B\x3C", 3, NULL);
	WriteProcessMemory(hProcess, (void*)0x4DAC81, "\xD9\x5B\x3C", 3, NULL);
	WriteProcessMemory(hProcess, (void*)0x4DAC88, "\xD9\x5B\x3C", 3, NULL);
}

void MemoryEdit::fixCameraLink()
{
	WriteProcessMemory(hProcess, (void*)0x4DAC2E, "\x89\x53\x20", 3, NULL);
	WriteProcessMemory(hProcess, (void*)0x4DAC31, "\x89\x43\x24", 3, NULL);
	WriteProcessMemory(hProcess, (void*)0x4DAC44, "\x89\x4B\x2B", 3, NULL);

	WriteProcessMemory(hProcess, (void*)0x4DAC71, "\xD9\x5B\x2C", 3, NULL);
	WriteProcessMemory(hProcess, (void*)0x4DAC7A, "\xD9\x5B\x30", 3, NULL);
	WriteProcessMemory(hProcess, (void*)0x4DAC81, "\xD9\x5B\x34", 3, NULL);
	WriteProcessMemory(hProcess, (void*)0x4DAC88, "\xD9\x5B\x38", 3, NULL);
}

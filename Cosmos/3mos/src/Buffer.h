#pragma once
#define _WIN32_WINNT 0x500
#include "Windows.h"
class Buffer
{
public:
	Buffer(int pScreenWidth, int pScreenHeight);
	void setHandle();
	void closeHandle();
	void setWindow();
	void edit(int x, int y, wchar_t c);
	void update();
	HANDLE getHandle() { return hConsole; }
	HWND getWnd() { return window; }
	void del();
	wchar_t* get(){return buffer;}
private:
	wchar_t* buffer{};
	int width{};
	int height{};
	HANDLE hConsole{};
	HWND window{};
	DWORD dwBytesWritten{};
};
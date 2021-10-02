#pragma warning( disable : 4996 )
#include "Buffer.h"

Buffer::Buffer(int pScreenWidth, int pScreenHeight)
{
	width = pScreenWidth, height = pScreenHeight;
	buffer = new wchar_t[width * height];
	for (int i = 0; i < width * height; i++) { buffer[i] = ' '; }
	hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	window = GetConsoleWindow();
}
void::Buffer::setHandle()
{
	SetConsoleActiveScreenBuffer(hConsole);
}
void::Buffer::closeHandle()
{
	CloseHandle(hConsole);
}
void::Buffer::setWindow()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	//MoveWindow(window_handle, x, y, width, height, redraw_window);
	MoveWindow(console, r.left, r.top, 660, 280, TRUE); //660 and 280 for  80 x 30?
	CONSOLE_FONT_INFOEX info = { 0 };
	info.cbSize = sizeof(info);
	info.dwFontSize.X = 8;
	info.dwFontSize.Y = 8; // leave X as zero
	info.FontFamily = FF_DONTCARE;
	info.FontWeight = FW_NORMAL;
	wcscpy(info.FaceName, L"Terminal");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
}
void Buffer::edit(int x, int y, wchar_t c)
{
	buffer[y * width + x] = c;
}
void Buffer::update()
{
	WriteConsoleOutputCharacter(hConsole, buffer, width * height, {0,0}, &dwBytesWritten);
}
void Buffer::del()
{
	delete[] buffer;
	buffer = nullptr;
}
#pragma once
#include <Windows.h>
#define MAX_INPUT_KEYBOARD 10
struct KeyboardState
{
	bool up{};
	bool down{};
	bool left{};
	bool right{};
	bool ctrl{};
	bool space{};
	bool enter{};
	bool esc{};
};
class Keyboard
{
public:
	KeyboardState getKeyboardState();
private:
	KeyboardState state;
};
#include "Keyboard.h"

KeyboardState Keyboard::getKeyboardState()
{
	bool input[MAX_INPUT_KEYBOARD];

	for (int i{}; i < MAX_INPUT_KEYBOARD; i++)			//CTRL L   R   S
		input[i] = (0x8000 & GetKeyState((unsigned char)("\x11\x25\x27\x20\x26\x28\x0D\x00\x00"[i]))) != 0;

	state.ctrl = input[0];

	state.left = input[1];

	state.right = input[2];

	state.space = input[3];

	state.up = input[4];

	state.down = input[5];

	state.enter = input[6];

	return state;
}
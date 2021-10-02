#include "GameState.h"
GameState::GameState(int sScreenWidth, int sScreenHeight) : buffer(sScreenWidth, sScreenHeight)
{
	ScreenWidth = sScreenWidth;
	ScreenHeight = sScreenHeight;
}
void::GameState::mm_display()
{
	mm_displayAmbience();
	mm_displayTitle();
	mm_displayModes();
	mm_displayCursor();
	getBuffer().update();
}
void::GameState::mm_displayAmbience()
{
	if (--stateDelay.star == 0)
	{
		ambience.addStar(2);
		ambience.advanceStars(buffer);
		stateDelay.star = STAR_DELAY;
	}
	ambience.deleteStar(27);
	ambience.printStars(buffer);

	//Top HUD line
	for (int i = 0; i < 80; i++)
		buffer.edit(i, 2, L'─');
	//Bottom HUD line
	for (int i = 0; i < 80; i++)
		buffer.edit(i, 27, L'─');
}
void::GameState::mm_displayTitle()
{
	std::wstring top = L"┌─┐┌─┐┌─┐┌┬┐┌─┐┌─┐";
	std::wstring mid = L"│  │ │└─┐││││ │└─┐";
	std::wstring bot = L"└─┘└─┘└─┘┴ ┴└─┘└─┘";

	for (int i = 0; i < top.length(); i++)
		buffer.edit(i + TITLE_X_OFFSET, TITLE_Y_OFFSET, top[i]);
	for (int i = 0; i < mid.length(); i++)
		buffer.edit(i + TITLE_X_OFFSET, 1 + TITLE_Y_OFFSET, mid[i]);
	for (int i = 0; i < bot.length(); i++)
		buffer.edit(i + TITLE_X_OFFSET, 2 + TITLE_Y_OFFSET, bot[i]);
}
void::GameState::mm_displayModes()
{
	std::wstring play{ L"PLAY" };
	std::wstring practice{ L"PRACTICE" };
	std::wstring highScores{ L"HIGH SCORES" };
	std::wstring settings{ L"SETTINGS" };
	std::wstring exit{ L"EXIT" };

	for (int i = 0; i < play.length(); i++)
		buffer.edit(i + PLAY_X_OFFSET, PLAY_Y_OFFSET, play[i]);

	for (int i = 0; i < practice.length(); i++)
		buffer.edit(i + PRACTICE_X_OFFSET, PRACTICE_Y_OFFSET, practice[i]);

	for (int i = 0; i < highScores.length(); i++)
		buffer.edit(i + HIGH_SCORES_X_OFFSET, HIGH_SCORES_Y_OFFSET, highScores[i]);

	for (int i = 0; i < settings.length(); i++)
		buffer.edit(i + SETTINGS_X_OFFSET, SETTINGS_Y_OFFSET, settings[i]);

	for (int i = 0; i < exit.length(); i++)
		buffer.edit(i + EXIT_X_OFFSET, EXIT_Y_OFFSET, exit[i]);
}
void::GameState::mm_displayCursor()
{
	int commandX{};
	int commandY{};
	int cursorX{};
	int cursorY{};

	//destroy prev cursor
	if (selectionChange)
	{
		switch (lastSelection)
		{
		case 0:
		{
			buffer.edit(PLAY_X_OFFSET - 2, PLAY_Y_OFFSET, L' ');
			buffer.edit(PLAY_X_OFFSET - 1, PLAY_Y_OFFSET, L' ');
			buffer.edit(PLAY_X_OFFSET + 4, PLAY_Y_OFFSET, L' ');
			break;
		}
		case 1:
		{
			buffer.edit(PRACTICE_X_OFFSET - 2, PRACTICE_Y_OFFSET, L' ');
			buffer.edit(PRACTICE_X_OFFSET - 1, PRACTICE_Y_OFFSET, L' ');
			buffer.edit(PRACTICE_X_OFFSET + 8, PRACTICE_Y_OFFSET, L' ');
			break;
		}
		case 2:
		{
			buffer.edit(HIGH_SCORES_X_OFFSET - 2, HIGH_SCORES_Y_OFFSET, L' ');
			buffer.edit(HIGH_SCORES_X_OFFSET - 1, HIGH_SCORES_Y_OFFSET, L' ');
			buffer.edit(HIGH_SCORES_X_OFFSET + 11, HIGH_SCORES_Y_OFFSET, L' ');
			break;
		}
		case 3:
		{
			buffer.edit(SETTINGS_X_OFFSET - 2, SETTINGS_Y_OFFSET, L' ');
			buffer.edit(SETTINGS_X_OFFSET - 1, SETTINGS_Y_OFFSET, L' ');
			buffer.edit(SETTINGS_X_OFFSET + 8, SETTINGS_Y_OFFSET, L' ');
			break;
		}
		case 4:
		{
			buffer.edit(EXIT_X_OFFSET - 2, EXIT_Y_OFFSET, L' ');
			buffer.edit(EXIT_X_OFFSET - 1, EXIT_Y_OFFSET, L' ');
			buffer.edit(EXIT_X_OFFSET + 4, EXIT_Y_OFFSET, L' ');
			break;
		}
		default:
			break;
		}
	}
	//find cursor position
	switch (selection)
	{
	case 0:
	{
		commandX = PLAY_X_OFFSET - 2;
		commandY = PLAY_Y_OFFSET;
		cursorX = PLAY_X_OFFSET + 4;
		cursorY = PLAY_Y_OFFSET;
		break;
	}
	case 1:
	{
		commandX = PRACTICE_X_OFFSET - 2;
		commandY = PRACTICE_Y_OFFSET;
		cursorX = PRACTICE_X_OFFSET + 8;
		cursorY = PRACTICE_Y_OFFSET;
		break;
	}
	case 2:
	{
		commandX = HIGH_SCORES_X_OFFSET - 2;
		commandY = HIGH_SCORES_Y_OFFSET;
		cursorX = HIGH_SCORES_X_OFFSET + 11;
		cursorY = HIGH_SCORES_Y_OFFSET;
		break;
	}
	case 3:
	{
		commandX = SETTINGS_X_OFFSET - 2;
		commandY = SETTINGS_Y_OFFSET;
		cursorX = SETTINGS_X_OFFSET + 8;
		cursorY = SETTINGS_Y_OFFSET;
		break;
	}
	case 4:
	{
		commandX = EXIT_X_OFFSET - 2;
		commandY = EXIT_Y_OFFSET;
		cursorX = EXIT_X_OFFSET + 4;
		cursorY = EXIT_Y_OFFSET;
		break;
	}
	default:
		break;
	}

	//display cursor
	buffer.edit(commandX, commandY, L'.');
	buffer.edit(commandX + 1, commandY, L'/');
	if (--stateDelay.cursor == 0)
	{
		cursorVis = cursorVis ? false : true;
		stateDelay.cursor = CURSOR_DELAY;
	}
	if (cursorVis)
		buffer.edit(cursorX, cursorY, L'_');
	else
		buffer.edit(cursorX, cursorY, L' ');
}
int::GameState::mm_getInput(Keyboard keyboard, Gamepad &gamepad)
{
	if (gamepad.Update()) //If controller is connected
	{
		if (--stateDelay.inputDelay <= 0)
			stateDelay.input = false;
		if (!stateDelay.input)
		{
			if ((gamepad.isButtonPressed(XINPUT_GAMEPAD_DPAD_UP) ||
				gamepad.leftStickY > .80f) && selection != 0)
			{
				lastSelection = selection--;
				selectionChange = true;
			}
			else if (( gamepad.isButtonPressed(XINPUT_GAMEPAD_DPAD_DOWN) ||
				gamepad.leftStickY < -.80f) && selection != 4)
			{
				lastSelection = selection++;
				selectionChange = true;
			}
			else if (( gamepad.isButtonPressed(XINPUT_GAMEPAD_DPAD_UP) ||
				gamepad.leftStickY > .80f) && selection == 0)
			{
				lastSelection = selection;
				selection = 4;
				selectionChange = true;
			}
			else if ((gamepad.isButtonPressed(XINPUT_GAMEPAD_DPAD_DOWN) ||
				gamepad.leftStickY < -.80f) && selection == 4)
			{
				lastSelection = selection;
				selection = 0;
				selectionChange = true;
			}
			else if (gamepad.isButtonPressed(XINPUT_GAMEPAD_A))
			{
				return selection;
			}
			stateDelay.input = true;
			stateDelay.inputDelay = INPUT_DELAY;
			return -1;
		}
	}
	else //If no controller, then Keyboard
	{
		if (--stateDelay.inputDelay <= 0)
			stateDelay.input = false;
		if (!stateDelay.input)
		{
			if (keyboard.getKeyboardState().up && selection != 0)
			{
				lastSelection = selection--;
				selectionChange = true;
			}
			else if (keyboard.getKeyboardState().down && selection != 4)
			{
				lastSelection = selection++;
				selectionChange = true;
			}
			else if (keyboard.getKeyboardState().up && selection == 0)
			{
				lastSelection = selection;
				selection = 4;
				selectionChange = true;
			}
			else if (keyboard.getKeyboardState().down && selection == 4)
			{
				lastSelection = selection;
				selection = 0;
				selectionChange = true;
			}
			else if (keyboard.getKeyboardState().enter && selection == 0)
			{
				return selection;
			}
			stateDelay.input = true;
			stateDelay.inputDelay = INPUT_DELAY;
			return -1;
		}
	}
	return -1;
}
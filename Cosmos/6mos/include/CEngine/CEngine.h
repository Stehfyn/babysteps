#pragma once
#pragma warning( disable : 4996)
#define WINVER 0x500
#define _WIN32_WINNT 0x500
#define OEM_RESOURCE
#define NOMINMAX

#include <windows.h>
#include <winuser.h>
#include <commctrl.h>
#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <thread>
#include <string>
#include <Xinput.h>
#include <algorithm>

#define MOUSE_KEY 0x0000 //change this later
#define MAX_GAMEPAD_BUTTONS 14                                                                                                                                                                                             

#define LEFT_MOUSE 0x0001
#define RIGHT_MOUSE 0x0004
#define MIDDLE_MOUSE 0x0008

typedef DWORD(WINAPI* PSLWA)(HWND, DWORD, BYTE, DWORD);
static PSLWA pSetLayeredWindowAttributes = NULL;
static BOOL initialized = FALSE;

inline BOOL MakeWindowTransparent(HWND hWnd, unsigned char factor)
{
	//First, see if we can get the API call we need. If we've tried
	//once, we don't need to try again. 
	if (!initialized)
	{
		HMODULE hDLL = LoadLibraryA("user32");

		pSetLayeredWindowAttributes =
			(PSLWA)GetProcAddress(hDLL, 
				"SetLayeredWindowAttributes");

		//if our api call fails
		if (pSetLayeredWindowAttributes == NULL)
			return FALSE;


		initialized = TRUE;
	}
		
	return pSetLayeredWindowAttributes(hWnd,
		RGB(255, 255, 255),
		factor,
		LWA_ALPHA);
}
inline BOOL WINAPI ConsoleHandlerRoutine(DWORD dwCtrlType)
{
	// This Function overrides the CTRL_CLOSE_EVENT of our window.
	// Iterates 256 times, setting the window transparency to a decreasing
	// value (255-0) at a fixed time interval.

	HWND hwnd = GetConsoleWindow();
	if (dwCtrlType == CTRL_CLOSE_EVENT)
	{
		bool intro{ true };
		int transVal{256};
		while (intro)
		{
			std::chrono::microseconds frame_target_time = (std::chrono::microseconds)17;
			auto start = std::chrono::high_resolution_clock::now();

			transVal -= 1;

			MakeWindowTransparent(hwnd, transVal);

			if (transVal <= 0)
				intro = false;

			auto end = std::chrono::high_resolution_clock::now();
			auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

			std::this_thread::sleep_for(frame_target_time - elapsed);
		}
		SystemParametersInfo(SPI_SETCURSORS, 0, NULL, 0);
		return true;
	}
	return false;
}

class Keyboard
{
public:
	struct sKeyState
	{
		bool bPressed;
		bool bReleased;
		bool bHeld;
	}m_keys[256];

private:
	short m_keyOldState[256];
	short m_keyNewState[256];
public:
	Keyboard()
	{
		std::memset(m_keyNewState, 0, 256 * sizeof(short));
		std::memset(m_keyOldState, 0, 256 * sizeof(short));
		std::memset(m_keys, 0, 256 * sizeof(sKeyState));
	}
private:
	void Update()
	{
		for (int i = 0; i < 256; i++)
		{
			m_keyNewState[i] = GetAsyncKeyState(i);

			m_keys[i].bPressed = false;
			m_keys[i].bReleased = false;

			if (m_keyNewState[i] != m_keyOldState[i])
			{
				if (m_keyNewState[i] & 0x8000)
				{
					m_keys[i].bPressed = !m_keys[i].bHeld;
					m_keys[i].bHeld = true;
				}
				else
				{
					m_keys[i].bReleased = true;
					m_keys[i].bHeld = false;
				}
			}
			m_keyOldState[i] = m_keyNewState[i];
		}
	}
	friend class CEngine;
};
class Mouse
{
private:
	struct MousePoll
	{
		bool m_KeyState[3]{};

		int m_PosX{};
		int m_PosY{};

		bool m_VerticalWheel{};
		bool m_VerticalWheelUp{};
		bool m_VerticalWheelDown{};

		bool m_MousePollDoubleClick{};
		

	}m_MousePoll{};

public:
	Mouse()
	{
		
	}

	struct sButtonState
	{
		bool bPressed{};
		bool bReleased{};
		bool bHeld{};
	}ButtonState[3];

private:
	bool ButtonsNewState[3]{};
	bool ButtonsOldState[3]{};

public:
	struct sCursorState
	{
		int X{};
		int Y{};
	}CursorState{};

	//0: Move, 1: Up, 2: Down
	bool MouseWheelState[3];
private:
	void Set()
	{
		m_MousePoll.m_VerticalWheel = false;
		m_MousePoll.m_VerticalWheelUp = false;
		m_MousePoll.m_VerticalWheelDown = false;

		m_MousePoll.m_MousePollDoubleClick = false;
	}
public: //does client code need to be in control?
	bool Update()
	{
		//Transferring poll state to Mouse's state

		// Left, Right, Middle Mouse
		for (int i = 0; i < 3; i++)
		{
			ButtonsNewState[i] = m_MousePoll.m_KeyState[i];

			ButtonState[i].bPressed = false;
			ButtonState[i].bReleased = false;

			if (ButtonsNewState[i] != ButtonsOldState[i])
			{
				if (ButtonsNewState[i])
				{
					ButtonState[i].bPressed = !ButtonState[i].bHeld;
					ButtonState[i].bHeld = true;
				}
				else
				{
					ButtonState[i].bReleased = true;
					ButtonState[i].bHeld = false;
				}
			}

			ButtonsOldState[i] = ButtonsNewState[i];
		}

		//CursorPos
		CursorState.X = m_MousePoll.m_PosX;
		CursorState.Y = m_MousePoll.m_PosY;

		//MouseWheel
		MouseWheelState[0] = m_MousePoll.m_VerticalWheel;
		MouseWheelState[1] = m_MousePoll.m_VerticalWheelUp;
		MouseWheelState[2] = m_MousePoll.m_VerticalWheelDown;

		return true;
	}

	friend class CEngine;
};
class Gamepad
{
public:
	struct sButtonState
	{
		bool bPressed;
		bool bReleased;
		bool bHeld;
	}m_Buttons[14]{};

	struct sAnalogState
	{
		//Analog discrete values
		float X;
		float Y;
	}m_LeftStick{}, m_RightStick{};

	struct sTriggerState
	{
		//Trigger discrete values

		float val;

		bool bPressed;
		bool bReleased;
		bool bHeld;

		bool GetNewState()
		{
			return bTriggerNewState;
		}
		bool GetOldState()
		{
			return bTriggerOldState;
		}

		void SetNewState(bool state)
		{
			bTriggerNewState = state;
		}

		void SetOldState(bool state)
		{
			bTriggerOldState = state;
		}

	private:
		bool bTriggerNewState;
		bool bTriggerOldState;
	}m_LeftTrigger{}, m_RightTrigger{};

	Gamepad(UINT id) : controllerID(id), deadzoneX(XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE), deadzoneY(XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
	{
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
	}

	Gamepad(UINT id, float deadzoneX, float deadzoneY)
	{
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
	}

	float Normalize(float input, float min, float max)
	{
		float average = (min + max) / 2;
		float range = (max - min) / 2;
		return (input - average) / range;
	}

	float ApplyDeadzone(float value, float maxValue, float deadzone)
	{
		if (value < -deadzone)
		{
			value += deadzone; //increase neg vals to remove deadzone discontinuity
		}
		else if (value > deadzone)
		{
			value -= deadzone; //decrease pos vals to remove deadzone discontinuity
		}
		else
		{
			return 0; //hey values are zero for once
		}
		float normValue = (float)value / (float)(maxValue - deadzone);//scales to 0-1
		return std::max(-1.0f, std::min(normValue, 1.0f));
	}

	bool Update()
	{
		if (!isConnected())
			return false;

		//=================== Polling and Populating Buttons ==========
		//bitmask via https://docs.microsoft.com/en-us/windows/win32/api/xinput/ns-xinput-xinput_gamepad

		short ButtonBitmasks[MAX_GAMEPAD_BUTTONS] = {

			XINPUT_GAMEPAD_DPAD_UP,
			XINPUT_GAMEPAD_DPAD_DOWN,
			XINPUT_GAMEPAD_DPAD_LEFT,
			XINPUT_GAMEPAD_DPAD_RIGHT,

			XINPUT_GAMEPAD_START,
			XINPUT_GAMEPAD_BACK,

			XINPUT_GAMEPAD_LEFT_THUMB,
			XINPUT_GAMEPAD_RIGHT_THUMB,

			XINPUT_GAMEPAD_LEFT_SHOULDER,
			XINPUT_GAMEPAD_RIGHT_SHOULDER,

			XINPUT_GAMEPAD_A,
			XINPUT_GAMEPAD_B,
			XINPUT_GAMEPAD_X,
			XINPUT_GAMEPAD_Y

		};

		for (int i = 0; i < MAX_GAMEPAD_BUTTONS; i++)
		{
			m_ButtonsNewState[i] = isButtonPressed(ButtonBitmasks[i]);

			m_Buttons[i].bPressed = false;
			m_Buttons[i].bReleased = false;

			//State Change
			if (m_ButtonsNewState[i] != m_ButtonsOldState[i])
			{
				if (m_ButtonsNewState[i])
				{
					m_Buttons[i].bPressed = !m_Buttons[i].bHeld;
					m_Buttons[i].bHeld = true;
				}
				else
				{
					m_Buttons[i].bReleased = true;
					m_Buttons[i].bHeld = false;
				}
			}

			m_ButtonsOldState[i] = m_ButtonsNewState[i];
		}
		//=================== Polling and Populating Sticks ===========

		//Model after "Handle Input from olcConsoleGameEngine"

		//Normalize input range pre Deadzone
		float normLX = Normalize(static_cast<float>(state.Gamepad.sThumbLX), -32767, 32767);
		float normLY = Normalize(static_cast<float>(state.Gamepad.sThumbLY), -32767, 32767);

		float normRX = Normalize(static_cast<float>(state.Gamepad.sThumbRX), -32767, 32767);
		float normRY = Normalize(static_cast<float>(state.Gamepad.sThumbRY), -32767, 32767);

		//Apply deadzone if left or y is not under full weight
		if (deadzoneX <= 1.0f || deadzoneY <= 1.0f)
		{
			m_LeftStick.X = ApplyDeadzone(normLX, maxValue, deadzoneX);
			m_LeftStick.Y = ApplyDeadzone(normLY, maxValue, deadzoneY);
			m_RightStick.X = ApplyDeadzone(normRX, maxValue, deadzoneX);
			m_RightStick.Y = ApplyDeadzone(normRY, maxValue, deadzoneY);
		}
		//Apply gradient 
		else
		{
			m_LeftStick.X = ApplyDeadzone(normLX, maxValue, Normalize(deadzoneX, SHRT_MIN, SHRT_MAX));
			m_LeftStick.Y = ApplyDeadzone(normLY, maxValue, Normalize(deadzoneY, SHRT_MIN, SHRT_MAX));
			m_RightStick.X = ApplyDeadzone(normRX, maxValue, Normalize(deadzoneX, SHRT_MIN, SHRT_MAX));
			m_RightStick.Y = ApplyDeadzone(normRY, maxValue, Normalize(deadzoneY, SHRT_MIN, SHRT_MAX));
		}

		//============== Polling and Populating Triggers =============
		m_LeftTrigger.val = static_cast<float>(state.Gamepad.bLeftTrigger) / 255.0f;//normalize input 
		m_RightTrigger.val = static_cast<float>(state.Gamepad.bRightTrigger) / 255.0f;

		m_LeftTrigger.SetNewState((m_LeftTrigger.val) != 0);
		m_RightTrigger.SetNewState((m_RightTrigger.val) != 0);

		m_LeftTrigger.bPressed = false;
		m_LeftTrigger.bReleased = false;

		m_RightTrigger.bPressed = false;
		m_RightTrigger.bReleased = false;

		if (m_LeftTrigger.GetNewState() != m_LeftTrigger.GetOldState())
		{
			if (m_LeftTrigger.GetNewState())
			{
				m_LeftTrigger.bPressed = !m_LeftTrigger.bHeld;
				m_LeftTrigger.bHeld = true;
			}
			else
			{
				m_LeftTrigger.bReleased = true;
				m_LeftTrigger.bHeld = false;
			}
		}
		m_LeftTrigger.SetOldState(m_LeftTrigger.GetNewState());

		if (m_RightTrigger.GetNewState() != m_RightTrigger.GetOldState())
		{
			if (m_RightTrigger.GetNewState())
			{
				m_RightTrigger.bPressed = !m_RightTrigger.bHeld;
				m_RightTrigger.bHeld = true;
			}
			else
			{
				m_RightTrigger.bReleased = true;
				m_RightTrigger.bHeld = false;
			}
		}
		m_RightTrigger.SetOldState(m_RightTrigger.GetNewState());

		return true;
	}

	UINT getControllerID() const
	{
		return controllerID;
	}

	bool isConnected()
	{
		if (XInputGetState(controllerID, &state) == ERROR_SUCCESS)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool isButtonPressed(UINT button) const
	{
		return (state.Gamepad.wButtons & button) != 0;
	}

	void Vibrate(USHORT speed)
	{
		vibration.wLeftMotorSpeed = speed;
		vibration.wRightMotorSpeed = speed;
		XInputSetState(controllerID, &vibration);
	}

	void Vibrate(USHORT leftSpeed, SHORT rightSpeed)
	{
		vibration.wLeftMotorSpeed = leftSpeed;
		vibration.wRightMotorSpeed = rightSpeed;
		XInputSetState(controllerID, &vibration);
	}

	~Gamepad()
	{

	}

private:
	UINT controllerID;
	XINPUT_STATE state;
	XINPUT_VIBRATION vibration;

	static constexpr float maxValue = 1.0f;

	bool m_ButtonsNewState[14];
	bool m_ButtonsOldState[14];

	float deadzoneX;
	float deadzoneY;
};

class CEngine
{
public:

	CEngine() : Keyboard(), Mouse(), Gamepad(0) 
	{
		hwnd = GetConsoleWindow();

		m_nScreenWidth = 80;
		m_nScreenHeight = 30;

		//Place Cursor offscreen
		Mouse.m_MousePoll.m_PosX = -1;
		Mouse.m_MousePoll.m_PosY = -1;

		m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		m_hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);

		m_wsTitle = L"Default App Name";
	}

	int ConstructConsole(int width, int height, int fontw, int fonth)
	{
		if (m_hConsole == INVALID_HANDLE_VALUE)
			return Error(L"Bad Handle");

		m_nScreenWidth = width;
		m_nScreenHeight = height;

		//Shrink Window before Buffer Expansion
		m_sRect = {0,0,1,1};
		SetConsoleWindowInfo(m_hConsole, TRUE, &m_sRect);

		//Set the size of the buffer
		m_coord = { (short)(m_nScreenWidth), (short)(m_nScreenHeight)};
		if (!SetConsoleScreenBufferSize(m_hConsole, m_coord))
			Error(L"SetConsoleScreenBufferSize");

		//Assign buffer to console
		if (!SetConsoleActiveScreenBuffer(m_hConsole))
			Error(L"SetConsoleScreenBufferSize2");
		//Set CursorInfo
		
		//Set cfi
		m_cfi.cbSize = sizeof(m_cfi);
		m_cfi.nFont = 0;
		m_cfi.dwFontSize.X = fontw;
		m_cfi.dwFontSize.Y = fonth;
		m_cfi.FontFamily = FF_DONTCARE;
		m_cfi.FontWeight = FW_NORMAL;

		wcscpy(m_cfi.FaceName, L"Terminal");
		if (!SetCurrentConsoleFontEx(m_hConsole, false, &m_cfi))
			return Error(L"SetCurrentConsoleFontEx");

		//Set csbi
		
		if (!GetConsoleScreenBufferInfo(m_hConsole, &m_csbi))
			return Error(L"GetConsoleScreenBufferInfo");
		if (m_nScreenHeight > m_csbi.dwMaximumWindowSize.Y)
			return Error(L"Screen Height / Font Height Too Big");
		if (m_nScreenWidth > m_csbi.dwMaximumWindowSize.X)
			return Error(L"Screen Width / Font Width Too Big");

		m_sRect = { 0, 0, (short)m_nScreenWidth - 1, (short)m_nScreenHeight - 1};
		if (!SetConsoleWindowInfo(m_hConsole, TRUE, &m_sRect))
			return Error(L"SetConsoleWindowInfo");

		// Set flags to allow mouse input and window input events to populate our console event messages		
		if (!SetConsoleMode(m_hConsoleIn, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_VIRTUAL_TERMINAL_INPUT))
			return Error(L"SetConsoleMode");

		// Allocate memory for screen buffer, set that space in memory to 0
		m_CharInfo = new CHAR_INFO[m_nScreenWidth * m_nScreenHeight];
		memset(m_CharInfo, 0, sizeof(CHAR_INFO) * m_nScreenWidth * m_nScreenHeight);

		//Set the ConsoleCtrlHandler with our overridden ConsoleHandlerRoutine
		SetConsoleCtrlHandler(ConsoleHandlerRoutine, true);

		//Initialize time_point variables for fps
		tp1 = std::chrono::system_clock::now();
		tp2 = std::chrono::system_clock::now();
	}
	void SetTitle(std::wstring pTitle)
	{
		m_wsTitle = pTitle;
	}

	void DrawChar(int x, int y, short c, short col)
	{
		if ((x >= 0) && (x < m_nScreenWidth) && (y >= 0) && (y < m_nScreenHeight))
		{
			m_CharInfo[y * m_nScreenWidth + x].Char.UnicodeChar = c;
			m_CharInfo[y * m_nScreenWidth + x].Attributes = col;
		}
	}

	void DrawRect(int p_x, int p_y, int width, int height, wchar_t Border, wchar_t Fill, short BorderCol, short FillCol)
	{
		bool canDraw = ((p_x >= 0 && (p_x + width) <= m_nScreenWidth) && ((p_y >= 0) && p_y + height <= m_nScreenHeight));
		if (canDraw)
		{
			for (int y = p_y; y < p_y + height; y++)
				for (int x = p_x; x < p_x + width; x++)
				{
					if (x == p_x || y == p_y || x == p_x + width - 1 || y == p_y + height - 1)
					{
						DrawChar(x, y, Border, BorderCol);
					}
					else
					{
						DrawChar(x, y, Fill, FillCol);
					}
				}
		}
		//DrawChar(p_x, p_y, Border, BorderCol);
	}

	//Poll Console Events
	void UpdateConsoleEvents()
	{
		tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsed = tp2 - tp1;
		std::chrono::duration<float, std::milli> elapsedTime = tp2 - tp1;
		while (elapsedTime.count() < 8.335)
		{
			tp2 = std::chrono::system_clock::now();
			elapsedTime = tp2 - tp1;
			elapsed = tp2 - tp1;
		}
		tp1 = tp2;
		m_fps = 1.0f / elapsed.count();
		t_fElapsed = elapsedTime.count() / 1000.0f;

		INPUT_RECORD inBuf[32]{};
		DWORD events = 0;
		GetNumberOfConsoleInputEvents(m_hConsoleIn, &events);

		if (events > 0)
		{
			ReadConsoleInput(m_hConsoleIn, inBuf, 32, &events);
			FlushConsoleInputBuffer(m_hConsoleIn);
		}

		//Poll input devices
		Keyboard.Update();
		Gamepad.Update();

		Mouse.Set();
		for (DWORD i = 0; i < events; i++)
		{
			switch (inBuf[i].EventType)
			{
				//Prepare structure of mouse events
			case FOCUS_EVENT:
			{
				CE_InFocus = inBuf[i].Event.FocusEvent.bSetFocus;
				if(!CE_InFocus)
					SystemParametersInfo(SPI_SETCURSORS, 0, NULL, 0);
				break;
			}
			//Mouse Events are not sent when the window is no longer active
			case MOUSE_EVENT:
			{
				switch (inBuf[i].Event.MouseEvent.dwEventFlags) //dweventflags we needs to use dwButtonState
				{
				case MOUSE_KEY:
				{
					DWORD dwButtonState = inBuf[i].Event.MouseEvent.dwButtonState;
					short bitmasks[3] = { LEFT_MOUSE, RIGHT_MOUSE, MIDDLE_MOUSE };
					for (int i = 0; i < 3; i++)
					{
						Mouse.m_MousePoll.m_KeyState[i] = (dwButtonState & bitmasks[i]) > 0;   //bitmasks[i]) > 0;
					}
					break;
				}
				case MOUSE_MOVED:
				{
					Mouse.m_MousePoll.m_PosX = inBuf[i].Event.MouseEvent.dwMousePosition.X;
					Mouse.m_MousePoll.m_PosY = inBuf[i].Event.MouseEvent.dwMousePosition.Y;
					break;
				}
				case DOUBLE_CLICK:
				{
					Mouse.m_MousePoll.m_MousePollDoubleClick = true;
					break;
				}
				case MOUSE_WHEELED:
				{
					//Bit shifting dwButtonState down two Bytes, per msdn
					short key_code = HIWORD(inBuf[i].Event.MouseEvent.dwButtonState);
					if (key_code > 0)
						Mouse.m_MousePoll.m_VerticalWheelUp = true;
					else
						Mouse.m_MousePoll.m_VerticalWheelDown = true;
					Mouse.m_MousePoll.m_VerticalWheel = true;
					break;
				}
				default:
					break;
				}
			}
			case WINDOW_BUFFER_SIZE_EVENT:
			{
				if (inBuf[i].Event.WindowBufferSizeEvent.dwSize.X != m_nScreenWidth ||
					inBuf[i].Event.WindowBufferSizeEvent.dwSize.Y != m_nScreenHeight)
				{
					//SetConsoleWindowInfo(m_hConsole, true, &m_sRect);
					//SetConsoleScreenBufferSize(m_hConsole, coord);
				}
				break;
			}
			default:
				break;
			}
		}
		Mouse.Update();
	}

	void RenderClear()
	{
		//Clear CharInfo buffer of Char and Color Info
		for (int y = 0; y < m_nScreenHeight; y++)
			for (int x = 0; x < m_nScreenWidth; x++)
			{
				DrawChar(x, y, L' ', 0x0000);
			}
	}

	void PresentRender()
	{
		GetConsoleScreenBufferInfo(m_hConsole, &m_csbi);
		
		//Set Console Title to m_wsTitle
		wchar_t s[256];
		swprintf_s(s, 256, L"%s, FPS: %3.2f, Top Left: (%d, %d) Bot Right: (%d, %d) Mouse Pos: (%d, %d)", 
			m_wsTitle.c_str(), m_fps, m_csbi.srWindow.Left, m_csbi.srWindow.Top, m_csbi.srWindow.Right, m_csbi.srWindow.Bottom,
			Mouse.CursorState.X, Mouse.CursorState.Y);
		SetConsoleTitle(s);

		/*SMALL_RECT fixed;
		fixed.Left = 1, fixed.Top = 1, fixed.Bottom = 30, fixed.Right = 80;*/

		//Blit to Screen
		WriteConsoleOutput(m_hConsole, m_CharInfo, { (short)m_nScreenWidth, (short)m_nScreenHeight }, { 0,0 }, &m_sRect);
	}

	int Error(const wchar_t* msg)
	{
		wchar_t buf[256];
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buf, 256, NULL);
		wprintf(L"ERROR: %s\n\t%s\n", msg, buf);
		return 0;
	}

	static BOOL CloseHandler(DWORD evt)
	{

	}

	~CEngine()
	{
		SystemParametersInfo(SPI_SETCURSORS, 0, NULL, 0);
		delete[] m_CharInfo;
	}

	bool OnUserCreate() {}
	bool OnUserUpdate(float fElapsedTime) {} // Look at GameThread for fixing timestep and calculating delta_time
	
public:
	Gamepad Gamepad;
	Mouse Mouse;
	Keyboard Keyboard;

	BOOL CE_InFocus{true}; //initialize with focus

protected:
	int m_nScreenWidth;
	int m_nScreenHeight;
private:

	std::wstring m_wsTitle;
	HWND hwnd{};

	HANDLE m_hConsole;
	HANDLE m_hConsoleIn;

	CONSOLE_FONT_INFOEX m_cfi;
	CONSOLE_SCREEN_BUFFER_INFO m_csbi;

	SMALL_RECT m_sRect;
	COORD m_coord;

	CHAR_INFO* m_CharInfo;

	std::chrono::system_clock::time_point tp1{};
	std::chrono::system_clock::time_point tp2{};

public:
	float m_fps{};
	float t_fElapsed{};
};
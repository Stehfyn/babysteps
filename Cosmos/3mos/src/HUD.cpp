#include "HUD.h"
void::HUD::displayScore(int score, Buffer buffer)
{
	int xOffset{ 39 };
	int yOffset{ 1 };
	scoreString = std::to_wstring(score);
	int scoreLength = scoreString.length();
	
	if (scoreLength == 3 || scoreLength == 4)
		xOffset -= 1;
	if (scoreLength == 5)
		xOffset -= 2;
	
	//scoreArray = new wchar_t[scoreString.length()];
	for(int i = 0; i < scoreLength; i++)
		buffer.edit(i + xOffset, yOffset, scoreString[i]);
}
void::HUD::displayEnemies(int remaining, Buffer buffer)
{
	int xOffset{ 77 };
	int yOffset{ 1 };

	currRemainString = std::to_wstring(remaining);

	int currLength = currRemainString.length(), lastLength = lastRemainString.length();

	if (currLength < lastLength)
		buffer.edit(xOffset + 1, yOffset, L' ');
	
	int remainLength = currRemainString.length();

	std::wstring enemyString = L"?: ";
	for (int i = 0; i < enemyString.length(); i++)
		buffer.edit(xOffset - 3 + i, 1, enemyString[i]);

	for (int i = 0; i < remainLength; i++)
		buffer.edit(i + xOffset, yOffset, currRemainString[i]);

	lastRemainString = std::to_wstring(remaining);
}
void::HUD::displayAccuracy(double accuracy, Buffer buffer)
{
	int xOffset{70};
	int yOffset{1};

	accuracy *= 100;
	std::ostringstream temp;
	temp << std::fixed;
	temp << std::setprecision(2);
	temp << accuracy;
	currAccString = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(temp.str()) + L'%';

	if (currAccString.length() > 7 || accuracy == 0) //zero initial shots results in a -nan(ind), a string longer than 7 (just laugh)
		currAccString = L"0.00%";
	if (currAccString.length() == 5)
	{
		buffer.edit(xOffset - 5, 1, L' ');
		buffer.edit(xOffset - 6, 1, L' ');
	}
	if (currAccString.length() == 6)
		buffer.edit(xOffset - 6, 1, L' ');
	for (int i = 0; i < currAccString.length(); i++)
		buffer.edit(xOffset - i, yOffset, currAccString[currAccString.length() - 1 - i]);
}
void::HUD::displayLine(Buffer buffer)
{
	for (int i = 0; i < 80; i++)
		buffer.edit(i, 2, L'─');
}
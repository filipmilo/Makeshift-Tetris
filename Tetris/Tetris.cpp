#include <iostream>
#include <windows.h>
#include <thread>
#include "Field.h"
using namespace std;

#define screenWidth  120			
#define screenHeight  60

int main() {
	SetConsoleTitle(L"TETRIS");

	Type types[7] = { SQUARE, LSHAPE, JSHAPE, LLONG, ZSHAPE, SSHAPE, TSHAPE };
	srand(time(0));
	int rtype = rand() % 7;
	Field field;
	Tetromino new1(types[rtype]);

	//logic
	bool GameOver = false;
	bool keys[4];
	bool keypress = false;
	int forcedown = 0;
	int speedfactor = 15;
	int linescleared = 0;
	int totallines = 0;
	int score = 0;

	wchar_t* screen = new wchar_t[screenWidth * screenHeight];
	for (int i = 0; i < screenWidth * screenHeight; i++) screen[i] = L' ';
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	while (!GameOver) {

		this_thread::sleep_for(50ms);

		for (int i = 0; i < 4; i++)
			keys[i] = (0x8000 & GetAsyncKeyState((unsigned char)("ASDW"[i]))) != 0;

		if (keys[0]) {
			Tetromino temp(new1);
			temp.setCurrentX(new1.getCurrentX() - 1);
			if (field.doesPieceFit(temp)) new1.setCurrentX(new1.getCurrentX() - 1);
		}

		if (keys[1]) {
			Tetromino temp(new1);
			temp.setCurrentY(new1.getCurrentY() + 1);
			if (field.doesPieceFit(temp)) new1.setCurrentY(new1.getCurrentY() + 1);
		}

		if (keys[2]) {
			Tetromino temp(new1);
			temp.setCurrentX(new1.getCurrentX() + 1);
			if (field.doesPieceFit(temp)) new1.setCurrentX(new1.getCurrentX() + 1);
		}

		if (keys[3]) {
			Tetromino temp(new1);
			temp.rotatePiece();
			if (keypress && field.doesPieceFit(temp)) new1.rotatePiece();
			keypress = false;
		}
		else keypress = true;

		if (forcedown == speedfactor) {

			Tetromino temp(new1);
			temp.setCurrentY(new1.getCurrentY() + 1);
			if (field.doesPieceFit(temp)) new1.setCurrentY(new1.getCurrentY() + 1);
			else {

				field.updatefield(new1);
				linescleared = field.checkLines(new1.getCurrentY());
				totallines += linescleared;
				switch (totallines) {
					case 10: speedfactor = 12; break;
					case 15: speedfactor = 10; break;
					case 25: speedfactor = 8; break;
					case 35: speedfactor = 7; break;
					case 45: speedfactor = 5; break;
					default: break;
				}
				score += totallines * linescleared + linescleared * 25;

				rtype = rand() % 7;
				Tetromino new2(types[rtype]);
				new1.updatePiece(new2);

				if (!field.doesPieceFit(new1)) GameOver = true;
			}
			forcedown = 0;
		}
		else forcedown++;

		field.drawField(screen, screenWidth);
		new1.drawPiece(screen, screenWidth);
		swprintf_s(&screen[3 *screenWidth + fieldWidth + 6], 16, L"SCORE: %8d", score);
		swprintf_s(&screen[4 * screenWidth + fieldWidth + 6], 16, L"LINES: %8d", totallines);
		swprintf_s(&screen[6 * screenWidth + fieldWidth + 6], 9, L"W-ROTATE");
		swprintf_s(&screen[7 * screenWidth + fieldWidth + 6], 7, L"A-LEFT");
		swprintf_s(&screen[8 * screenWidth + fieldWidth + 6], 8, L"D-RIGHT");
		swprintf_s(&screen[9 * screenWidth + fieldWidth + 6], 7, L"S-DOWN");
		
		WriteConsoleOutputCharacter(hConsole, screen, screenWidth * screenHeight, { 0,0 }, &dwBytesWritten);
	}

	CloseHandle(hConsole);
	cout << "GAME OVER!" << endl;
	cout << "YOUR SCORE WAS: " << score << endl;
	system("pause");
	return 0;
}
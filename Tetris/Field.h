#pragma once
#include "Tetromino.h"

#define fieldWidth 14
#define fieldHeight 18

class Field {
private:
	unsigned char field[fieldHeight][fieldWidth];

public:
	Field(){
		for (int i = 0; i < fieldHeight; i++) 
			for (int j = 0; j < fieldWidth; j++) {
				if (j == 0 || j == fieldWidth -1 || i == fieldHeight -1)
					field[i][j] = '#';
				else
					field[i][j] = ' ';
			}
	}

	void updatefield(Tetromino& put) {
		for (int x = 0; x < 4; x++) {
			for (int y = 0; y < 4; y++) {
				if (put.getPiecePart(y, x) != ' ')
					field[put.getCurrentY() + y][put.getCurrentX() + x] = put.getPiecePart(y, x);
			}
		}
	};

	void drawField(wchar_t* screen, int screenWidth) {
		for (int i = 0; i < fieldHeight; i++) {
			for (int j = 0; j < fieldWidth; j++) {
				screen[(i + 2) * screenWidth + j + 2] = field[i][j];
			}
		}
	}

	bool doesPieceFit(Tetromino& check) {
		for (int x = 0; x < 4; x++) {
			for (int y = 0; y < 4; y++) {
				if (field[check.getCurrentY() + y][check.getCurrentX() + x] != ' ' && check.getPiecePart(y, x) != ' ') return false;
			}
		}
		return true;
	}

	int checkLines(int currentY) {
		int n = 0;
		bool isline;
		for (int i = currentY; i <= currentY + 3; i++) {
			isline = true;
			for (int j = 1; j < fieldWidth - 1; j++) {
				if (field[i][j] == ' ' || field[i][j] == '#') isline = false;

				if ((j == fieldWidth - 2) && (field[i][j] != ' ') && isline) n++;
			}

			if (isline) {
				for (int j = 1; j < fieldWidth - 1; j++) {
					field[i][j] = '=';
				}
				this_thread::sleep_for(200ms);
				for (int j = 1; j < fieldWidth - 1; j++) {
					field[i][j] = ' ';
				}

				for (int x = i; x > 0; x--) {
					for (int y = 1; y < fieldWidth; y++) {
						if (field[x][y] != '#') {
							field[x][y] = field[x - 1][y];
						}
					}
				}
			}
		}
		return n;
	}
};
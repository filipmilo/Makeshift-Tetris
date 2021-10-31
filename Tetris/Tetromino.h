#pragma once

#include <iostream>
using namespace std;

enum Type {SQUARE, LSHAPE, JSHAPE, LLONG, ZSHAPE, SSHAPE, TSHAPE};

class Tetromino {
private:
	unsigned char piece[4][4];
	Type type;
	int currentX;
	int currentY;
public:
	
	// constructor with parameters
	Tetromino(Type type) {
		this->type = type;
		makePiece();
		currentX = 6;
		currentY = 0;
	}

	// copy constructor
	Tetromino(const Tetromino& original) {
		type = original.type;
		currentX = original.currentX;
		currentY = original.currentY;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				piece[i][j] = original.piece[i][j];
	}

	//make a piece
	void makePiece() {
		switch (type) {
		case SQUARE:
			for(int i = 0; i < 4; i++)
				for(int j = 0; j < 4; j++) {
					if ((i == 1 && j == 1) || (i == 1 && j == 2) || (i == 2 && j == 1) || (i == 2 && j == 2))
						piece[i][j] = 'A';
					else
						piece[i][j] = ' ';
				}
			break;
		case LSHAPE:
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++) {
					if ((i == 0 && j == 1) || (i == 1 && j == 1) || (i == 2 && j == 1) || (i == 2 && j == 2))
						piece[i][j] = 'B';
					else
						piece[i][j] = ' ';
				}
			break;
		case JSHAPE:
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++) {
					if ((i == 0 && j == 2) || (i == 1 && j == 2) || (i == 2 && j == 1) || (i == 2 && j == 2))
						piece[i][j] = 'C';
					else
						piece[i][j] = ' ';
				}
			break;
		case LLONG:
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++) {
					if ((i == 0 && j == 1) || (i == 1 && j == 1) || (i == 2 && j == 1) || (i == 3 && j == 1))
						piece[i][j] = 'D';
					else
						piece[i][j] = ' ';
				}
			break;
		case ZSHAPE:
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++) {
					if ((i == 1 && j == 0) || (i == 1 && j == 1) || (i == 2 && j == 1) || (i == 2 && j == 2))
						piece[i][j] = 'E';
					else
						piece[i][j] = ' ';
				}
			break;
		case SSHAPE:
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++) {
					if ((i == 1 && j == 3) || (i == 1 && j == 2) || (i == 2 && j == 1) || (i == 2 && j == 2))
						piece[i][j] = 'F';
					else
						piece[i][j] = ' ';
				}
			break;
		case TSHAPE:
			for (int i = 0; i < 4; i++)
				for (int j = 0; j < 4; j++) {
					if ((i == 1 && j == 1) || (i == 2 && j == 0) || (i == 2 && j == 1) || (i == 2 && j == 2))
						piece[i][j] = 'G';
					else
						piece[i][j] = ' ';
				}
			break;
		default: break;
		}
	}

	void rotatePiece() {
		//transposing of the matrix
		for (int i = 0; i < 4; i++) {
			for (int j = i; j < 4; j++) {
				unsigned char temp = piece[i][j];
				piece[i][j] = piece[j][i];
				piece[j][i] = temp;
			}
		}
		//fliping horizontally
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4/2; j++) {
				unsigned char temp = piece[i][j];
				piece[i][j] = piece[i][4 - 1 - j];
				piece[i][4 - 1 -j] = temp;
			}
		}
	}

	void drawPiece(wchar_t* screen,int screenWidth) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if(piece[i][j] != ' ') screen[(i + currentY + 2) * screenWidth + j + currentX + 2] = piece[i][j];
			}
		}
	}

	void updatePiece(Tetromino& replace) {
		type = replace.type;
		currentX = replace.currentX;
		currentY = replace.currentY;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				piece[i][j] = replace.piece[i][j];
	}

	unsigned char getPiecePart(int x, int y) {
		return piece[x][y];
	}

	int getCurrentX() {
		return currentX;
	}

	int getCurrentY() {
		return currentY;
	}

	void setCurrentX(int currentX) {
		this->currentX = currentX;
	}
	void setCurrentY(int currentY) {
		this->currentY = currentY;
	}
};
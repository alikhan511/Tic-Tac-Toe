#pragma once

//header files
#include"iostream"
#include"iomanip"
#include"string"
#include"cmath"
#include"fstream"
#include"vector"
#include"sstream"
#include"windows.h"

using namespace std;


class TicTacToe
{
private:
	int **board; // Pointer as a private data member for creating 2D array on heap memory
	int size;  //variable for the size of the board
	int player;
	int tCounter;
	int mark;
	string markPause;
	fstream file;

public:
	TicTacToe();
	~TicTacToe();
	void setSize(int size);
	void setBoard();
	int getSize() const;
	void printBoard();
	void setFile(); 
	void closeFile();
	void inputGameState();
	void saveState();

	int getTurnCounter() const;
	void deleteGameState();
	void play();
	void markCell(int m);
	bool checkWinState();
	int getPlayer() const;
};














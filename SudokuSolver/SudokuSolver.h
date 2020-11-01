#pragma once
#include <iostream>
#include <string>
#include <math.h>

#define UNASSINGED 0

using namespace std;

class SudokuSolver
{
public:
	static SudokuSolver* GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new SudokuSolver();
		}
		return instance;
	}

	static const int rowAndColumnLen = 9;

	int* UserSudokuSheet();
	int GetRowNum();
	int GetRowColumnLen() { return rowAndColumnLen; }
	int GetRowIndex() { return rowNum; }
	void PrintBoard(int board[rowAndColumnLen][rowAndColumnLen]);
	bool FindUnassignedLocation(int board[rowAndColumnLen][rowAndColumnLen], int &row, int &col);
	bool UsedInRow(int board[rowAndColumnLen][rowAndColumnLen], int row, int num);
	bool UsedInCol(int board[rowAndColumnLen][rowAndColumnLen], int col, int num);
	bool UsedInBox(int board[rowAndColumnLen][rowAndColumnLen], int boxStarRow, int boxStarCol, int num);
	bool IsSafe(int board[rowAndColumnLen][rowAndColumnLen], int row, int col, int num);
	bool Solve(int board[rowAndColumnLen][rowAndColumnLen]);

	

private:
	SudokuSolver();
	~SudokuSolver();

	string userValues;
	int rowNum = 0;
	int singleRow[SudokuSolver::rowAndColumnLen];
	// singleton instance
	static SudokuSolver* instance;
};


#include "SudokuSolver.h"

// singletone instance initialization
SudokuSolver* SudokuSolver::instance = nullptr;

SudokuSolver::SudokuSolver()
{
}

SudokuSolver::~SudokuSolver()
{
}

int* SudokuSolver::UserSudokuSheet()
{
	for (int i = 0; i < GetInstance()->GetRowColumnLen(); i++) { singleRow[i] = 0; }

	string userValuesStr;
	userValuesStr[0] = '\0';

	getline(cin, userValuesStr);

	int userValuesInt = stoi(userValuesStr);

	for (int i = SudokuSolver::GetInstance()->GetRowColumnLen() - 1; i >= 0; i--)
	{
		singleRow[i] = userValuesInt % 10;
		userValuesInt /= 10;
	}

	return singleRow;
}

int SudokuSolver::GetRowNum()
{
	rowNum++;

	return rowNum;
}

void SudokuSolver::PrintBoard(int board[rowAndColumnLen][rowAndColumnLen])
{
	cout << "+-----------+-----------+-----------+";
	cout << endl;
	for (int i = 0; i < rowAndColumnLen; i++)
	{
		cout << "| ";
		for (int j = 0; j < rowAndColumnLen; j++)
		{
			cout << board[i][j];

			if (j == 2 || j == 5 || j == 8)
			{
				cout << " | ";
			}
			else
			{
				cout << "   ";
			}
		}
		cout << endl;
		if ( i == 2 || i == 5 || i == 8)
		{
			cout << "+-----------+-----------+-----------+"; 
			cout << endl;
		}
		else
		{
			cout << "|           |		|           |" << endl;
		}
	}
}

// loops through the Sudoku board looking for any unnassigned values (0)
bool SudokuSolver::FindUnassignedLocation(int board[rowAndColumnLen][rowAndColumnLen], int& row, int& col)
{
	for (row = 0; row < rowAndColumnLen; row++)
	{
		for (col = 0; col < rowAndColumnLen; col++)
		{
			// when 0 is found, it returns true
			if (board[row][col] == UNASSINGED)
			{
				return true;
			}
		}
	}

	// returns false when no unassigned entries remain
	return false;
}

// returns true if an assigned entry in the specified row matches another given number
// meaning that number is unique to that row
bool SudokuSolver::UsedInRow(int board[rowAndColumnLen][rowAndColumnLen], int row, int num)
{
	for (int col = 0; col < rowAndColumnLen; col++)
	{
		if (board[row][col] == num)
		{
			return true;
		}
	}

	return false;
}

// returns true if an assigned entry in the specified column matches another given number
// meaning that number is unique to that column
bool SudokuSolver::UsedInCol(int board[rowAndColumnLen][rowAndColumnLen], int col, int num)
{
	for (int row = 0; row < rowAndColumnLen; row++)
	{
		if (board[row][col] == num)
		{
			return true;
		}
	}

	return false;
}

// returns true if an assigned entry in the specified 3x3 box matches another given number
// meaning that number is unique to that 3x3 box
bool SudokuSolver::UsedInBox(int board[rowAndColumnLen][rowAndColumnLen], int boxStarRow, int boxStarCol, int num)
{
	int rowRowCol = sqrt(rowAndColumnLen);

	for (int row = 0; row < rowRowCol; row++)
	{
		for (int col = 0; col < rowRowCol; col++)
		{
			if (board[row + boxStarRow][col + boxStarCol] == num)
			{
				return true;
			}
		}
	}

	return false;
}

// indicates whether a number is a legal entry into the sudoku board
bool SudokuSolver::IsSafe(int board[rowAndColumnLen][rowAndColumnLen], int row, int col, int num)
{
	int rowRowCol = sqrt(rowAndColumnLen);

	return !UsedInRow(board, row, num) 
		&& !UsedInCol(board, col, num) 
		&& !UsedInBox(board, row - row % rowRowCol, col - col % rowRowCol, num) 
		&& board[row][col] == UNASSINGED;
}

bool SudokuSolver::Solve(int board[rowAndColumnLen][rowAndColumnLen])
{
	int row, col;

	// if no unassigned locations, puzzle is solved
	if (!FindUnassignedLocation(board, row, col))
	{
		return true;
	}

	for (int num = 1; num <= rowAndColumnLen; num++)
	{
		// check to see if safe
		if (IsSafe(board, row, col, num))
		{
			// make a tentative assignment
			board[row][col] = num;

			// Return, if the value is successful
			if (Solve(board))
			{
				return true;
			}

			// Failed, reset to 0, try again
			board[row][col] = UNASSINGED;
		}
	}

	return false;
}

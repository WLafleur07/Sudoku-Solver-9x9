#include "SudokuSolver.h"

int main()
{
	bool boardEmpty = true;
	int board[SudokuSolver::rowAndColumnLen][SudokuSolver::rowAndColumnLen];
	
	cout << "Enter each row of your sudoku sheet. At the end of the row, hit Enter" << endl;
	cout << "If there is a blank space, simply enter a 0:" << endl << endl;

	while (boardEmpty)
	{
		int* buffer = SudokuSolver::GetInstance()->UserSudokuSheet();

		for (int i = 0; i < SudokuSolver::GetInstance()->GetRowColumnLen(); i++)
		{
			board[SudokuSolver::GetInstance()->GetRowIndex()][i] = buffer[i];
		}

		int rowCounter = SudokuSolver::GetInstance()->GetRowNum();

		if (rowCounter == 9)
		{
			boardEmpty = false;
		}
	}

	system("cls");

	if (SudokuSolver::GetInstance()->Solve(board) == true)
	{
		cout << endl << endl;
		SudokuSolver::GetInstance()->PrintBoard(board);
	}
	else
	{
		cout << "No solution exists";
	}

	return 0;
}
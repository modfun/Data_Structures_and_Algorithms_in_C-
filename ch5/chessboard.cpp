#include "chessboard.h"

using std::cout; using std::cin; using std::endl;

ChessBoard::ChessBoard(): available(true), squares(8), norm(squares-1)
{
	initializeBoard();
}

ChessBoard::ChessBoard(int n): available(true), squares(n), norm(squares-1)
{
	initializeBoard();
}

ChessBoard::~ChessBoard()
{
	delete column;
	delete left;
	delete right;
	delete position;
}

void ChessBoard::initializeBoard()
{
	register int i;

	position = new int[squares];		// [row] -> col
	column = new bool[squares];
	left = new bool[2*squares - 1];
	right = new bool[2*squares - 1];

	for (i = 0; i < squares; i++)
	{
		position[i] = -1;
		column[i] = available;
	}
	for (i = 0; i < 2*squares - 1; i++)
	{
		right[i] = available;
		left[i] = available;
	}

	howMany = 0;
}

void ChessBoard::putQueen(int row)
{
	for (int col = row; col < squares; col++)
	{
		if ((column[col] == available) &&
			(left[row + col] == available) &&
			(right[row - col + norm] == available))
		{
			position[row] = col;
			column[col] = !available;
			left[row + col] = !available;
			right[row - col + norm] = !available;

			if (row < (squares - 1))
			{
				putQueen(row + 1);
			}
			else
			{
				howMany++;
				printBoard(cout);
				cout << endl;
			}

			column[col] = available;
			left[row + col] = available;
			right[row - col + norm] = available;
		}
	}
}

void ChessBoard::findSolutions()
{
	putQueen(0);
	cout << howMany << " Solutions.\n";
}

void ChessBoard::printBoard(ostream &out)
{
	for (int row = 0; row < squares; row++)
	{
		for (int col = 0; col < squares; col++)
		{
			if (position[row] == col)
				out << 'Q';
			else
				out << '@';
			out << ' ';
		}
		out << '\n';
	}
}

int main(void)
{
	ChessBoard b(7);
	b.findSolutions();

	return (EXIT_SUCCESS);
}

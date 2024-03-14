#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include <cstddef>

using std::ostream;

class ChessBoard
{
	private:
		const bool available;
		const int squares, norm;
		bool *left, *right, *column;
		int *position, howMany;

	private:
		void putQueen(int);
		void printBoard(ostream &);
		void initializeBoard();

	public:
		ChessBoard();
		ChessBoard(int);
		~ChessBoard();

		void findSolutions();
};

#endif

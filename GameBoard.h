#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <utility>

const int NUM_PIECES = 12;
const int BOARD_SIZE = 8;
const int INVALID_COORD = -1;
const int EMPTY = 0;
const int SUCCESS = 1;
const int TAKE_PIECE = 2;
const int BLACK = 3;
const int RED = 4;
const int NONE = 5;

class Piece;


/*
* GameBoard Class, holds pieces and manages the movements 
* of pieces around the board
*/
class GameBoard
{
	public:
		GameBoard();
		~GameBoard();
		int pieceAtCoord(int row, int col) const;
		int selectPiece(int row, int col, int turnColor);
		void deselectPiece();
		bool pieceSelected() const;
		std::pair<int, int> selectedCoords() const;
		int attemptMove(int moveRow, int moveCol, bool jumpRestrict);
		bool jumpAvailable();
		int takePiece(int row, int col);
		int gameWon();

	private:
		int m_numBlack;
		int m_numRed;
		Piece* m_boardGrid[BOARD_SIZE][BOARD_SIZE];
		Piece* m_selectedPiece;

};

#endif // GAMEBOARD_H

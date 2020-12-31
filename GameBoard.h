#ifndef GAMEBOARD_H
#define GAMEBOARD_H

const int NUM_PIECES = 12;
const int BOARD_SIZE = 8;
const int INVALID_COORD = -1;
const int EMPTY = 0;
const int SUCCESS = 1;
const int BLACK = 2;
const int WHITE = 3;
const int NONE = 4;

class Piece;

class GameBoard
{
public:
	GameBoard();
	~GameBoard();
	int pieceAtCoord(int row, int col) const;
	int attemptMove(int pieceRow, int pieceCol, int moveRow, int moveCol);
	int takePiece(int row, int col);
	int gameWon();

private:
	//BlackPiece* m_blackPieces[NUM_PIECES];
	int m_numBlack;
	//WhitePiece* m_whitePieces[NUM_PIECES];
	int m_numWhite;
	Piece* m_boardGrid[BOARD_SIZE][BOARD_SIZE];

	friend class Test;


};

#endif // GAMEBOARD_H

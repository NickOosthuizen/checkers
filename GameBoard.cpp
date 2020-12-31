#include "GameBoard.h"
#include "Pieces.h"

/*
* Constructs checkers board
* and all of its pieces 
* for the game.
*/
GameBoard::GameBoard()
{
	m_numBlack = NUM_PIECES;
	m_numWhite = NUM_PIECES;
	int bRow = 0;
	int bCol = 1;
	int wRow = BOARD_SIZE - 1;
	int wCol = 0;

	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		for (int j = 0; j < BOARD_SIZE; ++j)
			m_boardGrid[i][j] = nullptr;
	}

	BlackPiece* blackPiece;
	WhitePiece* whitePiece;
	for (int i = 0; i < NUM_PIECES; ++i)
	{
		blackPiece = new BlackPiece(bRow, bCol, this);
		whitePiece = new WhitePiece(wRow, wCol, this);
		m_boardGrid[bRow][bCol] = blackPiece;
		m_boardGrid[wRow][wCol] = whitePiece;
		if (bCol == BOARD_SIZE - 1)
		{
			++bRow;
			--wRow;
			bCol = 0;
			wCol = 1;
		}
		else if (bCol == BOARD_SIZE - 2)
		{
			++bRow;
			--wRow;
			bCol = 1;
			wCol = 0;
		}
		else
		{
			bCol += 2;
			wCol += 2;
		}
	}
}

/*
* Delete any remaining Piece Objects
*/
GameBoard::~GameBoard()
{
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			if (m_boardGrid[i][j] != nullptr)
				delete m_boardGrid[i][j];
		}
	}
}

/*
* return the color of the piece at a board coordinate, or empty if
* none at the provided coordinates
*/
int GameBoard::pieceAtCoord(int row, int col) const
{
	if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE)
		return INVALID_COORD;
	else if (m_boardGrid[row][col] == nullptr)
		return EMPTY;
	else if (m_boardGrid[row][col]->pieceColor() == BLACK)
		return BLACK;
	else if (m_boardGrid[row][col]->pieceColor() == WHITE)
		return WHITE;
	else
		return INVALID_COORD;
}

/*
* Call a piece at given coordinates to move to a given set of coordinates
* If move succeeds, update board
* If move puts a piece at either end of the board, change it to a king piece
*/
int GameBoard::attemptMove(int pieceRow, int pieceCol, int moveRow, int moveCol)
{
	Piece* curPiece = m_boardGrid[pieceRow][pieceCol];
	int status;
	if (curPiece == nullptr)
		return INVALID_COORD;
	else
		status = curPiece->movePiece(moveRow, moveCol);
	if (status == SUCCESS) {
		if (moveRow == BOARD_SIZE - 1 || moveRow == 0)
		{
			King* newKing = new King(moveRow, moveCol, curPiece->pieceColor(), this);
			m_boardGrid[moveRow][moveCol] = newKing;
			m_boardGrid[pieceRow][pieceCol] = nullptr;
			delete curPiece;
		}
		else {
			m_boardGrid[moveRow][moveCol] = curPiece;
			m_boardGrid[pieceRow][pieceCol] = nullptr;
		}
		return SUCCESS;
	}
	else
		return INVALID_COORD;

}

/*
* Removes a piece at the given coordinates if there is a piece to take
*/
int GameBoard::takePiece(int row, int col)
{
	Piece* removePiece = m_boardGrid[row][col];
	if (removePiece == nullptr)
		return INVALID_COORD;

	int color = removePiece->pieceColor();

	if (color == BLACK)
	{
		--m_numBlack;
	}
	else if (color == WHITE)
	{
		--m_numWhite;
	}

	m_boardGrid[row][col] = nullptr;
	delete removePiece;

	return SUCCESS;

}


/*
* The game is won once one side has captured all other pieces
*/
int GameBoard::gameWon()
{
	if (m_numWhite == 0)
		return BLACK;
	else if (m_numBlack == 0)
		return WHITE;
	else
		return NONE;
}
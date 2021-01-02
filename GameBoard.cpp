#include "GameBoard.h"
#include "Pieces.h"
#include <utility>

/*
* Constructs checkers board
* and all of its pieces 
* for the game.
*/
GameBoard::GameBoard()
{
	m_numBlack = NUM_PIECES;
	m_numRed = NUM_PIECES;
	int bRow = 0;
	int bCol = 1;
	int rRow = BOARD_SIZE - 1;
	int rCol = 0;

	m_selectedPiece = nullptr;

	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		for (int j = 0; j < BOARD_SIZE; ++j)
			m_boardGrid[i][j] = nullptr;
	}

	Piece* blackPiece;
	Piece* redPiece;
	for (int i = 0; i < NUM_PIECES; ++i)
	{
		blackPiece = new Piece(bRow, bCol, BLACK, this);
		redPiece = new Piece(rRow, rCol, RED, this);
		m_boardGrid[bRow][bCol] = blackPiece;
		m_boardGrid[rRow][rCol] = redPiece;
		if (bCol == BOARD_SIZE - 1)
		{
			++bRow;
			--rRow;
			bCol = 0;
			rCol = 1;
		}
		else if (bCol == BOARD_SIZE - 2)
		{
			++bRow;
			--rRow;
			bCol = 1;
			rCol = 0;
		}
		else
		{
			bCol += 2;
			rCol += 2;
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
	else if (m_boardGrid[row][col]->pieceColor() == RED)
		return RED;
	else
		return INVALID_COORD;
}

/*
* Choice a piece to be the current active piece
* This piece is the one that move related functions are acting on
* A piece can only be selected if the turnColor matches the color of the piece
* trying to be selected
*/
int GameBoard::selectPiece(int row, int col, int turnColor)
{
	if (pieceAtCoord(row, col) == turnColor)
	{
		m_selectedPiece = m_boardGrid[row][col];
		return SUCCESS;
	}
	else
		return INVALID_COORD;
}

void GameBoard::deselectPiece()
{
	m_selectedPiece = nullptr;
}

bool GameBoard::pieceSelected() const 
{
	if (m_selectedPiece == nullptr)
		return false;
	else
		return true;
}


/*
* Display uses the coordinates of the selected piece to show 
* which piece is displayed
*/
std::pair<int, int> GameBoard::selectedCoords() const
{
	return m_selectedPiece->pieceCoordinates();
}

/*
* Call a piece at given coordinates to move to a given set of coordinates
* If move succeeds, update board
* If move puts a piece at either end of the board, change it to a king piece
*/
int GameBoard::attemptMove(int row, int col, bool jumpRestrict)
{
	int status;
	std::pair<int, int> originalCoords = m_selectedPiece->pieceCoordinates();
	status = m_selectedPiece->movePiece(row, col, jumpRestrict);
	if (status == SUCCESS || status == TAKE_PIECE) {
		if (row == BOARD_SIZE - 1 || row == 0)
			m_selectedPiece->makeKing();
		m_boardGrid[row][col] = m_selectedPiece;
		m_boardGrid[originalCoords.first ][originalCoords.second] = nullptr;
		
		return status;
	}
	else
		return INVALID_COORD;

}


/*
* Checks if from the selected piece if there is an adjacent piece
* with an empty space beyond it depending on the color of the piece
* If this is true, there is a jump possible for the selected piece
*/
bool GameBoard::jumpAvailable()
{
	int color = m_selectedPiece->pieceColor();
	std::pair<int, int> coords = m_selectedPiece->pieceCoordinates();
	int row = coords.first;
	int col = coords.second;
	int statusLeft, statusRight;
	if (m_selectedPiece->isKing() || color == BLACK)
	{
		statusLeft = pieceAtCoord(row + 1, col - 1);
		statusRight = pieceAtCoord(row + 1, col + 1);

		if (statusLeft != color && statusLeft != INVALID_COORD && statusLeft != EMPTY)
		{
			if (pieceAtCoord(row + 2, col - 2) == EMPTY)
				return true;
		}

		if (statusRight != color && statusRight != INVALID_COORD && statusLeft != EMPTY)
		{
			if (pieceAtCoord(row + 2, col + 2) == EMPTY)
				return true;
		}

	}

	if (m_selectedPiece->isKing() || color == RED)
	{
		statusLeft = pieceAtCoord(row - 1, col - 1);
		statusRight = pieceAtCoord(row - 1, col + 1);

		if (statusLeft != color && statusLeft != INVALID_COORD && statusLeft != EMPTY)
		{
			if (pieceAtCoord(row - 2, col - 2) == EMPTY)
				return true;
		}

		if (statusRight != color && statusRight != INVALID_COORD && statusRight != EMPTY)
		{
			if (pieceAtCoord(row - 2, col + 2) == EMPTY)
				return true;
		}

	}

	return false;
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
	else if (color == RED)
	{
		--m_numRed;
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
	if (m_numRed == 0)
		return BLACK;
	else if (m_numBlack == 0)
		return RED;
	else
		return NONE;
}
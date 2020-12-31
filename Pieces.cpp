#include "Pieces.h"
#include "GameBoard.h"
#include <utility>

/*
* Construct a piece object with coordinates, color, and board
*/
Piece::Piece(int row, int col, int color, GameBoard* board)
{
	m_row = row;
	m_col = col;
	m_color = color;
	m_board = board;
}

Piece::~Piece() 
{}

std::pair<int, int> Piece::pieceCoordinates() const
{
	return std::make_pair(m_row, m_col);
}

int Piece::pieceColor() const
{
	return m_color;
}

GameBoard* Piece::pieceBoard() const
{
	return m_board;
}

void Piece::updateCoordinates(int row, int col)
{
	m_row = row;
	m_col = col;
}

BlackPiece::BlackPiece(int row, int col, GameBoard* board)
	:Piece(row, col, BLACK, board)
{}

BlackPiece::~BlackPiece() 
{}

int BlackPiece::movePiece(int row, int col)
{
	if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE)
		return INVALID_COORD;

	std::pair<int, int> coord = pieceCoordinates();
	int curRow = coord.first;
	int curCol = coord.second;
	GameBoard* board = pieceBoard();

	if (curRow > row)
		return INVALID_COORD;
	if (curRow == row || curCol == col)
		return INVALID_COORD;
	if (board->pieceAtCoord(row, col) != EMPTY)
		return INVALID_COORD;

	if (row - curRow == 1 && abs(curCol - col) == 1)
	{
		updateCoordinates(row, col);
		return SUCCESS;
	}
	else if (row - curRow == 2 && abs(curCol - col) == 2)
	{
		int adjacentRow = curRow + 1;
		int adjacentCol;
		if (col > curCol)
			adjacentCol = curCol + 1;
		else
			adjacentCol = curCol - 1;

		if (board->pieceAtCoord(adjacentRow, adjacentCol) == WHITE)
		{
			board->takePiece(adjacentRow, adjacentCol);
			updateCoordinates(row, col);
			return SUCCESS;
		}
		else
			return INVALID_COORD;
	}
	return INVALID_COORD;
}

WhitePiece::WhitePiece(int row, int col, GameBoard* board)
	:Piece(row, col, WHITE, board)
{}

WhitePiece::~WhitePiece()
{}

int WhitePiece::movePiece(int row, int col)
{
	if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE)
		return INVALID_COORD;

	std::pair<int, int> coord = pieceCoordinates();
	int curRow = coord.first;
	int curCol = coord.second;
	GameBoard* board = pieceBoard();

	if (curRow < row)
		return INVALID_COORD;
	if (curRow == row || curCol == col)
		return INVALID_COORD;
	if (board->pieceAtCoord(row, col) != EMPTY)
		return INVALID_COORD;

	if (curRow - row == 1 && abs(curCol - col) == 1)
	{
		updateCoordinates(row, col);
		return SUCCESS;
	}

	else if (curRow - row == 2 && abs(curCol - col) == 2)
	{
		int adjacentRow = curRow - 1;
		int adjacentCol;
		if (col > curCol)
			adjacentCol = curCol + 1;
		else
			adjacentCol = curCol - 1;

		if (board->pieceAtCoord(adjacentRow, adjacentCol) == BLACK)
		{
			board->takePiece(adjacentRow, adjacentCol);
			updateCoordinates(row, col);
			return SUCCESS;
		}
		else
			return INVALID_COORD;
	}
	return INVALID_COORD;
}

King::King(int row, int col, int color, GameBoard* board)
	:Piece(row, col, color, board)
{}

int King::movePiece(int row, int col)
{
	if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE)
		return INVALID_COORD;

	std::pair<int, int> coord = pieceCoordinates();
	int curRow = coord.first;
	int curCol = coord.second;
	GameBoard* board = pieceBoard();

	if (curRow == row || curCol == col)
		return INVALID_COORD;
	if (board->pieceAtCoord(row, col) != EMPTY)
		return INVALID_COORD;

	if (abs(curRow - row) == 1 && abs(curCol - col) == 1)
	{
		updateCoordinates(row, col);
		return SUCCESS;
	}

	else if (abs(curRow - row) == 2 && abs(curCol - col) == 2)
	{
		int adjacentRow;
		int adjacentCol;

		if (row > curRow)
			adjacentRow = curRow + 1;
		else
			adjacentRow = curRow - 1;

		if (col > curCol)
			adjacentCol = curCol + 1;
		else
			adjacentCol = curCol - 1;

		if (board->pieceAtCoord(adjacentRow, adjacentCol) != pieceColor())
		{
			board->takePiece(adjacentRow, adjacentCol);
			updateCoordinates(row, col);
			return SUCCESS;
		}
		else
			return INVALID_COORD;
	}
	return INVALID_COORD;
	
}

King::~King()
{}



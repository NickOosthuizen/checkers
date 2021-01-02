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
	m_king = false;
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

void Piece::makeKing()
{
	m_king = true;
}

bool Piece::isKing() const
{
	return m_king;
}

void Piece::updateCoordinates(int row, int col)
{
	m_row = row;
	m_col = col;
}

/*
* Changes the coordinates of the piece if the given row and column are valid
* jump restrict means that only a jump move is allowed in the given function call
* If a piece is taken in the move, TAKE_PIECE is returned, but if just a successful move occurs,
* SUCCESS is returned
*/
int Piece::movePiece(int row, int col, bool jumpRestrict)
{
	if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE)
		return INVALID_COORD;

	std::pair<int, int> coord = pieceCoordinates();
	int curRow = coord.first;
	int curCol = coord.second;
	int adjacentColor;

	if (!m_king)
		if (curRow > row && m_color == BLACK || curRow < row && m_color == RED)
			return INVALID_COORD;
	if (curRow == row || curCol == col)
		return INVALID_COORD;
	if (m_board->pieceAtCoord(row, col) != EMPTY)
		return INVALID_COORD;
	
	if (!jumpRestrict)
	{
		if (abs(curRow - row) == 1 && abs(curCol - col) == 1)
		{
			updateCoordinates(row, col);
			return SUCCESS;
		}
	}

	if (abs(curRow - row) == 2 && abs(curCol - col) == 2)
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

		adjacentColor = m_board->pieceAtCoord(adjacentRow, adjacentCol);
		if (adjacentColor != m_color && adjacentColor != EMPTY)
		{
			m_board->takePiece(adjacentRow, adjacentCol);
			updateCoordinates(row, col);
			return TAKE_PIECE;
		}
		else
			return INVALID_COORD;
	}
	return INVALID_COORD;


}

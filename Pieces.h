#ifndef PIECES_H
#define PIECES_H

#include <utility>

class GameBoard;

/*
* General Piece class
*/
class Piece
{
	public:
		Piece(int startRow, int startCol, int color, GameBoard* board);
		~Piece();
		std::pair<int, int> pieceCoordinates() const;
		int pieceColor() const;
		void makeKing();
		bool isKing() const;
		void updateCoordinates(int row, int col);
		int movePiece(int row, int col, bool jumpRestrict);

	private:
		int m_row, m_col, m_color;
		bool m_king;
		GameBoard* m_board;
};

#endif // PIECES_H


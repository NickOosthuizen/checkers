#ifndef PIECES_H
#define PIECES_H

#include <utility>

class GameBoard;

/*
* General Piece class, most 
*/
class Piece
{
	public:
		Piece(int startRow, int startCol, int color, GameBoard* board);
		virtual ~Piece();
		std::pair<int, int> pieceCoordinates() const;
		int pieceColor() const;
		GameBoard* pieceBoard() const;
		void updateCoordinates(int row, int col);
		virtual int movePiece(int row, int col) = 0;

	private:
		int m_row, m_col, m_color;
		GameBoard* m_board;
};


class BlackPiece : public Piece
{
	public:
		BlackPiece(int startRow, int startCol, GameBoard* board);
		virtual ~BlackPiece();
		virtual int movePiece(int row, int col);

	private:

};

class WhitePiece : public Piece
{
	public:
		WhitePiece(int startRow, int startCol, GameBoard* board);
		virtual ~WhitePiece();
		virtual int movePiece(int row, int col);

	private: 

};



class King : public Piece
{
	public:
		King(int startRow, int startCol, int color, GameBoard* board);
		virtual ~King();
		virtual int movePiece(int row, int col);

	private:

};

#endif // PIECES_H

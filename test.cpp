#include <iostream>
#include <assert.h>
#include <utility>
#include "GameBoard.h"
#include "Pieces.h"
#include "Test.h"
#include "GameController.h"

Test::Test(GameBoard* board)
{
	m_testBoard = board;
}

Test::~Test()
{}

/*
* color = 0 for black pieces 
* color = 1 for white pieces
* I got lazy writing out the asserts
*/

void Test::constructionTest() const
{
	assert(m_testBoard->pieceAtCoord(0, 0) == EMPTY);
	assert(m_testBoard->pieceAtCoord(0, 1) == BLACK);
	assert(m_testBoard->pieceAtCoord(0, 7) == BLACK);
	assert(m_testBoard->pieceAtCoord(2, 1) == BLACK);
	assert(m_testBoard->pieceAtCoord(2, 7) == BLACK);
	assert(m_testBoard->pieceAtCoord(3, 0) == EMPTY);
	assert(m_testBoard->pieceAtCoord(7, 0) == WHITE);
	assert(m_testBoard->pieceAtCoord(7, 6) == WHITE);
	assert(m_testBoard->pieceAtCoord(5, 6) == WHITE);
	assert(m_testBoard->m_numBlack == 12);
	assert(m_testBoard->m_numWhite == 12);
	assert(m_testBoard->pieceAtCoord(-1, 6) == INVALID_COORD);
	assert(m_testBoard->pieceAtCoord(8, 0) == INVALID_COORD);


}

void Test::moveTest() const
{
	assert(m_testBoard->attemptMove(4, 3, 5, 4) == INVALID_COORD);
	assert(m_testBoard->attemptMove(0, 1, 0, 2) == INVALID_COORD);
	assert(m_testBoard->attemptMove(0, 1, 1, 2) == INVALID_COORD);
	assert(m_testBoard->attemptMove(5, 0, 6, 1) == INVALID_COORD);
	assert(m_testBoard->attemptMove(7, 0, 8, 1) == INVALID_COORD);
	assert(m_testBoard->attemptMove(7, 0, 8, -1) == INVALID_COORD);
	assert(m_testBoard->attemptMove(5, 6, 6, 5) == INVALID_COORD);
	

	constructionTest();

	assert(m_testBoard->attemptMove(5, 0, 4, 1) == SUCCESS);
	assert(m_testBoard->pieceAtCoord(4, 1) == WHITE);
	assert(m_testBoard->attemptMove(4, 1, 3, 0) == SUCCESS);
	assert(m_testBoard->pieceAtCoord(3, 0) == WHITE);
	assert(m_testBoard->attemptMove(3, 0, 4, 1) == INVALID_COORD);
	assert(m_testBoard->pieceAtCoord(3, 0) == WHITE);
	assert(m_testBoard->attemptMove(3, 0, 2, 1) == INVALID_COORD);
	assert(m_testBoard->pieceAtCoord(3, 0) == WHITE);

	assert(m_testBoard->attemptMove(2, 3, 3, 4) == SUCCESS);
	assert(m_testBoard->pieceAtCoord(3, 4) == BLACK);
	assert(m_testBoard->attemptMove(3, 4, 2, 3) == INVALID_COORD);
	assert(m_testBoard->pieceAtCoord(3, 4) == BLACK);
	assert(m_testBoard->attemptMove(3, 4, 4, 5) == SUCCESS);
	assert(m_testBoard->pieceAtCoord(4, 5) == BLACK);
	assert(m_testBoard->attemptMove(5, 4, 3, 6) == SUCCESS);
	assert(m_testBoard->pieceAtCoord(3, 6) == WHITE);
	assert(m_testBoard->pieceAtCoord(4, 5) == EMPTY);
	assert(m_testBoard->m_numBlack == 11);

}

int main()
{
	GameBoard* board = new GameBoard;
	//Test tester(board);
	GameController controller(board);
	//controller.displayBoard();
	//tester.constructionTest();
	//tester.moveTest();
	//controller.displayBoard();
	controller.playGame();
	
}


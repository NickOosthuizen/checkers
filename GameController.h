#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <utility>

class GameBoard;

class GameController
{
	public:
		GameController(GameBoard* board);
		~GameController();
		void displayBoard() const;
		void playGame();
		int getMove(int& currentRow, int& currentCol, int& moveRow, int& moveCol);

	private:
		GameBoard* m_board;

};

#endif


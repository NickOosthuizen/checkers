#include "GameController.h"
#include "GameBoard.h"

int main()
{
	GameBoard board;
	GameController game(&board);
	game.playGame();
}
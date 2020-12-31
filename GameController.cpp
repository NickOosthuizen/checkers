#include "GameController.h"
#include "GameBoard.h"
#include <iostream>
#include <utility>
#include <string>
#include <cctype>

void clearScreen();

GameController::GameController(GameBoard* board)
{
	m_board = board;
}

GameController::~GameController()
{
	delete m_board;
}

void GameController::displayBoard() const
{
	std::cout << "  ";
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		std::cout << i;
		std::cout << '|';
	}
	std::cout << std::endl;
	std::cout << "  ";
	for (int i = 0; i < (BOARD_SIZE) * 2 ; ++i)
		std::cout << '-';
	std::cout << std::endl;
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		std::cout << i;
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			std::cout << '|';
			if (m_board->pieceAtCoord(i, j) == EMPTY)
				std::cout << ' ';
			else if (m_board->pieceAtCoord(i, j) == BLACK)
				std::cout << 'B';
			else if (m_board->pieceAtCoord(i, j) == WHITE)
				std::cout << 'W';

		}
		std::cout << '|';
		std::cout << std::endl;
		std::cout << "  ";
		for (int i = 0; i < BOARD_SIZE * 2 ; ++i)
			std::cout << '-';
		std::cout << std::endl;
	}
}

void GameController::playGame()
{
	int currentRow = -1;
	int currentCol = -1;
	int moveRow = -1;
	int moveCol = -1;
	while (m_board->gameWon() == NONE)
	{
		clearScreen();
		displayBoard();
		if (getMove(currentRow, currentCol, moveRow, moveCol) == SUCCESS)
		{
			m_board->attemptMove(currentRow, currentCol, moveRow, moveCol);
		}
	}
}

int GameController::getMove(int& currentRow, int& currentCol, int& moveRow, int& moveCol)
{
	std::string input;
	std::getline(std::cin, input);

	for (int i = 0; i < 4; ++i)
	{
		if (!isdigit(input[i]))
			return INVALID_COORD;
	}

	currentRow = input[0] - '0';
	currentCol = input[1] - '0';
	moveRow = input[2] - '0';
	moveCol = input[3] - '0';

	return SUCCESS;
}

#pragma warning(disable : 4005)
#include <windows.h>

void clearScreen()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	COORD upperLeft = { 0, 0 };
	DWORD dwCharsWritten;
	FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
		&dwCharsWritten);
	SetConsoleCursorPosition(hConsole, upperLeft);
}
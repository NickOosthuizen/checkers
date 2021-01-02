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


/*
* Draws the board based off the current state of the gameboard grid
* If a piece is selected, it will have a blue background
* Red pieces are colored red 
* Color outputs use ANSI color codes
* \033 = ESC character
* [num;num;...m = specify color codes
* 44: blackground blue
* 31: foreground red
*/
void GameController::displayBoard() const
{
	int selectedRow = -1;
	int selectedCol = -1;
	if (m_board->pieceSelected())
	{
		selectedRow = m_board->selectedCoords().first;
		selectedCol = m_board->selectedCoords().second;
	}

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
			{
				if (i == selectedRow && j == selectedCol)
					std::cout << "\033[44mB\033[0m";
				else
					std::cout << 'B';
			}
			else if (m_board->pieceAtCoord(i, j) == RED)
			{
				if (i == selectedRow && j == selectedCol)
					std::cout << "\033[31;44mR\033[0m";
				else
					std::cout << "\033[31mR\033[0m";
			}

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
	int row = -1;
	int col = -1;
	bool blackTurn = true;
	bool jumpRestrict = false;
	int turnColor = BLACK;
	int status = INVALID_COORD;
	while (m_board->gameWon() == NONE)
	{
		clearScreen();
		displayBoard();

		if (blackTurn)
			turnColor = BLACK;
		else
			turnColor = RED;

		if (getSelection(row, col) == SUCCESS)
		{
			if (jumpRestrict)
			{
				m_board->attemptMove(row, col, jumpRestrict);
				if (m_board->jumpAvailable())
					continue;
				else
				{
					jumpRestrict = false;
					m_board->deselectPiece();
					blackTurn = !blackTurn;
				}
			}
			else if (m_board->pieceAtCoord(row, col) == turnColor)
				m_board->selectPiece(row, col, turnColor);
			else if (m_board->pieceSelected())
			{
				status = m_board->attemptMove(row, col, jumpRestrict);
				if (status == SUCCESS)
				{
					m_board->deselectPiece();
					blackTurn = !blackTurn;
				}
				else if (status == TAKE_PIECE)
				{
					if (m_board->jumpAvailable())
						jumpRestrict = true;
					else
					{
						m_board->deselectPiece();
						blackTurn = !blackTurn;
					}
				}
			}
		}
		
	}
}


/*
* Valid inputs are just 2 numbers in the form row,col
* In input there is no comma, just the numbers
*/
int GameController::getSelection(int& row, int& col)
{
	std::string input;
	std::getline(std::cin, input);

	if (input.size() != 2 || !isdigit(input[0]) || !isdigit(input[1]))
		return INVALID_COORD;

	row = input[0] - '0';
	col = input[1] - '0';

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
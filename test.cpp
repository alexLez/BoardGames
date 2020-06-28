#include <iostream>
#include <algorithm>


enum state
{
	empty = 0, player, ai
};

void drawBoard(const int board[9])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			char square; 
			if (board[3 * i + j] == empty)
				square = ' ';
			else if (board[3 * i + j] == player)
				square = 'O';
			else
				square = 'X';

			std::cout << square;
			if (j!=2)
				std::cout << '|';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void drawBoardTemplate(void)
{
	std::cout << "Layout:" << std::endl;
	for (int i = 0; i < 9; i++)
	{
		std::cout << i+1;

		if (i % 3 == 2)
			std::cout << std::endl;
		else
			std::cout << "|";
	}
}

int EvaluateBoard(const int board[9]) 
{
	//checking rows for a victory
	for (int i = 0; i < 9; i+=3)
	{
		if (board[i] == board[i+1] && board[i+1] == board[i+2])
		{
			if (board[i] == ai)
				return 5;
			if (board[i] == player)
				return -5;
		}
	}

	//checking cols for a victory
	for (int i = 0; i < 3; i++)
	{
		if (board[i] == board[i + 3] && board[i + 3] == board[i + 6])
		{
			if (board[i] == ai)
				return 5;
			if (board[i] == player)
				return -5;
		}
	}

	//checking diagonals for a vicotry

	if (board[0] == board[4] && board[4] == board[8])
	{
		if (board[0] == ai)
			return 5;
		if (board[0] == player)
			return -5;
	}

	if (board[2] == board[4] && board[4] == board[6])
	{
		if (board[2] == ai)
			return 5;
		if (board[2] == player)
			return -5;
	}

	else
		return 0;
}

bool isGameOver(const int board[9])
{
	for (int i = 0; i < 9; i++)
	{
		if (board[i] == empty)
			return false;
	}
	return true;
}

int minimax(int board[9], bool maximise)
{
	int score = EvaluateBoard(board);

	if (score == 5)
		return score;

	if (score == -5)
		return score;

	if (isGameOver(board))
		return 0;

	if (maximise)
	{
		int best = -100;

		for (int i = 0; i < 9; i++)
		{
			if (board[i] == empty)
			{
				board[i] = ai;
				best = std::max(best, minimax(board, !maximise));
				board[i] = empty;
			}
		}
		return best;
	}

	if (!maximise)
	{
		int best = 100;

		for (int i = 0; i < 9; i++)
		{
			if (board[i] == empty)
			{
				board[i] = player;
				best = std::min(best, minimax(board, !maximise));
				board[i] = empty;
			}
		}
		return best;
	}
}

int findBestMove(int board[9])
{
	int best=-1000, pos;
	int score;

	for (int i = 0; i < 9; i++)
	{
		if (board[i] == empty)
		{
			board[i] = ai;
			score = minimax(board, false);
			if (score > best)
			{
				best = score;
				pos = i;
			}
			board[i] = empty;
		}
	}
	return pos;
}

bool setup(int b[9])
{
	for (int i = 0; i < 9; i++)
	{
		b[i] = empty;
	}

	drawBoardTemplate();
	std::cout << "Would you like to go first? 1/0" << std::endl;
	bool start;

	std::cin >> start;


	return start;

}

void playerMove(int b[9])
{
	std::cout << "Where would you like to move, 1-9" << std::endl;
	bool moved = false;
	int a;


	while (!moved)
	{

		std::cin >> a;

		if (b[a - 1] != empty)
		{
			std::cout << "Square already taken, enter again" << std::endl;
		}
		else
		{
			b[a - 1] = player;
			moved = true;
		}
	}
}

int main() {

	int b[9];
	bool usermove = setup(b);
	int aiMove;
	bool gameover = false;

	
	while (!gameover)
	{

		if (usermove)
		{
			playerMove(b);
		}
		else
		{
			aiMove = findBestMove(b);
			b[aiMove] = ai;
		}

		drawBoard(b);
		if (EvaluateBoard(b) == 5 || isGameOver(b) || EvaluateBoard(b) == -5) 
			gameover=true;
		
		usermove =!usermove;
	}
	
	drawBoard(b);
	std::cout << "Gameover" << std::endl;
	std::cin.get();
	return 0;
}

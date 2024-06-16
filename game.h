#pragma once
#include <string>
#include <vector>

struct Position
{
	int row;
	int column;
};

struct HangmanPart
{
	Position position;
	char c;
};

class Game
{
	enum class GameState
	{
		START,
		UPDATE,
		FINISH
	};

public:
	static const int COLUMNS = 9;
	static const int ROWS = 8;
	static const int MAX_ELEMENTS = COLUMNS * ROWS;

	void OnInit();
	void OnInput();
	bool OnUpdate(float deltaTime);
	void OnRender();
	void OnShutdown();

private:
	std::string m_word;
	std::vector<std::string> m_wordsPool = { "kolor", "silnik", "wzorzec", "silnie", "kanapka" };
	std::vector<bool> m_guessedLetters;
	GameState m_gameState = GameState::START;
	int m_failAnswerCount;
	int m_answerFail = false;
	std::vector<std::vector<HangmanPart>> m_hangman{ 
		{
			HangmanPart{Position{7,0}, '/'}
		},
		{
			HangmanPart{Position{7,2}, '\\'}
		},
		{
			HangmanPart{Position{6,1}, '|'},
			HangmanPart{Position{5,1}, '|'},
		},
		{
			HangmanPart{Position{4,1}, '|'},
			HangmanPart{Position{3,1}, '|'},
		},
		{
			HangmanPart{Position{2,1}, '|'},
			HangmanPart{Position{1,1}, '|'},
		},
		{
			HangmanPart{Position{0,2}, '_'},
			HangmanPart{Position{0,3}, '_'},
			HangmanPart{Position{0,4}, '_'},
			HangmanPart{Position{0,5}, '_'},
			HangmanPart{Position{0,6}, '_'},
		},
		{
			HangmanPart{Position{1,6}, '|'},
		},
		{
			HangmanPart{Position{2,6}, 'O'},
		},
		{
			HangmanPart{Position{3,6}, '|'},
			HangmanPart{Position{4,6}, '|'},
		},
		{
			HangmanPart{Position{3,5}, '\\'},
		},
		{
			HangmanPart{Position{3,7}, '/'},
		},
		{
			HangmanPart{Position{5,5}, '/'},
		},
		{
			HangmanPart{Position{5,7}, '\\'},
		},
	};
	std::vector<char> m_hangmanBox;
};

#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

void Game::OnInit()
{
	m_guessedLetters.clear();
	srand(std::time(NULL));
	int randomIndex = rand() % m_wordsPool.size();
	m_word = m_wordsPool[randomIndex];

	m_hangmanBox.reserve(Game::MAX_ELEMENTS);

	for (int row = 0; row < Game::ROWS; ++row) {
		for (int column = 0; column < Game::COLUMNS; ++column) {
			m_hangmanBox.push_back(' ');
		}
	}

	m_failAnswerCount = 0;
}

void Game::OnInput()
{

}

bool Game::OnUpdate(float deltaTime)
{
	if (m_answerFail) {
		for (int i = 0; i < m_hangman[m_failAnswerCount].size(); ++i) {
			int index = m_hangman[m_failAnswerCount][i].position.row * Game::COLUMNS + m_hangman[m_failAnswerCount][i].position.column;
			m_hangmanBox[index] = m_hangman[m_failAnswerCount][i].c;
		}
		++m_failAnswerCount;
		m_answerFail = false;
	}

	return false;
}

void Game::OnRender()
{
	for (int i = 0; i < Game::ROWS; ++i) {
		for (int j = 0; j < Game::COLUMNS; ++j) {
			std::cout << m_hangmanBox[i * Game::COLUMNS + j];
		}
		std::cout << std::endl;
	}
}

void Game::OnShutdown()
{
	m_guessedLetters.clear();
}

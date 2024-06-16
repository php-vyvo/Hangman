#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <algorithm>

const std::string Game::FILE_PATH = "words.txt";

void Game::OnInit()
{
	loadWordsFromFile();
	selectWord();
	prepareGuessedLetters();
	prepareHangman();

	m_failAnswerCount = 0;
	m_gameState = GameState::UPDATE;
}

void Game::OnInput(char inputKey)
{
	if (inputKey != EMPTY_KEY) {
		m_keyState = KeyPressed{ true, (char)toupper(inputKey) };

		m_gameState = GameState::UPDATE;
	}
}

bool Game::OnUpdate(float deltaTime)
{
	updateAfterKeyPressed();

	if (m_gameState == GameState::FINISH) {
		return true;
	}

	return false;
}

void Game::OnRender()
{
	if (m_gameState != GameState::UPDATE && m_gameState != GameState::FINISH) {
		return;
	}

	std::system("cls");
	
	for (int i = 0; i < Game::ROWS; ++i) {
		for (int j = 0; j < Game::COLUMNS; ++j) {
			std::cout << m_hangmanBox[i * Game::COLUMNS + j];
		}
		std::cout << std::endl;
	}

	std::cout << "Haslo do odgadniecia: ";
	for (int i = 0; i < m_word.size(); ++i) {
		if (!m_guessedLetters[i]) {
				std::cout << " _ ";
		} else {
			std::cout << " " << m_word[i] << " ";
		}
	}
	
	if (m_gameState != GameState::FINISH) {
		std::cout << std::endl << "Podaj litere hasla: ";
	} else if (m_winner) {
		std::cout << std::endl << "Gratulacje wygrales!. Wcisnij dowolny klawisz.";
	} else {
		std::cout << std::endl << "Przegrales. Moze innym razem. Wcisnij dowolny klawisz.";
	}
	
	m_gameState = GameState::START;
}

void Game::OnShutdown()
{
	m_guessedLetters.clear();
}

void Game::loadWordsFromFile()
{
	m_wordsPool.clear();
	
		std::ifstream wordsStream(FILE_PATH);
	
		std::string word;
	
		while (std::getline(wordsStream, word)) {
		m_wordsPool.push_back(word);
	}
	
	wordsStream.close();
}

void Game::selectWord()
{
	srand(std::time(NULL));
	int randomIndex = rand() % m_wordsPool.size();
	m_word = m_wordsPool[randomIndex];
	std::transform(m_word.begin(), m_word.end(), m_word.begin(), ::toupper);
}

void Game::updateAfterKeyPressed()
{
	if (m_keyState.state) {
		int trueAnswer = checkCurrentAnswer();

		onFailAnswer();
		
		if (trueAnswer == m_word.size()) {
			m_winner = true;
			m_gameState = GameState::FINISH;
		}

		if (m_failAnswerCount > m_hangman.size() - 1) {
			m_gameState = GameState::FINISH;
		}

		m_keyState.state = false;
	}
}

void Game::onFailAnswer()
{
	if (m_answerFail) {
		for (int i = 0; i < m_hangman[m_failAnswerCount].size(); ++i) {
			int index = m_hangman[m_failAnswerCount][i].position.row * Game::COLUMNS + m_hangman[m_failAnswerCount][i].position.column;
			m_hangmanBox[index] = m_hangman[m_failAnswerCount][i].c;
		}
		++m_failAnswerCount;
		m_answerFail = false;
	}
}

int Game::checkCurrentAnswer()
{
	int trueAnswer = 0;
	m_answerFail = true;
			
	for (int i = 0; i < m_word.size(); ++i) {
		if (m_word[i] == m_keyState.key && !m_guessedLetters[i]) {
			m_guessedLetters[i] = true;
			m_answerFail = false;
		}
				
		if (m_guessedLetters[i]) {
			++trueAnswer;
		}
	}
			
	return trueAnswer;
}

void Game::prepareGuessedLetters()
{
	m_guessedLetters.clear();
	m_guessedLetters.reserve(m_word.size());
	for (int i = 0; i < m_word.size(); ++i) {
		m_guessedLetters.push_back(false);
	}
}

void Game::prepareHangman()
{
	m_hangmanBox.clear();
	m_hangmanBox.reserve(Game::MAX_ELEMENTS);
	for (int i = 0; i < Game::MAX_ELEMENTS; ++i) {
		m_hangmanBox.push_back(' ');
	}
}

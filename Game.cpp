#include "Game.h"

using namespace WordleConstants;

Game::Game(Difficulty diff)
{
	selectWord(diff);
}

Game::~Game()
{
}

void Game::selectWord(Difficulty diff)
{
	// Define the word length ranges for each difficulty level
	int minLength = 0;
	int maxLength = 0;

	switch (diff) {
	case Easy:
		maxLength = 4;
		break;
	case Medium:
		minLength = 5;
		maxLength = 6;
		break;
	case Hard:
		minLength = 7;
		maxLength = 1000;
	}

	// Load the resource containing words
	QFile file("WordSet.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return;
	}

	QTextStream in(&file);
	while (!in.atEnd()) {
		QString word = in.readLine().trimmed();
		// Filter the words based on the selected difficulty
		if (word.length() >= minLength && word.length() <= maxLength) {
			m_filteredWords.append(word);
		}
	}

	file.close();

	QRandomGenerator::securelySeeded();

	// Randomly select a word from the loaded words
	int index = QRandomGenerator::global()->bounded(0, m_filteredWords.size());
	m_selectedWord = m_filteredWords[index];

	// Clean up filtered words to contain only words of same length as the game's word
	m_filteredWords.erase(std::remove_if(m_filteredWords.begin(), m_filteredWords.end(),
		[this](const QString& s) { return s.size() != this->m_selectedWord.size(); }), m_filteredWords.end());
}

Game::GuessResult Game::checkGuess(const QString& guess)
{
	// Compare the player's guess with the selected word
	if (!m_filteredWords.contains(guess)) return InvalidGuess;
	else if (!(guess.toLower() == m_selectedWord)) return WrongGuess;
	else return CorrectGuess;
}



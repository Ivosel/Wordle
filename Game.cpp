#include "Game.h"

Game::Game(int difficulty)
{
	selectWord(difficulty);
}

Game::~Game()
{
}

void Game::selectWord(int difficulty)
{
	// Load the resource containing words
	QFile file("WordSet.txt");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return;
	}

	QTextStream in(&file);
	QStringList words;
	while (!in.atEnd()) {
		QString word = in.readLine().trimmed();
		words.append(word);
	}

	file.close();

	// Define the word length ranges for each difficulty level
	int minLength = 0;
	int maxLength = 0;
	if (difficulty == 4) {
		maxLength = 4;
	}
	else if (difficulty == 6) {
		minLength = 5;
		maxLength = 6;
	}
	else if (difficulty == 8) {
		minLength = 7;
		maxLength = 100;
	}

	// Filter the words based on the selected difficulty
	for (const QString& word : words) {
		if (word.length() >= minLength && word.length() <= maxLength) {
			m_filteredWords.append(word);
		}
	}

	QRandomGenerator::securelySeeded();

	// Randomly select a word from the loaded words
	int index = QRandomGenerator::global()->bounded(0, m_filteredWords.size());
	m_selectedWord = m_filteredWords[index];

	// Clean up filtered words to contain only words of same length as the game's word
	m_filteredWords.erase(std::remove_if(m_filteredWords.begin(), m_filteredWords.end(),
		[this](const QString& s) { return s.size() < this->m_selectedWord.size(); }), m_filteredWords.end());
}

int Game::checkGuess(const QString& guess)
{
	// Compare the player's guess with the selected word
	if (!m_filteredWords.contains(guess)) return 2;
	else if (!(guess.toLower() == m_selectedWord)) return 1;
	else return 0;
}



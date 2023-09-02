#pragma once

#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>
#include <QTime>
#include "Constants.h"

class Game
{
public:
	enum GuessResult {
		CorrectGuess,
		WrongGuess,
		InvalidGuess
	};

	Game(WordleConstants::Difficulty diff);
	~Game();
	void selectWord(WordleConstants::Difficulty diff);
	GuessResult checkGuess(const QString& guess);
	QString m_selectedWord;

private:
	QStringList m_filteredWords;
};
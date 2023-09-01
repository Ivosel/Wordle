#pragma once

#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>
#include <QTime>

class Game
{
public:
	enum GuessResult {
		CorrectGuess,
		LastChanceWrongGuess,
		InvalidGuess
	};

	Game(int difficulty);
	~Game();
	void selectWord(int difficulty);
	GuessResult checkGuess(const QString& guess);
	QString m_selectedWord;

private:
	QStringList m_filteredWords;
};
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
	Game(int difficulty);
	~Game();
	void selectWord(int difficulty);
	int checkGuess(const QString& guess);
	QString m_selectedWord;

private:
	QStringList m_filteredWords;
};
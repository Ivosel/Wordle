#pragma once

#ifndef UISTRINGS_H
#define UISTRINGS_H

#include <QString>

namespace UIStrings {
	const QString EasyButton = "Easy (up to 4 letters)";
	const QString MediumButton = "Medium (5-6 letters)";
	const QString HardButton = "Hard (7 or more letters)";
	const QString WrongLetter = "Wrong letter";
	const QString CorrectLetter = "Correct letter";
	const QString CorrPosLetter = "Correct letter and position";
	const QString Legend = "Legend:";
	const QString Title = "WORDLE";
	const QString GameDifficulty = "Select Game Difficulty:";
	const QString KeyboardLetters = "QWERTZUIOPASDFGHJKLYXCVBNM";
	const QString GameEndNoButton = "Quit";
	const QString GameEndQuestion = "Start a new game?";
	const QString Victory = "Congratulations!";
	const QString Defeat = "Better luck next time";
}

#endif
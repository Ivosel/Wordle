#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include "ui_Wordle.h"
#include "Game.h"
#include "KeyboardGrid.h"
#include "GuessingGrid.h"
#include "Styles.h"
#include "Constants.h"
#include "UIStrings.h"

class Wordle : public QMainWindow
{
	Q_OBJECT

public:
	Wordle(QWidget* parent = nullptr);
	~Wordle();

private slots:
	void onEasyClicked();
	void onMediumClicked();
	void onHardClicked();
	void onExitTriggered();
	void onNewGameTriggered();

private:
	void SetUpSelectionScreen();
	void SetUpGame(WordleConstants::Difficulty diff);
	void CreateButtons();

	Ui::WordleClass ui;
	Game* m_newGame;
	GuessingGrid* m_customGrid;
	KeyboardGrid* m_letterGrid;
};

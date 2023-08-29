#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include "ui_Wordle.h"
#include "Game.h"
#include "KeyboardGrid.h"
#include "MyGrid.h"
#include "Styles.h"

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
	void SetUpGame(int difficulty);
	void CreateButtons();

	Ui::WordleClass ui;
	Game* m_newGame;
	MyGrid* m_customGrid;
	KeyboardGrid* m_letterGrid;
};

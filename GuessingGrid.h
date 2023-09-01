#pragma once

#include <QWidget>
#include <QGridLayout>
#include <qevent.h>
#include <qmessagebox.h>
#include "Game.h"
#include "KeyboardGrid.h"

class GuessingGrid : public QWidget
{
	Q_OBJECT

public:
	GuessingGrid(Game* gameInstance, KeyboardGrid* letterGrid, int numColumns, QWidget* parent = nullptr);
	~GuessingGrid();

signals:
	void yesClicked();
	void noClicked();

private:
	void createLabels();
	void updateLabelBackgroundColors(const QString& guess);
	void keyPressEvent(QKeyEvent* event);

	QGridLayout* m_layout;
	Game* m_gameInstance;
	KeyboardGrid* m_letterGrid;
	std::vector<std::vector<QLabel*>> m_labels;

	int m_numColumns;
	int m_numRows;
	int m_currentRow;
	int m_currentCol;
};
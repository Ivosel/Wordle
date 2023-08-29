#pragma once

#include <QWidget>
#include <QGridLayout>
#include <qevent.h>
#include <qmessagebox.h>
#include "MyLabel.h"
#include "Game.h"
#include "KeyboardGrid.h"

class MyGrid : public QWidget
{
	Q_OBJECT

public:
	MyGrid(Game* gameInstance, KeyboardGrid* letterGrid, int numColumns, QWidget* parent = nullptr);
	~MyGrid();

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
	std::vector<std::vector<MyLabel*>> m_labels;

	int m_numColumns;
	int m_numRows;
	int m_currentRow;
	int m_currentCol;
};

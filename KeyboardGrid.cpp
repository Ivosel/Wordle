#include "KeyboardGrid.h"

KeyboardGrid::KeyboardGrid(QWidget* parent)
	: QWidget(parent)
{
	m_layout = new QGridLayout(this);
	createButtons();
	setLayout(m_layout);
}

KeyboardGrid::~KeyboardGrid()
{}

void KeyboardGrid::createButtons()
{
	int row = 0;
	int col = 0;
	QString keyboardLetters = UIStrings::KeyboardLetters;

	// Create buttons representing the keyboard, add them to the layout and the button list member
	for (auto c : keyboardLetters) {
		QLabel* label = new QLabel(c);
		m_letterLabels.append(label);
		m_layout->addWidget(label, row, col);
		label->setFixedSize(WordleConstants::KeyDimension, WordleConstants::KeyDimension);
		label->setAlignment(Qt::AlignCenter);
		label->setStyleSheet(AVAILABLE_LETTER_LABEL);

		col++;
		if (label->text() == "P" || label->text() == "L") {
			col = 0;
			row++;
		}
	}
}

void KeyboardGrid::updateButtons(QString guess)
{
	// Update the appearance of the buttons representing the keyboard if they have been used in a player's guess
	QString keyboardLetters = UIStrings::KeyboardLetters.toLower();

	for (int i = 0; i < keyboardLetters.length(); ++i) {
		if (guess.contains(keyboardLetters[i])) m_letterLabels[i]->setStyleSheet(USED_LETTER_LABEL);
	}
}

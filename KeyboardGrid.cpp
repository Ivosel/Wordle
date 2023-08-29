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
	m_alphabet = QStringList() << "Q" << "W" << "E" << "R" << "T" << "Z" << "U" << "I" << "O" << "P" <<
		"A" << "S" << "D" << "F" << "G" << "H" << "J" << "K" << "L" <<
		"Y" << "X" << "C" << "V" << "B" << "N" << "M";

	int row = 0;
	int col = 0;

	// Create buttons representing the keyboard, add them to the layout and the button list member
	for (const QString& letter : m_alphabet) {
		QPushButton* button = new QPushButton(letter);
		m_letterButtons.append(button);
		m_layout->addWidget(button, row, col);
		button->setFixedSize(40, 40);
		button->setEnabled(false);

		col++;
		if (button->text() == "P" || button->text() == "L") {
			col = 0;
			row++;
		}
	}
}

void KeyboardGrid::updateButtons(QString guess)
{
	// Update the appearance of the buttons representing the keyboard if they have been used in a player's guess
	for (QPushButton* button : m_letterButtons) {
		if (guess.contains(button->text().toLower())) {
			button->setStyleSheet(USED_LETTER_BUTTON);
		}
	}
}

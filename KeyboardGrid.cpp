#include "KeyboardGrid.h"

KeyboardGrid::KeyboardGrid(QWidget* parent)
	: QWidget(parent)
{
	m_layout = new QVBoxLayout(this);
	createButtons();
	setLayout(m_layout);
}

KeyboardGrid::~KeyboardGrid()
{}

void KeyboardGrid::createButtons()
{
	QString keyboardLetters = UIStrings::KeyboardLetters;
	QHBoxLayout* rowLayout = new QHBoxLayout;

	// Iterate through the letters of the keyboard and create rows resembling the keyboard layout
	for (auto c : keyboardLetters) {
		QLabel* label = new QLabel(c);
		m_letterLabels.append(label);
		label->setFixedSize(WordleConstants::KeyDimension, WordleConstants::KeyDimension);
		label->setAlignment(Qt::AlignCenter);
		label->setStyleSheet(AVAILABLE_LETTER_LABEL);
		rowLayout->addWidget(label);

		if (label->text() == "P") {
			m_layout->addLayout(rowLayout);
			// Start a new row and add spacing for shorter next row
			rowLayout = new QHBoxLayout;
			rowLayout->addSpacerItem(new QSpacerItem(WordleConstants::KeyDimension / 2, WordleConstants::KeyDimension, QSizePolicy::Fixed, QSizePolicy::Fixed));
		}
		else if (label->text() == "L") {
			rowLayout->addSpacerItem(new QSpacerItem(WordleConstants::KeyDimension / 2, WordleConstants::KeyDimension, QSizePolicy::Fixed, QSizePolicy::Fixed));
			m_layout->addLayout(rowLayout);
			// Start a new row and add spacing for shorter next row
			rowLayout = new QHBoxLayout;
			rowLayout->addSpacerItem(new QSpacerItem((WordleConstants::KeyDimension), WordleConstants::KeyDimension, QSizePolicy::Fixed, QSizePolicy::Fixed));
		}
	}

	// Add the last row
	rowLayout->addSpacerItem(new QSpacerItem((WordleConstants::KeyDimension / 2) * 5, WordleConstants::KeyDimension, QSizePolicy::Fixed, QSizePolicy::Fixed));
	m_layout->addLayout(rowLayout);
}

void KeyboardGrid::updateButtons(QString guess)
{
	// Update the appearance of the buttons representing the keyboard if they have been used in a player's guess
	QString keyboardLetters = UIStrings::KeyboardLetters.toLower();

	for (int i = 0; i < keyboardLetters.length(); ++i) {
		if (guess.contains(keyboardLetters[i])) m_letterLabels[i]->setStyleSheet(USED_LETTER_LABEL);
	}
}

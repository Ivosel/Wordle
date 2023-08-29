#include "MyGrid.h"

MyGrid::MyGrid(Game* gameInstance, KeyboardGrid* letterGrid, int numColumns, QWidget* parent)
	: QWidget(parent), m_gameInstance(gameInstance), m_letterGrid(letterGrid), m_numColumns(numColumns),
	m_numRows(6), m_currentRow(0), m_currentCol(0)
{
	m_layout = new QGridLayout(this);
	m_labels.resize(m_numRows, std::vector<MyLabel*>(m_numColumns));
	createLabels();

	// Set the size of MyGrid widget
	int totalWidth = m_numColumns * 60;
	setFixedWidth(totalWidth);
	m_layout->setHorizontalSpacing(5);
	m_layout->setVerticalSpacing(15);

	setLayout(m_layout);
}

MyGrid::~MyGrid()
{}

void MyGrid::createLabels()
{
	// Create and add labels to the layout and the vector
	for (int row = 0; row < m_numRows; ++row) {
		for (int col = 0; col < m_numColumns; ++col) {
			MyLabel* label = new MyLabel("", row, col);
			m_labels[row][col] = label;
			m_layout->addWidget(label, row, col);
		}
	}
}

void MyGrid::keyPressEvent(QKeyEvent* event)
{
	// Get the pressed key
	QString key = event->text();

	// Check if the pressed key is a letter
	if (key.length() == 1 && key.at(0).isLetter()) {
		if (m_currentRow < m_labels.size() && m_currentCol < m_labels[0].size()) {
			// Set the letter in the current label
			MyLabel* currentLabel = m_labels[m_currentRow][m_currentCol];
			currentLabel->setText(key);

			// Move cursor to the next label within the same row
			m_currentCol++;
			if (m_currentCol >= m_labels[0].size()) {
				// Do not move to the next row if focus is on the last label in the row
				m_currentCol = m_labels[0].size() - 1;
			}

			// Update focus to the next label
			if (m_currentCol >= 0 && m_currentCol < m_labels[0].size()) {
				MyLabel* nextLabel = m_labels[m_currentRow][m_currentCol];
				nextLabel->setFocus();
			}
		}
	}

	// Check if the Backspace key was pressed
	else if (event->key() == Qt::Key_Backspace) {
		if (m_currentRow < m_labels.size() && m_currentCol >= 0) {
			MyLabel* currentLabel = m_labels[m_currentRow][m_currentCol];

			// Check if the text in the current label contains a letter
			if (currentLabel->text().isEmpty() || !currentLabel->text().at(0).isLetter()) {
				// Clear the text in the previous label and move focus to it
				if (m_currentCol > 0) {
					m_currentCol--;
					MyLabel* prevLabel = m_labels[m_currentRow][m_currentCol];
					prevLabel->clear();
					prevLabel->setFocus();
				}
			}
			else {
				// Clear the text in the current label
				currentLabel->clear();
			}
		}
	}

	// Check if the Enter key was pressed
	else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {

		// Create players guess string and read the current row labels contents to it
		QString guess;
		for (const MyLabel* label : m_labels[m_currentRow]) {
			QString labelText = label->text();
			labelText = labelText.trimmed();
			if (!labelText.isEmpty()) {
				guess += labelText;
			}
		}

		// Create a dialog for game end
		QMessageBox msgBox;
		msgBox.setIcon(QMessageBox::Question);
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		msgBox.setDefaultButton(QMessageBox::Yes);
		msgBox.setButtonText(QMessageBox::No, "Quit");
		int reply;

		// Call checkGuess to determine the game outcome
		switch (m_gameInstance->checkGuess(guess)) {
		case 0: // Set the dialog for player vicotry
			m_letterGrid->updateButtons(guess);
			updateLabelBackgroundColors(guess);
			msgBox.setText("Start a new game?");
			msgBox.setWindowTitle("Congratulations!");
			reply = msgBox.exec();

			if (reply == QMessageBox::Yes) {
				emit yesClicked();
			}
			else if (reply == QMessageBox::No) {
				emit noClicked();
			}
			break;
		case 1: // Set the dialog for player defeat
			m_letterGrid->updateButtons(guess);
			updateLabelBackgroundColors(guess);
			if (m_currentRow == 5) {
				msgBox.setText("Start a new game?");
				msgBox.setWindowTitle("Better luck next time");
				reply = msgBox.exec();
				if (reply == QMessageBox::Yes) {
					emit yesClicked();
				}
				else if (reply == QMessageBox::No) {
					emit noClicked();
				}
			}
			m_currentRow++;
			m_currentCol = 0;
			break;
		}

		// Update focus to the next label
		if (m_currentRow < m_labels.size() && m_currentCol < m_labels[0].size()) {
			MyLabel* nextLabel = m_labels[m_currentRow][m_currentCol];
			nextLabel->setFocus();
		}
	}
}

void MyGrid::updateLabelBackgroundColors(const QString& guess) {
	const QString selectedWord = m_gameInstance->m_selectedWord.toLower();

	// Iterate the letters of the player's guess and the game's word to update the label appearance in the grid
	for (int i = 0; i < selectedWord.length(); ++i) {
		MyLabel* label = m_labels[m_currentRow][i];

		if (i < guess.length()) {
			QChar selectedChar = selectedWord.at(i);
			QChar guessedChar = guess.at(i).toLower();

			if (guessedChar == selectedChar) {
				// Correct letter in correct position
				label->setAutoFillBackground(true);
				label->setStyleSheet(CORRECT_POSITION_LABEL);
			}
			else if (selectedWord.contains(guessedChar)) {
				// Correct letter in wrong position
				label->setAutoFillBackground(true);
				label->setStyleSheet(CORRECT_LETTER_LABEL);
			}
		}
	}
}

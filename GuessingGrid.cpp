#include "GuessingGrid.h"

using namespace WordleConstants;

GuessingGrid::GuessingGrid(QLabel* leftInvalidWord, QLabel* rightInvalidWord, Game* gameInstance, KeyboardGrid* letterGrid, int numColumns, QWidget* parent)
	: QWidget(parent), m_leftInvalidWord(leftInvalidWord), m_rightInvalidWord(rightInvalidWord), m_gameInstance(gameInstance), m_letterGrid(letterGrid),
	m_numColumns(numColumns), m_numRows(DefaultChances), m_currentRow(0), m_currentCol(0)
{
	leftInvalidWord->setStyleSheet(INVALID_WORD_LABEL);
	rightInvalidWord->setStyleSheet(INVALID_WORD_LABEL);

	m_layout = new QGridLayout(this);
	m_labels.resize(m_numRows, std::vector<QLabel*>(m_numColumns));
	createLabels();

	// Set the size of GuessingGrid widget
	int totalWidth = m_numColumns * (LabelDimension + GuessLabelsHspacing * 2);
	setFixedWidth(totalWidth);
	m_layout->setHorizontalSpacing(GuessLabelsHspacing);
	m_layout->setVerticalSpacing(GuessLabelsVspacing);

	setLayout(m_layout);
}

GuessingGrid::~GuessingGrid()
{}

void GuessingGrid::createLabels()
{
	// Create and add labels to the layout and the vector
	for (int row = 0; row < m_numRows; ++row) {
		for (int col = 0; col < m_numColumns; ++col) {
			QLabel* label = new QLabel("");
			label->setStyleSheet(DEFAULT_LABEL);
			label->setFixedSize(LabelDimension, LabelDimension);
			label->setAlignment(Qt::AlignCenter);
			m_labels[row][col] = label;
			m_layout->addWidget(label, row, col);
		}
	}
}

void GuessingGrid::keyPressEvent(QKeyEvent* event)
{
	QString key = event->text();

	if (key.length() == 1 && key.at(0).isLetter()) {
		handleLetterKey(key);
	}

	else if (event->key() == Qt::Key_Backspace) {
		handleBackspaceKey();
	}

	else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
		handleEnterKey();
	}
}

void GuessingGrid::handleLetterKey(QString key)
{
	if (m_currentRow < m_labels.size() && m_currentCol < m_labels[0].size()) {
		// Set the letter in the current label
		QLabel* currentLabel = m_labels[m_currentRow][m_currentCol];
		currentLabel->setText(key);

		// Move cursor to the next label within the same row
		m_currentCol++;
		if (m_currentCol >= m_labels[0].size()) {
			// Do not move to the next row if focus is on the last label in the row
			m_currentCol = m_labels[0].size() - 1;
		}

		// Update focus to the next label
		if (m_currentCol >= 0 && m_currentCol < m_labels[0].size()) {
			QLabel* nextLabel = m_labels[m_currentRow][m_currentCol];
			nextLabel->setFocus();
		}
	}
}

void GuessingGrid::handleBackspaceKey()
{
	m_leftInvalidWord->clear();
	m_rightInvalidWord->clear();


	if (m_currentRow < m_labels.size() && m_currentCol >= 0) {
		QLabel* currentLabel = m_labels[m_currentRow][m_currentCol];

		// Check if the text in the current label contains a letter
		if (currentLabel->text().isEmpty() || !currentLabel->text().at(0).isLetter()) {
			// Clear the text in the previous label and move focus to it
			if (m_currentCol > 0) {
				m_currentCol--;
				QLabel* prevLabel = m_labels[m_currentRow][m_currentCol];
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

void GuessingGrid::handleEnterKey()
{
	// Return if the last label in the row is empty
	QLabel const* lastLabel = m_labels[m_currentRow].back();
	if (lastLabel->text().isEmpty()) {
		return;
	}

	QString guess = createGuessFromLabels();

	switch (m_gameInstance->checkGuess(guess)) {

	case Game::CorrectGuess:
		handleCorrectGuess(guess);
		break;

	case Game::WrongGuess:
		if (m_currentRow == LastRow) {
			handleLastChanceWrongGuess(guess);
		}
		else handleWrongGuess(guess);
		break;

	case Game::InvalidGuess:
		handleInvalidGuess();
	}
}

QString GuessingGrid::createGuessFromLabels()
{
	// Create players guess string and read the current row labels contents to it
	QString guess;
	for (const QLabel* label : m_labels[m_currentRow]) {
		QString labelText = label->text();
		if (!labelText.isEmpty()) {
			guess += labelText;
		}
	}
	return guess;
}

void GuessingGrid::handleCorrectGuess(QString guess)
{
	m_letterGrid->updateButtons(guess);
	updateLabelBackgroundColors(guess);

	// Create message box for player victory
	QMessageBox msgBox;
	msgBox.setIcon(QMessageBox::Question);
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::Yes);
	msgBox.setButtonText(QMessageBox::No, UIStrings::GameEndNoButton);

	msgBox.setText(UIStrings::GameEndQuestion);
	msgBox.setWindowTitle(UIStrings::Victory);

	int reply = msgBox.exec();
	if (reply == QMessageBox::Yes) {
		emit yesClicked();
	}
	else if (reply == QMessageBox::No) {
		emit noClicked();
	}
}

void GuessingGrid::handleLastChanceWrongGuess(QString guess)
{
	m_letterGrid->updateButtons(guess);
	updateLabelBackgroundColors(guess);

	// Create message box for player defeat
	QMessageBox msgBox;
	msgBox.setIcon(QMessageBox::Question);
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::Yes);
	msgBox.setButtonText(QMessageBox::No, UIStrings::GameEndNoButton);

	msgBox.setText(QString("<p align='center'>%1<br>\"%2\"<br>%3</p>").arg(UIStrings::SelectedWord, m_gameInstance->m_selectedWord.toUpper(), UIStrings::GameEndQuestion));
	msgBox.setWindowTitle(UIStrings::Defeat);

	int reply = msgBox.exec();
	if (reply == QMessageBox::Yes) {
		emit yesClicked();
	}
	else if (reply == QMessageBox::No) {
		emit noClicked();
	}
}

void GuessingGrid::handleWrongGuess(QString guess)
{
	m_letterGrid->updateButtons(guess);
	updateLabelBackgroundColors(guess);
	m_currentRow++;
	m_currentCol = 0;
}

void GuessingGrid::handleInvalidGuess() {
	m_leftInvalidWord->setText(UIStrings::InvalidWord);
	m_rightInvalidWord->setText(UIStrings::InvalidWord);
}

void GuessingGrid::updateLabelBackgroundColors(const QString& guess) {
	const QString selectedWord = m_gameInstance->m_selectedWord.toLower();

	// Iterate the letters of the player's guess and the game's word to update the label appearance in the grid
	for (int i = 0; i < selectedWord.length(); ++i) {
		QLabel* label = m_labels[m_currentRow][i];

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

#include "Wordle.h"

using namespace WordleConstants;

Wordle::Wordle(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	// Connect menu items to slots
	connect(ui.actionNew_Game, &QAction::triggered, this, &Wordle::onNewGameTriggered);
	connect(ui.actionExit, &QAction::triggered, this, &Wordle::onExitTriggered);

	SetUpSelectionScreen();
}

Wordle::~Wordle()
{
}

void Wordle::SetUpSelectionScreen()
{
	setFixedSize(QSize(WindowWidth, WindowHeight));

	// Create buttons for selecting game difficulty
	QPushButton* easyButton = new QPushButton(UIStrings::EasyButton, this);
	QPushButton* mediumButton = new QPushButton(UIStrings::MediumButton, this);
	QPushButton* hardButton = new QPushButton(UIStrings::HardButton, this);
	easyButton->setFixedSize(DiffButtonW, DiffButtonH);
	mediumButton->setFixedSize(DiffButtonW, DiffButtonH);
	hardButton->setFixedSize(DiffButtonW, DiffButtonH);

	// Connect button signals to slots
	connect(easyButton, &QPushButton::clicked, this, &Wordle::onEasyClicked);
	connect(mediumButton, &QPushButton::clicked, this, &Wordle::onMediumClicked);
	connect(hardButton, &QPushButton::clicked, this, &Wordle::onHardClicked);

	// Create labels for legend
	QLabel* label1 = new QLabel("W", this);
	label1->setStyleSheet(DEFAULT_LABEL);
	label1->setFixedSize(LabelDimension, LabelDimension);
	label1->setAlignment(Qt::AlignCenter);
	QLabel* label2 = new QLabel("W", this);
	label2->setStyleSheet(CORRECT_LETTER_LABEL);
	label2->setFixedSize(LabelDimension, LabelDimension);
	label2->setAlignment(Qt::AlignCenter);
	QLabel* label3 = new QLabel("W", this);
	label3->setStyleSheet(CORRECT_POSITION_LABEL);
	label3->setFixedSize(LabelDimension, LabelDimension);
	label3->setAlignment(Qt::AlignCenter);

	// Create descriptions for legend labels
	QLabel* description1 = new QLabel(UIStrings::WrongLetter, this);
	QLabel* description2 = new QLabel(UIStrings::CorrectLetter, this);
	QLabel* description3 = new QLabel(UIStrings::CorrPosLetter, this);

	// Create layouts for legend labels and descriptions
	QVBoxLayout* labelsLayout = new QVBoxLayout;

	QGridLayout* label1Layout = new QGridLayout;
	label1Layout->addWidget(label1, 0, 0);
	label1Layout->addWidget(description1, 0, 1);
	labelsLayout->addLayout(label1Layout);

	QGridLayout* label2Layout = new QGridLayout;
	label2Layout->addWidget(label2, 0, 0);
	label2Layout->addWidget(description2, 0, 1);
	labelsLayout->addLayout(label2Layout);

	QGridLayout* label3Layout = new QGridLayout;
	label3Layout->addWidget(label3, 0, 0);
	label3Layout->addWidget(description3, 0, 1);
	labelsLayout->addLayout(label3Layout);

	// Create layout for difficulty selection buttons
	QVBoxLayout* buttonsLayout = new QVBoxLayout;
	buttonsLayout->addWidget(easyButton);
	buttonsLayout->addWidget(mediumButton);
	buttonsLayout->addWidget(hardButton);

	// Create a horizontal layout to arrange legend labels and difficulty selection buttons
	QHBoxLayout* mainLayout = new QHBoxLayout;
	mainLayout->addLayout(labelsLayout);
	mainLayout->addLayout(buttonsLayout);

	// Create labels and layout for sections (legent, title, difficulty)
	QLabel* legendLabel = new QLabel(UIStrings::Legend, this);
	QLabel* titleLabel = new QLabel(UIStrings::Title, this);
	QLabel* selectDifficultyLabel = new QLabel(UIStrings::GameDifficulty, this);

	QHBoxLayout* descriptionLayout = new QHBoxLayout;
	descriptionLayout->addWidget(legendLabel, 0, Qt::AlignBottom);
	descriptionLayout->addWidget(titleLabel);
	titleLabel->setStyleSheet(TITLE_TEXT);
	descriptionLayout->setAlignment(titleLabel, Qt::AlignLeft);
	descriptionLayout->addWidget(selectDifficultyLabel, 0, Qt::AlignBottom);

	// Create layout for the entire screen
	QVBoxLayout* finalLayout = new QVBoxLayout;
	finalLayout->addLayout(descriptionLayout);
	finalLayout->addLayout(mainLayout);

	// Create a central widget and set the main layout
	QWidget* centralWidget = new QWidget(this);
	centralWidget->setLayout(finalLayout);
	setCentralWidget(centralWidget);
}

void Wordle::SetUpGame(Difficulty diff)
{
	m_newGame = new Game(diff);

	m_letterGrid = new KeyboardGrid;

	// Create an instance of GuessingGrid and connect signals from the grids msgBox to slots
	m_customGrid = new GuessingGrid(m_newGame, m_letterGrid, m_newGame->m_selectedWord.length());
	connect(m_customGrid, &GuessingGrid::yesClicked, this, &Wordle::onNewGameTriggered);
	connect(m_customGrid, &GuessingGrid::noClicked, this, &Wordle::onExitTriggered);

	// Set the size of the main window
	int gridSize = m_customGrid->width();
	QSize finalSize = QSize(qMax(WindowWidth, gridSize), WindowHeight);
	setFixedSize(finalSize);

	// Create a layout for the custom grid
	QVBoxLayout* customGridLayout = new QVBoxLayout;
	customGridLayout->addWidget(m_customGrid);
	customGridLayout->setAlignment(Qt::AlignCenter);

	// Create a layout for the used letters grid
	QVBoxLayout* letterGridLayout = new QVBoxLayout;
	letterGridLayout->addWidget(m_letterGrid);
	letterGridLayout->setAlignment(Qt::AlignCenter);

	// Create a layout to hold both layouts
	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addLayout(customGridLayout);
	mainLayout->addLayout(letterGridLayout);

	// Create a central widget and set the main layout
	QWidget* centralWidget = new QWidget(this);
	centralWidget->setLayout(mainLayout);
	setCentralWidget(centralWidget);

	m_customGrid->setFocus();
}

void Wordle::onNewGameTriggered()
{
	// Handle class destruction
	disconnect(m_customGrid, &GuessingGrid::yesClicked, this, &Wordle::onNewGameTriggered);
	disconnect(m_customGrid, &GuessingGrid::noClicked, this, &Wordle::onExitTriggered);
	delete m_newGame;
	delete m_customGrid;
	delete m_letterGrid;

	SetUpSelectionScreen();
}

void Wordle::onExitTriggered()
{
	qApp->quit();
}

void Wordle::onEasyClicked()
{
	SetUpGame(Easy);
}

void Wordle::onMediumClicked()
{
	SetUpGame(Medium);
}

void Wordle::onHardClicked()
{
	SetUpGame(Hard);
}



#include "Wordle.h"



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
	setFixedSize(QSize(800, 600));

	// Create buttons for selecting game difficulty
	QPushButton* easyButton = new QPushButton("Easy (up to 4 letters)", this);
	QPushButton* mediumButton = new QPushButton("Medium (5-6 letters)", this);
	QPushButton* hardButton = new QPushButton("Hard (7 or more letters)", this);
	easyButton->setFixedSize(300, 50);
	mediumButton->setFixedSize(300, 50);
	hardButton->setFixedSize(300, 50);

	// Connect button signals to slots
	connect(easyButton, &QPushButton::clicked, this, &Wordle::onEasyClicked);
	connect(mediumButton, &QPushButton::clicked, this, &Wordle::onMediumClicked);
	connect(hardButton, &QPushButton::clicked, this, &Wordle::onHardClicked);

	// Create labels for legend
	MyLabel* label1 = new MyLabel("W", 0, 0, this);
	MyLabel* label2 = new MyLabel("W", 1, 0, this);
	label2->setStyleSheet(CORRECT_LETTER_LABEL);
	MyLabel* label3 = new MyLabel("W", 2, 0, this);
	label3->setStyleSheet(CORRECT_POSITION_LABEL);

	// Create descriptions for legend labels
	QLabel* description1 = new QLabel("Wrong Letter", this);
	QLabel* description2 = new QLabel("Right Letter", this);
	QLabel* description3 = new QLabel("Right Letter And Position", this);

	// Create layouts for legend labels and descriptions
	QVBoxLayout* labelsLayout = new QVBoxLayout;

	QGridLayout* label1Layout = new QGridLayout;
	label1Layout->addWidget(label1, 0, 0);
	label1Layout->addWidget(description1, 0, 1);
	label1Layout->setColumnStretch(0, 1);
	label1Layout->setColumnStretch(1, 1);
	labelsLayout->addLayout(label1Layout);

	QGridLayout* label2Layout = new QGridLayout;
	label2Layout->addWidget(label2, 0, 0);
	label2Layout->addWidget(description2, 0, 1);
	label2Layout->setColumnStretch(0, 1);
	label2Layout->setColumnStretch(1, 1);
	labelsLayout->addLayout(label2Layout);

	QGridLayout* label3Layout = new QGridLayout;
	label3Layout->addWidget(label3, 0, 0);
	label3Layout->addWidget(description3, 0, 1);
	label3Layout->setColumnStretch(0, 1);
	label3Layout->setColumnStretch(1, 1);
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
	QLabel* legendLabel = new QLabel("Legend:", this);
	QLabel* titleLabel = new QLabel("WORDLE", this);
	QLabel* selectDifficultyLabel = new QLabel("Select Game Difficulty:", this);

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

void Wordle::SetUpGame(int difficulty)
{
	m_newGame = new Game(difficulty);

	m_letterGrid = new KeyboardGrid;

	// Create an instance of MyGrid and connect signals from the grids msgBox to slots
	m_customGrid = new MyGrid(m_newGame, m_letterGrid, m_newGame->m_selectedWord.length());
	connect(m_customGrid, &MyGrid::yesClicked, this, &Wordle::onNewGameTriggered);
	connect(m_customGrid, &MyGrid::noClicked, this, &Wordle::onExitTriggered);

	// Set the size of the main window
	int gridSize = m_customGrid->width();
	QSize finalSize = QSize(qMax(800, gridSize), 600);
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
	SetUpSelectionScreen();
}

void Wordle::onExitTriggered()
{
	qApp->quit();
}

void Wordle::onEasyClicked()
{
	SetUpGame(4);
}

void Wordle::onMediumClicked()
{
	SetUpGame(6);
}

void Wordle::onHardClicked()
{
	SetUpGame(8);
}



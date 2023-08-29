#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include "Styles.h"

class KeyboardGrid : public QWidget
{
	Q_OBJECT

public:
	KeyboardGrid(QWidget* parent = nullptr);
	~KeyboardGrid();
	void updateButtons(QString guess);

private:
	void createButtons();

	QGridLayout* m_layout;
	QStringList m_alphabet;
	QList<QPushButton*> m_letterButtons;
};

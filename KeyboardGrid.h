#pragma once

#include <QWidget>
#include <QGridLayout>
#include <Qlabel>
#include "Styles.h"
#include "Constants.h"
#include "UIStrings.h"

class KeyboardGrid : public QWidget
{
	Q_OBJECT

public:
	KeyboardGrid(QWidget* parent = nullptr);
	~KeyboardGrid();
	void updateButtons(QString guess);

private:
	void createButtons();

	QVBoxLayout* m_layout;
	QList<QLabel*> m_letterLabels;
};

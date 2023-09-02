#pragma once

#include <QWidget>
#include <QGridLayout>
#include <Qlabel>
#include "Styles.h"
#include "Constants.h"

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
	QList<QLabel*> m_letterLabels;
};

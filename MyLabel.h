#pragma once

#include <QLabel>
#include "Styles.h"

class MyLabel : public QLabel
{
	Q_OBJECT

public:
	MyLabel(const QString& text, int row, int col, QWidget* parent = nullptr);
	~MyLabel();

private:
	int m_row;
	int m_column;
};

#include "MyLabel.h"

MyLabel::MyLabel(const QString& text, int row, int col, QWidget* parent)
	: QLabel(text, parent), m_row(row), m_column(col)
{
	setStyleSheet(DEFAULT_LABEL);
	setFixedSize(50, 50);
}

MyLabel::~MyLabel()
{}

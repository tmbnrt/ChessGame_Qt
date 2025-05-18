#pragma once

#include "ui_BoardView.h"
#include "MenuView.h"
#include <QWidget>
#include <QLabel>
#include <QGridLayout>

class BoardView : public QWidget
{
	Q_OBJECT

signals:
	void backToMenuClicked();

public:
	explicit BoardView(QWidget* parent = nullptr);
	~BoardView();

private slots:
	void										onBackButtonClicked();

private:
	Ui::BoardView*								ui;
	MenuView*									menuView;

	int											gridSize = 480;
	void										setupBoard();
	void										setFigures();
};


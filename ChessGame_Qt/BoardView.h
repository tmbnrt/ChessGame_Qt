#pragma once

#include "ui_BoardView.h"
#include "MenuView.h"
//#include "Logic/Game.h"
#include "Logic/Character.h"
#include "Logic/PlayerMoves.h"
#include <map>
#include <QWidget>
#include <QLabel>
#include <QGridLayout>

class BoardView : public QWidget
{
	Q_OBJECT

signals:
	void										backToMenuClicked();
	void										userInputReceived();

public:
	explicit BoardView(QWidget* parent = nullptr);
	~BoardView();

	// Game logic interaction
	void										update(const std::vector<std::vector<Character*>> board);
	void										getMove(PlayerMoves& playerMoves);
	std::vector<int>							move_from;
	std::vector<int>							move_to;

private slots:
	void										onBackButtonClicked();
	void										handleButtonClick(int row, int col);

private:
	Ui::BoardView*								ui;
	MenuView*									menuView;

	int											gridSize = 480;
	void										setupBoard();
	void										setFigures();

	// Game logic interaction
	std::vector<int>							pressedButton;
	std::unordered_map<char, std::string>		designationFigure;
	void										waitForUserInput();
	void										highlightFields(std::vector<std::vector<int>> possible);
};


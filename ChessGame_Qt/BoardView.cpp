#include "BoardView.h"

BoardView::BoardView(QWidget* parent) : QWidget(parent), ui(new Ui::BoardView) {
	ui->setupUi(this);

	// Setup chess board from designer
	setupBoard();

	// Start game logic
	//Game game = Game(this);
	//game.start();

	connect(ui->buttonBackToMenu, &QPushButton::clicked, this, &BoardView::backToMenuClicked);
}

void BoardView::handleButtonClick(int row, int col) {
	// Save the grid button position clicked by the user
	pressedButton = { row, col };
}

void BoardView::endOfGame(bool win, int n_moves) {
	//...
}

void BoardView::waitForUserInput() {
	QGridLayout* layout = findChild<QGridLayout*>("gridLayout");
	QEventLoop loop;

	if (layout) {
		for (int row = 0; row < 8; ++row) {
			for (int col = 0; col < 8; ++col) {
				QPushButton* button = qobject_cast<QPushButton*>(layout->itemAtPosition(row, col)->widget());
				if (button) {
					// create button connection
					connect(button, &QPushButton::clicked, this, [this, row, col, &loop]() {
						handleButtonClick(row, col);
						emit userInputReceived();
						loop.quit();
						});
				}
			}
		}
	}

	connect(this, &BoardView::userInputReceived, &loop, &QEventLoop::quit);
	loop.exec();
}

void BoardView::setFigures() {
	designationFigure.insert({ 't', "resources/pieces/512h/b_rook_png_512px.png" });
	designationFigure.insert({ 's', "resources/pieces/512h/b_knight_png_512px.png" });
	designationFigure.insert({ 'l', "resources/pieces/512h/b_bishop_png_512px.png" });
	designationFigure.insert({ 'd', "resources/pieces/512h/b_queen_png_512px.png" });
	designationFigure.insert({ 'k', "resources/pieces/512h/b_king_png_512px.png" });
	designationFigure.insert({ 'b', "resources/pieces/512h/b_pawn_png_512px.png" });
	designationFigure.insert({ 'T', "resources/pieces/512h/w_rook_png_512px.png" });
	designationFigure.insert({ 'S', "resources/pieces/512h/w_knight_png_512px.png" });
	designationFigure.insert({ 'L', "resources/pieces/512h/w_bishop_png_512px.png" });
	designationFigure.insert({ 'D', "resources/pieces/512h/w_queen_png_512px.png" });
	designationFigure.insert({ 'K', "resources/pieces/512h/w_king_png_512px.png" });
	designationFigure.insert({ 'B', "resources/pieces/512h/w_pawn_png_512px.png" });

	std::vector<std::vector<std::string>> pathFigures(8, std::vector<std::string>(8, ""));
	pathFigures[0][0] = "resources/pieces/512h/b_rook_png_512px.png";
	pathFigures[0][1] = "resources/pieces/512h/b_knight_png_512px.png";
	pathFigures[0][2] = "resources/pieces/512h/b_bishop_png_512px.png";
	pathFigures[0][3] = "resources/pieces/512h/b_queen_png_512px.png";
	pathFigures[0][4] = "resources/pieces/512h/b_king_png_512px.png";
	pathFigures[0][5] = "resources/pieces/512h/b_bishop_png_512px.png";
	pathFigures[0][6] = "resources/pieces/512h/b_knight_png_512px.png";
	pathFigures[0][7] = "resources/pieces/512h/b_rook_png_512px.png";
	for (int i = 0; i < 8; i++)
		pathFigures[1][i] = "resources/pieces/512h/b_pawn_png_512px.png";	

	pathFigures[7][0] = "resources/pieces/512h/w_rook_png_512px.png";
	pathFigures[7][1] = "resources/pieces/512h/w_knight_png_512px.png";
	pathFigures[7][2] = "resources/pieces/512h/w_bishop_png_512px.png";
	pathFigures[7][3] = "resources/pieces/512h/w_queen_png_512px.png";
	pathFigures[7][4] = "resources/pieces/512h/w_king_png_512px.png";
	pathFigures[7][5] = "resources/pieces/512h/w_bishop_png_512px.png";
	pathFigures[7][6] = "resources/pieces/512h/w_knight_png_512px.png";
	pathFigures[7][7] = "resources/pieces/512h/w_rook_png_512px.png";
	for (int i = 0; i < 8; i++)
		pathFigures[6][i] = "resources/pieces/512h/w_pawn_png_512px.png";

	int fieldSize = gridSize / 8;

	QGridLayout* layout = findChild<QGridLayout*>("gridLayout");
	if (layout) {
		for (int i = 0; i < 8; ++i) {
			for (int j = 0; j < 8; ++j) {
				if (pathFigures[i][j] != "") {
					QPushButton* button = qobject_cast<QPushButton*>(layout->itemAtPosition(i, j)->widget());
					if (button) {
						QPixmap pixmap(QString::fromStdString(pathFigures[i][j]));
						QIcon icon(pixmap);
						button->setIcon(icon);
						button->setIconSize(QSize(fieldSize, fieldSize));						
					}
				}
			}
		}
	}
}

void BoardView::setupBoard() {
	int fieldSize = gridSize / 8;

	QGridLayout* layout = findChild<QGridLayout*>("gridLayout");
	if (layout) {
		layout->setContentsMargins(0, 0, 0, 0);				// avoid unnecessary bounds
		layout->setSpacing(0);								// avoid distance between buttons
		//for (int i = 0; i < 8; ++i) {
		//	layout->setColumnStretch(i, 0);					// deactivate dynamic fit
		//	layout->setRowStretch(i, 0);
		//	layout->setColumnMinimumWidth(i, fieldSize);	// field width to defined value
		//	layout->setRowMinimumHeight(i, fieldSize);		// field height to defined value
		//}

		for (int row = 0; row < 8; ++row) {
			for (int col = 0; col < 8; ++col) {
				QPushButton* button = qobject_cast<QPushButton*>(layout->itemAtPosition(row, col)->widget());
				if (button) {
					button->setFixedSize(fieldSize, fieldSize);
					button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
					QString color = ((row + col) % 2 == 0) ? "white" : "gray";
					button->setStyleSheet("background-color: " + color + "; border 1px solid black;");					
				}
			}
		}
	}

	setFigures();
}

void BoardView::onBackButtonClicked() {
	menuView = new MenuView();
	menuView->show();
	this->close();
}

void BoardView::update(const std::vector<std::vector<Character*>> board) {
	std::vector<std::vector<char>> charBoard(8, std::vector<char>(8));
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[0].size(); j++) {
			if (board[i][j] != nullptr)
				charBoard[i][j] = board[i][j]->getDesignation();
			else
				charBoard[i][j] = '0';
		}
	}

	int fieldSize = gridSize / 8;
	QGridLayout* layout = findChild<QGridLayout*>("gridLayout");
	if (layout) {
		for (int i = 0; i < board.size(); ++i) {
			for (int j = 0; j < board[0].size(); ++j) {
				QPushButton* button = qobject_cast<QPushButton*>(layout->itemAtPosition(i, j)->widget());
				if (button) {
					QString color = ((i + j) % 2 == 0) ? "white" : "gray";
					button->setStyleSheet("background-color: " + color + "; border 1px solid black;");
					QPixmap pixmap(QString::fromStdString(designationFigure[charBoard[i][j]]));
					QIcon icon(pixmap);
					button->setIcon(icon);
					button->setIconSize(QSize(fieldSize, fieldSize));
				}
			}
		}
	}
}

void BoardView::highlightFields(std::vector<std::vector<int>> allowed) {
	// Unhighlight
	QGridLayout* layout = findChild<QGridLayout*>("gridLayout");
	for (int row = 0; row < 8; ++row) {
		for (int col = 0; col < 8; ++col) {
			QPushButton* button = qobject_cast<QPushButton*>(layout->itemAtPosition(row, col)->widget());
			if (button) {
				QString color = ((row + col) % 2 == 0) ? "white" : "gray";
				button->setStyleSheet("background-color: " + color + "; border 1px solid black;");
				//button->setStyleSheet("border: 1px solid black;");
			}
		}
	}

	// Highlight relevant buttons
	for (int i = 0; i < allowed.size(); ++i) {
		QPushButton* button = qobject_cast<QPushButton*>(layout->itemAtPosition(allowed[i][0], allowed[i][1])->widget());
		if (button) {
			QString color = ((allowed[i][0] + allowed[i][1]) % 2 == 0) ? "white" : "gray";
			button->setStyleSheet("background-color: " + color + "; border: 2px solid red;");
			//button->setStyleSheet("border: 2px solid red;");
		}
	}
}

void BoardView::getMove(PlayerMoves& playerMoves) {
	std::vector<int> actual;
	std::vector<int> target;

	bool selActPosition = true;
	bool correct_input = false;

	// EDIT --> This is from the SFML framework !
	while (!correct_input) {
		// Check input
		// Get pressed button
		waitForUserInput();

		int row = pressedButton[0];
		int col = pressedButton[1];

		// CHECK IF ALLOWED
		if (selActPosition && playerMoves.checkAllowedActual(std::vector<int>{ row, col })) {
			actual = std::vector<int>{ row, col };
			selActPosition = false;

			// Mark targets
			highlightFields(playerMoves.getTargets(actual));
		}
		else if (!selActPosition) {
			target = std::vector<int>{ row, col };
			if ((target[0] == actual[0] && target[1] == actual[1]) || playerMoves.checkAllowedActual(std::vector<int>{ target[0], target[1] })) {
				// unmark board
				std::vector<std::vector<int>> empty;
				//window.clear();
				//drawBoard();
				//drawImages(act_board);
				highlightFields(empty);
				selActPosition = true;
				continue;
			}

			if (playerMoves.checkAllowed(actual, target)) {
				correct_input = true;
				playerMoves.addHistory(actual, target);
				this->move_from = actual;
				this->move_to = target;
			}
			else {
				//drawBoard();
				//drawImages(act_board);
				selActPosition = true;
				continue;
			}
		}
	}
}

BoardView::~BoardView() {
	delete ui;
}

#include "BoardView.h"

BoardView::BoardView(QWidget* parent) : QWidget(parent), ui(new Ui::BoardView) {
	ui->setupUi(this);
	//setFixedSize(gridSize + 200, gridSize + 200);

	// Setup chess board from designer
	setupBoard();	

	connect(ui->buttonBackToMenu, &QPushButton::clicked, this, &BoardView::backToMenuClicked);
}

void BoardView::setFigures() {
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

BoardView::~BoardView() {
	delete ui;
}

#include "BoardView.h"

BoardView::BoardView(QWidget* parent) : QWidget(parent), ui(new Ui::BoardView) {
	ui->setupUi(this);

	// Setup chess board from designer
	setupBoard();

	connect(ui->buttonBackToMenu, &QPushButton::clicked, this, &BoardView::backToMenuClicked);
}

void BoardView::setupBoard() {
	QGridLayout* layout = findChild<QGridLayout*>("gridLayout");
	if (layout) {
		for (int row = 0; row < 8; ++row) {
			for (int col = 0; col < 8; ++col) {
				QPushButton* button = qobject_cast<QPushButton*>(layout->itemAtPosition(row, col)->widget());
				if (button) {
					QString color = ((row + col) % 2 == 0) ? "white" : "gray";
					button->setStyleSheet("background-color: " + color + "; border 1px solid black;");
				}
			}
		}
	}
}

void BoardView::onBackButtonClicked() {
	menuView = new MenuView();
	menuView->show();
	this->close();
}

BoardView::~BoardView() {
	delete ui;
}

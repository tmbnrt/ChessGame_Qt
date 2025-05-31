#include "EndOfGameView.h"

EndOfGameView::EndOfGameView(QWidget* parent) : QWidget(parent), ui(new Ui::EndOfGameView) {
	ui->setupUi(this);

	connect(ui->buttonExitToMenu, &QPushButton::clicked, this, &EndOfGameView::backToMenuClicked);
}

void EndOfGameView::setInfo(int n_moves, double seconds) {
	if (n_moves > 0) {
		ui->lineEditMessage->setText("Congratulations, you won the match!");
		
		std::string moves_str = std::to_string(n_moves);
		ui->lineEditMoves->setText(QString::fromStdString(moves_str));

		// time
		std::string seconds_str = std::to_string(seconds);
		ui->lineEditTime->setText(QString::fromStdString(seconds_str));
	}
	else if (n_moves < 0) {
		ui->lineEditMessage->setText("Poor, you lost the match!");
	}
	else {
		ui->lineEditMessage->setText("Stealmate!");
	}
}

void EndOfGameView::onBackButtonClicked() {
	menuView = new MenuView();
	menuView->show();
	this->close();
}

EndOfGameView::~EndOfGameView()
{}

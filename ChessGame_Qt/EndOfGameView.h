#pragma once

//#include <QMainWindow>
#include "MenuView.h"
#include "ui_EndOfGameView.h"
#include <QWidget>

class EndOfGameView : public QWidget
{
	Q_OBJECT

signals:
	void										backToMenuClicked();
	void										newGameClicked();

public:
	explicit EndOfGameView(QWidget *parent = nullptr);
	~EndOfGameView();
	void										setInfo(int n_moves, double elapsed_seconds);

private slots:
	void										onBackButtonClicked();

private:
	Ui::EndOfGameView*							ui;
	MenuView*									menuView;
	int											n_moves;
	int											time;
};

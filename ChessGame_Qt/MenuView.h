#pragma once

#include "ui_MenuView.h"
#include <QWidget>

class MenuView : public QWidget
{
	Q_OBJECT

signals:
	void startGameClicked();

public:
	explicit MenuView(QWidget* parent = nullptr);
	~MenuView();

	QPushButton* getStartButton() const { return ui->buttonStartGame; }

private:
	Ui::MenuView*								ui;
};

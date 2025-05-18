#include "MenuView.h"

MenuView::MenuView(QWidget* parent) : QWidget(parent), ui(new Ui::MenuView)
{
    ui->setupUi(this);  // UI-Elemente initialisieren

    connect(ui->buttonStartGame, &QPushButton::clicked, this, &MenuView::startGameClicked);
}

MenuView::~MenuView()
{
    delete ui;
}

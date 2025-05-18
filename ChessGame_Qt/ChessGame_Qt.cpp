#include "ChessGame_Qt.h"

ChessGame_Qt::ChessGame_Qt(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(1000, 500);
    createMenus();

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    layout = new QVBoxLayout(centralWidget);

    // QStackedWidget for different views
    stackedWidget = new QStackedWidget();
    layout->addWidget(stackedWidget);

    // Create menu and board view
    menuView = new MenuView();
    boardView = new BoardView();

    stackedWidget->addWidget(menuView);
    stackedWidget->addWidget(boardView);

    stackedWidget->setCurrentWidget(menuView);  // Default widget

    // Verbinde die Signale für den Wechsel der Ansicht
    connect(menuView, &MenuView::startGameClicked, this, &ChessGame_Qt::switchToBoardView);
    connect(boardView, &BoardView::backToMenuClicked, this, &ChessGame_Qt::switchToMenuView);
}

void ChessGame_Qt::switchToBoardView()
{
    stackedWidget->setCurrentWidget(boardView);

    // Start game logic
    Game game = Game(boardView);
    game.start();
}

void ChessGame_Qt::switchToMenuView()
{
    stackedWidget->setCurrentWidget(menuView);
}

void ChessGame_Qt::createMenus() {
    menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    // File menu
    fileMenu = menuBar->addMenu("File");
    newAction = fileMenu->addAction("New");
    exitAction = fileMenu->addAction("Exit");

    // Edit menu
    editMenu = menuBar->addMenu("Edit");
    editMenu->addAction("Undo");
    editMenu->addAction("Redo");

    // Exit button
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);
}

ChessGame_Qt::~ChessGame_Qt()
{}

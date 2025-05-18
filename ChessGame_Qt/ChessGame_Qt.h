#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ChessGame_Qt.h"
#include "MenuView.h"
#include "BoardView.h"
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

class ChessGame_Qt : public QMainWindow
{
    Q_OBJECT

public:
    ChessGame_Qt(QWidget *parent = nullptr);
    ~ChessGame_Qt();

private slots:
    void                                        switchToBoardView();
    void                                        switchToMenuView();

private:
    Ui::ChessGame_QtClass                       ui;
    void                                        createMenus();

    QMenuBar*                                   menuBar;
    QMenu*                                      fileMenu;
    QMenu*                                      editMenu;
    QAction*                                    newAction;
    QAction*                                    exitAction;

    QWidget*                                    centralWidget;
    QVBoxLayout*                                layout;
    QStackedWidget*                             stackedWidget;
    MenuView*                                   menuView;
    BoardView*                                  boardView;
};

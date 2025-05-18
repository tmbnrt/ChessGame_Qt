#include "Game.h"
//#include "Prediction.h"

Game::Game(BoardView* view) : boardView(view) {}

void Game::initPlayer(std::string name_1, std::string name_2) {
    this->white = Player();
    this->white.assign(name_1, 1);
    this->black = Player();
    this->black.assign(name_2, 2);
}

int Game::start() {
    // Create and initialize board
    std::vector<std::vector<Character*>> init_board(8, std::vector<Character*>(8));
    this->board = init_board;

    // Initialize renderer
    //Renderer renderer(8, 100);

    initPlayer("Player1", "Player2");
    this->board = white.putChars(this->board);
    this->board = black.putChars(this->board);

    // Initialize player's possible moves
    this->playerMoves = std::vector<PlayerMoves> { PlayerMoves(), PlayerMoves() };

    // Initialize test engine
    Test test = Test();

    // Initialize AI Prediction 
    //Prediction prediction = Prediction();

    // Main loop
    bool random_enemy = true;
    bool predict = false;
    int winner = 0;;
    int act_player = 1;       // white starts
    Action action = Action();
    bool active = true;
    while (active) {
        // TEST MOVES
        //this->board = test.move(board);       

        // Print board to console
        action.printBoard(board);
        boardView->update(board);

        // Get all possible moves of player
        playerMoves[act_player - 1].checkPlayerMoves(board, act_player);

        // CHECK IF GAME IS LOST OR STALEMATE
        if (playerMoves[act_player - 1].checkMate()) {
            if (act_player == 1)
                winner = 2;
            else
                winner = 1;
            active = false;
            break;
        }
        if (playerMoves[act_player - 1].getNumberMoves() == 0 && !playerMoves[act_player - 1].isChess()) {
            winner = 0;
            active = false;
            break;
        }

        // Get random move for black player (enemy)
        if (random_enemy && act_player == 2) {
            action.createRandomMove(playerMoves[act_player - 1]);
            board = board[action.random_from[0]][action.random_from[1]]->move(board, std::vector<int> {action.random_to[0], action.random_to[1]});
            act_player = 1;
            continue;
        }
        //if (predict) {
        //    prediction.inputProcess(board, playerMoves[act_player - 1]);
        //    std::vector<int> ai_from = prediction.getMove()[0];
        //    std::vector<int> ai_to = prediction.getMove()[1];
        //}

        // Get move from renderer - OR - console
        boardView->getMove(playerMoves[act_player - 1]);
        //std::vector<std::vector<int>> playerMove = action.getMoves(act_player);

        // Move figure on board
        board = board[boardView->move_from[0]][boardView->move_from[1]]->move(board, std::vector<int> { boardView->move_to[0], boardView->move_to[1] }, false);
        
        // Check if pawn has reached oppisite side
        if (act_player == 1 && board[boardView->move_to[0]][boardView->move_to[1]]->getDesignation() == 'B' && boardView->move_to[0] == 0)
            board = white.getQueen(board, boardView->move_to);
        if (act_player == 2 && board[boardView->move_to[0]][boardView->move_to[1]]->getDesignation() == 'b' && boardView->move_to[0] == 7)
            board = black.getQueen(board, boardView->move_to);

        // Switch player
        if (act_player == 1)
            act_player = 2;
        else
            act_player = 1;
    }
    if (winner > 0)
        std::cout << "  --> Winner is Player " + act_player << std::endl;
    else
        std::cout << "  --> Stealmate!" << std::endl;

    return 0;
}

Game::~Game() {}

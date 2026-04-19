#include <iostream>
#include <ctime>
#include <cstdlib>

/**
 * @brief Prints the current game board with all player moves.
 * @param board The 6x7 game board array that stores the current state of the game.
 */
void printBoard(char board[6][7]);

/**
 * @brief Places a player's piece in the chosen column if possible.
 * @param board The 6x7 game board array.
 * @param col The column index (0–6) where the player wants to drop their piece.
 * @param player The character symbol representing the current player ('X' or 'O').
 * @return true if the piece was successfully placed, false if the column is full or invalid.
 */
bool makeMove(char board[6][7], int col, char player);

/**
 * @brief Checks the board to see if the given player has won the game.
 * @param board The 6x7 game board array.
 * @param player The character symbol representing the current player.
 * @return true if the player has 4 in a row (horizontal, vertical, or diagonal).
 */
bool checkWin(char board[6][7], char player);

/**
 * @brief Checks if the board is completely full (tie game).
 * @param board The 6x7 game board array.
 * @return true if no empty cells ('.') remain, false otherwise.
 */
bool isFull(char board[6][7]);

/**
 * @brief Gets a valid column number from the player.
 * Keeps asking until a valid and non-full column is entered.
 * @param board The 6x7 game board array.
 * @return A valid column index (0–6).
 */
int getValidColumn(char board[6][7]);

/**
 * @brief Makes the computer choose a random available column.
 * @param board The 6x7 game board array.
 * @return The chosen column index (0–6).
 */
int getAIMove(char board[6][7]);


int main() {

    // Create a 6x7 board and fill it with '.' to show all spots are empty
    char board[6][7];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            board[i][j] = '.';
        }
    }

    // Player symbols
    const char human = 'X';
    const char AI = 'O';
    char currentPlayer = human;

    bool gameOver = false;

    // Seed random number generator for AI move randomness
    std::srand(std::time(0));

    // Main game loop
    while (!gameOver) {
        // Show the current board state
        printBoard(board);

        int column;

        if (currentPlayer == human) {
            // Human player's turn
            column = getValidColumn(board);
        } else {
            // AI player's turn
            column = getAIMove(board);
            std::cout << "Computer chooses column " << column + 1 << std::endl;
        }

        // Try placing the piece in the selected column
        bool success = makeMove(board, column, currentPlayer);

        if (success) {
            // Check for a win
            if (checkWin(board, currentPlayer)) {
                printBoard(board);
                if (currentPlayer == human)
                    std::cout << "You win!" << std::endl;
                else
                    std::cout << "AI wins!" << std::endl;
                gameOver = true;
            }
            // If no one wins, check if the board is full (tie)
            else if (isFull(board)) {
                printBoard(board);
                std::cout << "It's a tie!" << std::endl;
                gameOver = true;
            }
            // If game isn't over, switch turns
            else {
                if (currentPlayer == human)
                    currentPlayer = AI;
                else
                    currentPlayer = human;
            }
        } else {
            std::cout << "That column is full! Try again.\n";
        }
    }

    return 0;
}

void printBoard(char board[6][7]) {

    for (int i = 0; i < 6; i++) {
        for (int j= 0; j < 7; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
    // Print column numbers below the board for reference
    std::cout << "1 2 3 4 5 6 7";
}

bool makeMove(char board[6][7], int col, char player) {
    if (col <0 || col >= 7 ) {
        return false; // invalid column
    }
    // Start from the bottom row and find an empty spot
    for (int i = 5; i >= 0; i--) {
        if (board[i][col] == '.') {
            board[i][col] = player;
            return true; // successfully placed
        }
    }
    return false; // column is full
}

bool checkWin(char board[6][7], char player) {
    // Check horizontal win
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == player && board[i][j+1] == player &&
                board[i][j+2] == player && board[i][j+3] == player) {
                return true;
            }
        }
    }

    // Check vertical win
    for (int j = 0; j < 7; j++) {
        for (int i = 0; i < 3; i++) {
            if (board[i][j] == player && board[i+1][j] == player &&
                board[i+2][j] == player && board[i+3][j] == player) {
                return true;
            }
        }
    }

    // Check diagonal (\)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == player && board[i+1][j+1] == player &&
                board[i+2][j+2] == player && board[i+3][j+3] == player) {
                return true;
            }
        }
    }

    // Check diagonal (/)
    for (int i = 3; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == player && board[i-1][j+1] == player &&
                board[i-2][j+2] == player && board[i-3][j+3] == player) {
                return true;
            }
        }
    }
    return false;
}

bool isFull(char board[6][7]) {
    for (int j = 0; j < 7; j++) {
        if (board[0][j] == '.') {
            return false; // top cell empty → still space
        }
    }
    return true; // board completely full
}

int getValidColumn(char board[6][7]) {
    int col;
    while (true) {
        std::cout << "Please enter a column from (1 - 7): ";
        std::cin >> col;

        // Make sure the input is within range
        if (col < 1 || col > 7) {
            std::cout << "Please enter a valid column from (1 - 7): ";
        }
        // Make sure the column isn't already full
        else if (board[0][col-1] != '.') {
            std::cout << "That column is full please try again" << std::endl;
        }
        else {
            return col-1; // convert to 0-based index
        }
    }
}


int getAIMove(char board[6][7]) {
   int move;
   do {
       move = rand() % 7; // random number between 0–6
   } while (board[0][move] != '.'); // make sure the column isn’t full
   return move;
}









// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.

// TIP Press <shortcut actionId="RenameElement"/> when your caret is at the
// <b>lang</b> variable name to see how CLion can help you rename it.


// TIP Press <shortcut actionId="Debug"/> to start debugging your code.
// We have set one <icon src="AllIcons.Debugger.Db_set_breakpoint"/>
// breakpoint for you, but you can always add more by pressing

// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
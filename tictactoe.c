#include <stdio.h>

/* Simple two‑player Tic‑Tac‑Toe game.
 *
 * Board positions are numbered from 1 to 3 for both rows and columns.
 * Players take turns entering the row and column of their desired move.
 * The program checks for a win or a draw after each move.
 */

/* Function prototypes */
void printBoard(char board[3][3]);
int checkWinner(char board[3][3]);
int isBoardFull(char board[3][3]);

int main(void)
{
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    char currentPlayer = 'X';
    int row, col;
    int gameRunning = 1;

    printf("Welcome to Tic‑Tac‑Toe!\n");
    while (gameRunning) {
        printBoard(board);
        printf("Player %c, enter your move (row and column, 1‑3): ", currentPlayer);
        if (scanf("%d %d", &row, &col) != 2) {
            /* If input fails, clear invalid input */
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF) {
                /* discard */
            }
            printf("Invalid input. Please enter two numbers between 1 and 3.\n");
            continue;
        }
        if (row < 1 || row > 3 || col < 1 || col > 3) {
            printf("Positions must be between 1 and 3. Try again.\n");
            continue;
        }
        row--; col--;  /* convert to 0‑based index */
        if (board[row][col] != ' ') {
            printf("That position is already taken. Try again.\n");
            continue;
        }
        board[row][col] = currentPlayer;

        /* Check for a winner */
        if (checkWinner(board)) {
            printBoard(board);
            printf("Player %c wins!\n", currentPlayer);
            gameRunning = 0;
        } else if (isBoardFull(board)) {
            printBoard(board);
            printf("It's a draw!\n");
            gameRunning = 0;
        } else {
            /* Switch players */
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
    return 0;
}

/* Print the current state of the board */
void printBoard(char board[3][3])
{
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("-----------\n");
    }
    printf("\n");
}

/* Check if the current player has won.  Returns 1 if there is a winner, 0 otherwise. */
int checkWinner(char board[3][3])
{
    /* Check rows and columns */
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return 1;
        }
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return 1;
        }
    }
    /* Check diagonals */
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return 1;
    }
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return 1;
    }
    return 0;
}

/* Check if the board is full (no empty spaces).  Returns 1 if full, 0 otherwise. */
int isBoardFull(char board[3][3])
{
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

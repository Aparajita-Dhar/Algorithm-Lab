#include <iostream>
#include <vector>

/* Topic 4: Backtracking Method (N-Queens Problem)
   Strategy: Place queens one by one in different columns. If placing a queen 
   leads to an invalid state, backtrack and change the position of the previous queen.
*/
class BacktrackingEngine {
private:
    int boardSize;

    // Utility function to check if a queen can be safely placed at board[row][col]
    bool isSafePosition(const std::vector<std::vector<int>>& board, int row, int col) {
        // Check this row on the left side
        for (int i = 0; i < col; i++) {
            if (board[row][i] == 1) return false;
        }

        // Check upper diagonal on left side
        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 1) return false;
        }

        // Check lower diagonal on left side
        for (int i = row, j = col; j >= 0 && i < boardSize; i++, j--) {
            if (board[i][j] == 1) return false;
        }

        return true;
    }

    // Recursive helper function to solve the N-Queens space
    bool solveNQueensHelper(std::vector<std::vector<int>>& board, int col) {
        // Base case: If all queens are placed, return true
        if (col >= boardSize) return true;

        // Consider this column and try placing this queen in all rows one by one
        for (int i = 0; i < boardSize; i++) {
            if (isSafePosition(board, i, col)) {
                board[i][col] = 1; // Place queen

                // Recur to place rest of the queens
                if (solveNQueensHelper(board, col + 1)) return true;

                // If placing queen here doesn't lead to a solution, BACKTRACK
                board[i][col] = 0; 
            }
        }
        return false; // Target cannot be resolved in this configuration
    }

public:
    BacktrackingEngine(int size) : boardSize(size) {}

    void executeNQueens() {
        std::vector<std::vector<int>> board(boardSize, std::vector<int>(boardSize, 0));

        std::cout << "--- 4. Backtracking Paradigm (" << boardSize << "-Queens) ---\n";
        if (!solveNQueensHelper(board, 0)) {
            std::cout << "Solution does not exist.\n";
            return;
        }

        // Print the final solution matrix
        for (int i = 0; i < boardSize; i++) {
            for (int j = 0; j < boardSize; j++) {
                std::cout << (board[i][j] ? "Q " : ". ");
            }
            std::cout << "\n";
        }
    }
};

int main() {
    // Solving for a standard 4x4 chess allocation grid
    BacktrackingEngine engine(4);
    engine.executeNQueens();
    return 0;
}

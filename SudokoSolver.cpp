#include <iostream>

const int GRID_SIZE = 9;

void printGrid(int grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            std::cout << grid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Function to check if a number is already present in the row
bool isNumberInRow(int grid[GRID_SIZE][GRID_SIZE], int row, int number) {
    for (int col = 0; col < GRID_SIZE; ++col) {
        if (grid[row][col] == number) {
            return true;
        }
    }
    return false;
}

// Function to check if a number is already present in the column
bool isNumberInColumn(int grid[GRID_SIZE][GRID_SIZE], int col, int number) {
    for (int row = 0; row < GRID_SIZE; ++row) {
        if (grid[row][col] == number) {
            return true;
        }
    }
    return false;
}

// Function to check if a number is already present in the 3x3 grid
bool isNumberInBox(int grid[GRID_SIZE][GRID_SIZE], int startRow, int startCol, int number) {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (grid[row + startRow][col + startCol] == number) {
                return true;
            }
        }
    }
    return false;
}

// Function to check if a number can be placed at the given position
bool isSafe(int grid[GRID_SIZE][GRID_SIZE], int row, int col, int number) {
    return !isNumberInRow(grid, row, number) &&
           !isNumberInColumn(grid, col, number) &&
           !isNumberInBox(grid, row - row % 3, col - col % 3, number);
}

// Function to find the next empty cell in the grid
bool findEmptyCell(int grid[GRID_SIZE][GRID_SIZE], int& row, int& col) {
    for (row = 0; row < GRID_SIZE; ++row) {
        for (col = 0; col < GRID_SIZE; ++col) {
            if (grid[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

// Function to solve the Sudoku puzzle using backtracking
bool solveSudoku(int grid[GRID_SIZE][GRID_SIZE]) {
    int row, col;

    // Find the next empty cell
    if (!findEmptyCell(grid, row, col)) {
        // If no empty cell is found, the puzzle is solved
        return true;
    }

    // Try placing numbers from 1 to 9 in the empty cell
    for (int number = 1; number <= 9; ++number) {
        if (isSafe(grid, row, col, number)) {
            // Place the number in the empty cell
            grid[row][col] = number;

            // Recursively solve the remaining puzzle
            if (solveSudoku(grid)) {
                return true;
            }

            // If the solution fails, backtrack and try the next number
            grid[row][col] = 0;
        }
    }

    // If no number can be placed at the current cell, backtrack
    return false;
}

int main() {
    int grid[GRID_SIZE][GRID_SIZE] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(grid)) {
        std::cout << "Sudoku puzzle solved:" << std::endl;
        printGrid(grid);
    } else {
        std::cout << "Unable to solve the Sudoku puzzle!" << std::endl;
    }

    return 0;
}

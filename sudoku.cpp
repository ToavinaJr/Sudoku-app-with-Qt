#include "sudoku.h"
#include <algorithm>
#include <random>

Sudoku::Sudoku() {
    std::srand(std::time(0));
    std::fill(&grid[0][0], &grid[0][0] + 9 * 9, 0);
}

// Vérifie si un nombre peut être placé dans la case (row, col)
bool Sudoku::isSafe(int row, int col, int num) {
    // Vérification ligne et colonne
    for (int i = 0; i < 9; i++) {
        if (grid[row][i] == num || grid[i][col] == num)
            return false;
    }

    // Vérification bloc 3x3
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[startRow + i][startCol + j] == num)
                return false;

    return true;
}

// Remplissage de la grille avec un Sudoku valide (Backtracking)
bool Sudoku::fillGrid(int row, int col) {
    if (row == 9) return true; // Fin de la grille
    if (col == 9) return fillGrid(row + 1, 0); // Passer à la ligne suivante
    if (grid[row][col] != 0) return fillGrid(row, col + 1); // Case déjà remplie

    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::shuffle(numbers.begin(), numbers.end(), std::mt19937(std::random_device()()));

    for (int num : numbers) {
        if (isSafe(row, col, num)) {
            grid[row][col] = num;
            if (fillGrid(row, col + 1)) return true;
            grid[row][col] = 0; // Backtrack
        }
    }
    return false;
}

// Suppression de nombres pour créer un puzzle
void Sudoku::removeNumbers(int difficulty) {
    int count = difficulty; // Nombre de cases à vider
    while (count > 0) {
        int row = std::rand() % 9;
        int col = std::rand() % 9;
        if (grid[row][col] != 0) {
            grid[row][col] = 0;
            count--;
        }
    }
}


// Vérification si le nombre est valide à la position (row, col)
bool Sudoku::isValid(int num, int row, int col) {
    // Vérification ligne et colonne
    for (int i = 0; i < 9; i++) {
        if (grid[row][i] == num || grid[i][col] == num)
            return false;
    }

    // Vérification bloc 3x3
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[startRow + i][startCol + j] == num)
                return false;

    return true;
}

// Génération complète du Sudoku
void Sudoku::generateSudoku(int difficulty) {
    std::fill(&grid[0][0], &grid[0][0] + 9 * 9, 0);
    fillGrid();
    removeNumbers(difficulty);
}

// Retourne la grille sous forme de vecteur
std::vector<std::vector<int>> Sudoku::getGrid() {
    std::vector<std::vector<int>> sudokuGrid(9, std::vector<int>(9));
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            sudokuGrid[i][j] = grid[i][j];
    return sudokuGrid;
}

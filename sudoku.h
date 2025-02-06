#ifndef SUDOKU_H
#define SUDOKU_H

#include <vector>
#include <cstdlib>
#include <ctime>

class Sudoku {
private:
    int grid[9][9];

public:
    Sudoku();
    bool isSafe(int row, int col, int num);
    bool fillGrid(int row = 0, int col = 0);
    void removeNumbers(int difficulty);
    std::vector<std::vector<int>> getGrid();
    void generateSudoku(int difficulty = 40);
    bool isValid(int num, int row, int col); // Ajout de la méthode
};

#endif

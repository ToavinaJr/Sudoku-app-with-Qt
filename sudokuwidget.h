#ifndef SUDOKUWIDGET_H
#define SUDOKUWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>

#include "sudoku.h"

class SudokuWidget : public QWidget {
    Q_OBJECT

private:
    QGridLayout *gridLayout;
    QLineEdit *cells[9][9];
    QPushButton *generateButton;
    QPushButton *verifyButton;
    QPushButton *restartButton;

    QLabel *titleLabel;
    Sudoku sudoku;
    std::vector<std::vector<int>> initialGrid; // Pour stocker l'état initial

public:
    SudokuWidget(QWidget *parent = nullptr);
    void updateGrid();
    bool verifySudoku();
    void highlightErrors();

private slots:
    void generateSudoku();
    void checkSudoku();
    void resetToInitial();
};

#endif

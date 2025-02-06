#include <QApplication>
#include "sudokuwidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    SudokuWidget window;
    window.setWindowTitle("Sudoku - Qt App");
    window.setMinimumSize(500, 600);
    window.show();

    return app.exec();
}

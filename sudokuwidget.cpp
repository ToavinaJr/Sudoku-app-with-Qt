#include "sudokuwidget.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QValidator>

SudokuWidget::SudokuWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Titre
    titleLabel = new QLabel("Sudoku", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #444;");

    // Grille de Sudoku
    gridLayout = new QGridLayout();
    gridLayout->setSpacing(0); // Réduit l'espacement entre les cellules

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            cells[row][col] = new QLineEdit(this);
            cells[row][col]->setFixedSize(50, 50);
            cells[row][col]->setAlignment(Qt::AlignCenter);

            // Calcul des positions dans la grille 3x3
            bool isTopEdge = (row % 3 == 0);
            bool isLeftEdge = (col % 3 == 0);
            bool isBottomEdge = (row % 3 == 2) || (row == 8);
            bool isRightEdge = (col % 3 == 2) || (col == 8);

            // Construction du style avec des bordures plus épaisses aux limites des blocs 3x3
            QString borderStyle = QString(
                                      "QLineEdit {"
                                      "border-top: %1;"
                                      "border-left: %2;"
                                      "border-bottom: %3;"
                                      "border-right: %4;"
                                      "font-size: 28px;"
                                      "font-weight: bold;"
                                      "font-family: Arial, sans-serif;"
                                      "background-color: #ffffff;"
                                      "color: #000;"
                                      "padding: 0;"
                                      "margin: 0;"
                                      ).arg(isTopEdge ? "2px solid black" : "1px solid #888")
                                      .arg(isLeftEdge ? "2px solid black" : "1px solid #888")
                                      .arg(isBottomEdge ? "2px solid black" : "1px solid #888")
                                      .arg(isRightEdge ? "2px solid black" : "1px solid #888");

            borderStyle += "}";

            // Application du style
            cells[row][col]->setStyleSheet(borderStyle);

            // Validator pour les chiffres 1-9
            QValidator *validator = new QIntValidator(1, 9, this);
            cells[row][col]->setValidator(validator);

            gridLayout->addWidget(cells[row][col], row, col);
        }
    }

    // Boutons
    generateButton = new QPushButton("Générer Sudoku", this);
    verifyButton = new QPushButton("Vérifier Sudoku", this);

    generateButton->setStyleSheet(
        "background-color: #28a745; color: white; font-size: 16px; "
        "padding: 10px; border-radius: 8px;"
        );
    verifyButton->setStyleSheet(
        "background-color: #007bff; color: white; font-size: 16px; "
        "padding: 10px; border-radius: 8px;"
        );

    restartButton = new QPushButton("Rejouer");

    // Connecter le signal clicked du bouton Rejouer
    connect(restartButton, &QPushButton::clicked, this, &SudokuWidget::resetToInitial);
    connect(generateButton, &QPushButton::clicked, this, &SudokuWidget::generateSudoku);
    connect(verifyButton, &QPushButton::clicked, this, &SudokuWidget::checkSudoku);


    // Ajout des widgets au layout principal
    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(gridLayout);
    mainLayout->addWidget(generateButton);
    mainLayout->addWidget(verifyButton);

    setLayout(mainLayout);
    setStyleSheet("background-color: #f8f9fa; padding: 20px;");
}

void SudokuWidget::generateSudoku() {
    sudoku.generateSudoku(40); // Générer un Sudoku avec une difficulté moyenne
    updateGrid();

    QMessageBox msgBox;
    msgBox.setWindowTitle("Sudoku");
    msgBox.setText("Sudoku généré avec succès !");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setMinimumWidth(400); // Largeur minimale pour éviter que le texte soit écrasé

    // Appliquer un style CSS amélioré
    msgBox.setStyleSheet(
        "QLabel {"
        "   font-size: 18px;"
        "   font-weight: bold;"
        "   color: #2E86C1;" // Bleu moderne
        "   padding: 10px;"
        "   min-width: 300px;" // Largeur minimale pour le texte
        "}" "QMessageBox {"
        "   background-color: #F4F6F7;" // Gris clair
        "   border-radius: 10px;"
        "}"
        "QPushButton {"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "   padding: 8px 16px;"
        "   border-radius: 5px;"
        "   background-color: #2E86C1;" // Bleu moderne
        "   color: white;"
        "}"
        "QPushButton:hover {"
        "   background-color: #1A5276;" // Bleu foncé au survol
        "}"
        );

    msgBox.exec();
}

void SudokuWidget::resetToInitial() {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            int value = initialGrid[row][col];

            // Détermine les bordures des blocs 3x3
            bool isTopEdge = (row % 3 == 0);
            bool isLeftEdge = (col % 3 == 0);
            bool isBottomEdge = (row % 3 == 2) || (row == 8);
            bool isRightEdge = (col % 3 == 2) || (col == 8);

            QString baseStyle = QString(
                                    "QLineEdit {"
                                    "border-top: %1;"
                                    "border-left: %2;"
                                    "border-bottom: %3;"
                                    "border-right: %4;"
                                    "font-size: 28px;"
                                    "font-weight: bold;"
                                    "font-family: Arial, sans-serif;"
                                    "%5"
                                    "padding: 0;"
                                    "margin: 0;"
                                    "}"
                                    ).arg(
                                            isTopEdge ? "2px solid black" : "1px solid #888",
                                            isLeftEdge ? "2px solid black" : "1px solid #888",
                                            isBottomEdge ? "2px solid black" : "1px solid #888",
                                            isRightEdge ? "2px solid black" : "1px solid #888",
                                            value != 0 ? "background-color: #e8e8e8; color: #000000;"
                                                       : "background-color: #ffffff; color: #0066cc;"
                                        );

            if (value != 0) {
                cells[row][col]->setText(QString::number(value));
                cells[row][col]->setReadOnly(true);
            } else {
                cells[row][col]->setText("");
                cells[row][col]->setReadOnly(false);
            }
            cells[row][col]->setStyleSheet(baseStyle);
        }
    }
}


void SudokuWidget::updateGrid() {
    std::vector<std::vector<int>> grid = sudoku.getGrid();
    initialGrid = grid;

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            int value = grid[row][col];

            // Détermine les bordures des blocs 3x3
            bool isTopEdge = (row % 3 == 0);
            bool isLeftEdge = (col % 3 == 0);
            bool isBottomEdge = (row % 3 == 2) || (row == 8);
            bool isRightEdge = (col % 3 == 2) || (col == 8);

            // Construction du style de base
            QString baseStyle = QString(
                                    "QLineEdit {"
                                    "border-top: %1;"
                                    "border-left: %2;"
                                    "border-bottom: %3;"
                                    "border-right: %4;"
                                    "font-size: 28px;"
                                    "font-weight: bold;"
                                    "font-family: Arial, sans-serif;"
                                    "%5" // Placeholder pour background-color
                                    "color: %6;" // Placeholder pour text color
                                    "padding: 0;"
                                    "margin: 0;"
                                    "}"
                                    ).arg(
                                            isTopEdge ? "2px solid black" : "1px solid #888",
                                            isLeftEdge ? "2px solid black" : "1px solid #888",
                                            isBottomEdge ? "2px solid black" : "1px solid #888",
                                            isRightEdge ? "2px solid black" : "1px solid #888"
                                        );

            if (value != 0) {
                // Cases préremplies
                cells[row][col]->setText(QString::number(value));
                cells[row][col]->setReadOnly(true);
                cells[row][col]->setStyleSheet(
                    baseStyle.arg("background-color: #e8e8e8;", "#000000")
                );
            } else {
                // Cases vides à remplir par l'utilisateur
                cells[row][col]->setText("");
                cells[row][col]->setReadOnly(false);
                cells[row][col]->setStyleSheet(
                    baseStyle.arg("background-color: #ffffff;", "#0066cc")
                );
            }
        }
    }
}


void SudokuWidget::checkSudoku() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Sudoku");

    if (verifySudoku()) {
        msgBox.setText("Bravo ! Sudoku Correct !");
        msgBox.setIcon(QMessageBox::Information);
    } else {
        msgBox.setText("Erreur ! Vérifie ta solution.");
        msgBox.setIcon(QMessageBox::Warning);
        highlightErrors();  // Met en évidence les cases incorrectes
    }

    // Appliquer un style CSS au message box
    msgBox.setStyleSheet(
        "QLabel{font-size: 18px; font-weight: bold; color: red;}"
        "QPushButton{font-size: 16px; padding: 8px;}"
        );

    msgBox.exec();
}

bool SudokuWidget::verifySudoku() {
    bool hasEmptyCells = false;

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (cells[row][col]->text().isEmpty()) {
                hasEmptyCells = true;
                continue; // Continue au lieu de retourner false directement
            }
            int value = cells[row][col]->text().toInt();
            if (!sudoku.isValid(value, row, col)) {
                return false;
            }
        }
    }

    return !hasEmptyCells; // Si une case est vide, return false, sinon true
}


void SudokuWidget::highlightErrors() {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            // Calcul des bordures 3x3
            bool isTopEdge = (row % 3 == 0);
            bool isLeftEdge = (col % 3 == 0);
            bool isBottomEdge = (row % 3 == 2) || (row == 8);
            bool isRightEdge = (col % 3 == 2) || (col == 8);

            // Construction du style de base avec les bordures
            QString baseStyle = QString(
                "QLineEdit {"
                "border-top: %1;"
                "border-left: %2;"
                "border-bottom: %3;"
                "border-right: %4;"
                "font-size: 28px;"
                "font-weight: bold;"
                "font-family: Arial, sans-serif;"
                "%5" // Placeholder pour background-color et autres styles
                "padding: 0;"
                "margin: 0;"
                "}"
            ).arg(
                isTopEdge ? "2px solid black" : "1px solid #888",
                isLeftEdge ? "2px solid black" : "1px solid #888",
                isBottomEdge ? "2px solid black" : "1px solid #888",
                isRightEdge ? "2px solid black" : "1px solid #888"
            );

            if (!cells[row][col]->text().isEmpty()) {
                int value = cells[row][col]->text().toInt();
                if (!sudoku.isValid(value, row, col)) {
                    // Style pour les cases incorrectes
                    cells[row][col]->setStyleSheet(
                        baseStyle.arg(
                            "background-color: #ffdddd;"
                            "color: red;"
                            )
                        );
                } else {
                    // Restaurer le style normal pour les cases correctes
                    bool isPrefilledCell = cells[row][col]->isReadOnly();
                    if (isPrefilledCell) {
                        cells[row][col]->setStyleSheet(
                            baseStyle.arg(
                                "background-color: #e8e8e8;"
                                "color: #000000;"
                                )
                            );
                    } else {
                        cells[row][col]->setStyleSheet(
                            baseStyle.arg(
                                "background-color: #ffffff;"
                                "color: #0066cc;"
                                )
                            );
                    }
                }
            }
        }
    }
}

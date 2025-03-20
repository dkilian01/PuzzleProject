#include "PuzzleProject.h"
#include <QVBoxLayout>

PuzzleProject::PuzzleProject(QWidget* parent)
    : QMainWindow(parent) 
{
    boardSize = 6;
    board = new PuzzleBoard(boardSize);
    ui.setupUi(this);
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    gridLayout = new QGridLayout();
    mainLayout->addLayout(gridLayout);




    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            QPushButton* button = new QPushButton(this);
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            buttons.append(button);
            gridLayout->addWidget(button, i, j);
            connect(button, &QPushButton::clicked, this, &PuzzleProject::onTileClicked);
        }
    }
    updateBoard();
}

PuzzleProject::~PuzzleProject()
{
    delete board;
}

void PuzzleProject::updateBoard() {
    for (int i = 0; i < boardSize; i++)
        for (int j = 0; j < boardSize; j++)
            buttons[i * boardSize + j]->setText(board->getBoard()[i][j] == 0 ? "" : QString::number(board->getBoard()[i][j]));
}

void PuzzleProject::onTileClicked() {
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    if (!clickedButton) return;

    int index = buttons.indexOf(clickedButton);
    board->move(index / boardSize, index % boardSize);
    updateBoard();
}


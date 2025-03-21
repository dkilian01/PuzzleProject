#include "PuzzleProject.h"
#include <QVBoxLayout>
#include<QMessageBox>
PuzzleProject::PuzzleProject(int boardSize,QWidget* parent)
    : QMainWindow(parent),boardSize(boardSize)
{
  
    board = new PuzzleBoard(boardSize);
    board->changeBoard();
    ui.setupUi(this);
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    gridLayout = new QGridLayout();
    mainLayout->addLayout(gridLayout);

    timeLabel = new QLabel("Czas: 0.0s", this);
    mainLayout->addWidget(timeLabel);

    time = new QTimer(this);
    connect(time, &QTimer::timeout, this, &PuzzleProject::updateTime);
    time->start(100);


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
            buttons[i * boardSize + j]->setText(board->getBoard()[i][j] == boardSize*boardSize ? "" : QString::number(board->getBoard()[i][j]));
}

void PuzzleProject::onTileClicked() {
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    if (!clickedButton) return;

    int index = buttons.indexOf(clickedButton);
    board->move(index / boardSize, index % boardSize);
    updateBoard();

    if (board->isSolved())
    {
        time->stop();
        timeLabel->setText("Gratulacje! Czas:" + QString::number(board->getTime()));
        QMessageBox::information(this, "Ukonczone", "Bravo!: Czas" + QString::number(board->getTime()));
    }
}

void PuzzleProject::updateTime() {
    timeLabel->setText("Czas:" + QString::number(board->getTime()));
}

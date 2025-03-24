#include "PuzzleProject.h"
#include "Player.h"
#include "StatisticsDialog.h"
#include "RankDialog.h"
#include <QVBoxLayout>
#include <QMessageBox>

PuzzleProject::PuzzleProject(int boardSize,Player player,QWidget* parent)
    : QMainWindow(parent),boardSize(boardSize),player(player)
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

    testLabel = new QLabel("Czas: 0.0s", this);
    mainLayout->addWidget(testLabel);
    testLabel->setText("Step:");
    createControlButtons(mainLayout);

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
        for (int j = 0; j < boardSize; j++) {
            //buttons[i * boardSize + j]->setText(board->getBoard()[i][j] == boardSize*boardSize ? "" : QString::number(board->getBoard()[i][j]));
            QPushButton* btn = buttons[i * boardSize + j];
            int val = board->getBoard()[i][j];
            btn->setText(val == boardSize * boardSize ? "" : QString::number(val));
        }
   
    testLabel->setText("Step:" + QString::number(board->getStep()));
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
        double t = board->getTime();
        timeLabel->setText("Gratulacje! Czas:" + QString::number(t));
        QMessageBox::information(this, "Ukonczone", "Bravo!: Czas" + QString::number(t));
        player.setScore(t, boardSize);

    }
}

void PuzzleProject::updateTime() {
    timeLabel->setText("Czas:" + QString::number(board->getTime()));
}

void PuzzleProject::closeEvent(QCloseEvent* event)
{
    player.saveToFile();

    event->accept();
}
void PuzzleProject::createControlButtons(QVBoxLayout* layout) {
    undoButton = new QPushButton("Cofnij", this);
    redoButton = new QPushButton("Przywroc", this);
    saveButton = new QPushButton("Zapisz gre", this);
    loadButton = new QPushButton("Wczytaj gre", this);
    themeButton = new QPushButton("Zmien motyw", this);
    statsButton = new QPushButton("Statystyki gracza", this);
    rankingButton = new QPushButton("Ranking graczy", this);

    layout->addWidget(undoButton);
    layout->addWidget(redoButton);
    layout->addWidget(saveButton);
    layout->addWidget(loadButton);
    layout->addWidget(themeButton);
    layout->addWidget(statsButton);
    layout->addWidget(rankingButton);

    connect(undoButton, &QPushButton::clicked, this, &PuzzleProject::handleUndo);
    connect(redoButton, &QPushButton::clicked, this, &PuzzleProject::handleRedo);
    connect(saveButton, &QPushButton::clicked, this, &PuzzleProject::handleSave);
    connect(loadButton, &QPushButton::clicked, this, &PuzzleProject::handleLoad);
    connect(themeButton, &QPushButton::clicked, this, &PuzzleProject::handleThemeToggle);
    connect(statsButton, &QPushButton::clicked, [this]() {
        StatisticsDialog dlg(player, this);
        dlg.exec();
        });
    connect(rankingButton, &QPushButton::clicked, [this]() {
        RankDialog dlg(this);
        dlg.exec();
        });
}

void PuzzleProject::handleUndo() {
    if (board->canUndo()) {
        board->undoMove();
        updateBoard();
    }
}

void PuzzleProject::handleRedo() {
    if (board->canRedo()) {
        board->redoMove();
        updateBoard();
    }
}

void PuzzleProject::handleSave() {
    board->saveState("savegame.txt");
    QMessageBox::information(this, "Zapisano", "Stan gry zosta³ zapisany.");
}

void PuzzleProject::handleLoad() {
    if (board->loadState("savegame.txt")) {
        updateBoard();
        QMessageBox::information(this, "Wczytano", "Stan gry zosta³ wczytany.");
    }
    else {
        QMessageBox::warning(this, "B³¹d", "Nie uda³o siê wczytaæ gry.");
    }
}

void PuzzleProject::handleThemeToggle() {
    darkMode = !darkMode;
    if (darkMode) {
        qApp->setStyleSheet("QWidget { background-color: #222; color: white; } QPushButton { background-color: #444; color: white; }");
    }
    else {
        qApp->setStyleSheet("");
    }
}
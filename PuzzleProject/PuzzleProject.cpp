#include "PuzzleProject.h"
#include "Player.h"
#include "StatisticsDialog.h"
#include "HexPuzzle.h"
#include "RankDialog.h"
#include <QVBoxLayout>
#include <QMessageBox>

PuzzleProject::PuzzleProject(PuzzleBase* board,Player player,QWidget* parent)
    : QMainWindow(parent),board(board),player(player)
{
    board->startTimer();
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
    

    /*for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            QPushButton* button = new QPushButton(this);
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            buttons.append(button);
            gridLayout->addWidget(button, i, j);
            connect(button, &QPushButton::clicked, this, &PuzzleProject::onTileClicked);
        }
    }*/
    createBoardLayout();
    updateBoard();
}

PuzzleProject::~PuzzleProject()
{
    delete board;
}

void PuzzleProject::updateBoard() {
    const auto& grid = board->getBoard();
    int maxVal = grid.size() * grid.size() + 1;
    bool isHex = dynamic_cast<HexPuzzle*>(board);
    int index = 0;

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            QPushButton* btn = buttons[index++];
            int val = grid[i][j];

            bool up = false;
            if (isHex) {
                if (i < grid.size() / 2) up = (j % 2 == 0);
                else up = (j % 2 == 1);
            }

            // Ustawienie maski trójk¹ta (zminimalizowany margines)
            if (isHex) {
                int w = btn->width();
                int h = btn->height();
                QPolygon triangle;
                if (up) {
                    triangle << QPoint(w / 2, 0) << QPoint(0, h) << QPoint(w, h);
                }
                else {
                    triangle << QPoint(0, 0) << QPoint(w, 0) << QPoint(w / 2, h);
                }
                btn->setMask(QRegion(triangle));
            }
            else {
                btn->clearMask();
            }

            if (val == maxVal - 1 || val == maxVal) {
                btn->setText("");
                btn->setStyleSheet("background-color: #cccccc; border: none;");
            }
            else {
                QString color = up ? "#4CAF50" : "#2196F3";
                btn->setText(QString::number(val));
                btn->setStyleSheet(
                    "background-color: " + color + ";"
                    "color: white;"
                    "font-weight: bold;"
                    "font-size: 14px;"
                    "border: none;"
                    "margin: 0px;"
                    "padding: 0px;"
                );
            }
        }
    }
}


void PuzzleProject::onTileClicked() {
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    if (!clickedButton) return;
    int index = buttons.indexOf(clickedButton);


    const auto& grid = board->getBoard();
    board->move(index);
    testLabel->setText("X:" + QString::number(board->getX()) + " Y:" + QString::number(board->getY()) + " button" + QString::number(index));
    
   
    updateBoard();

    if (board->isSolved())
    {
        time->stop();
        double t = board->getTime();
        timeLabel->setText("Gratulacje! Czas:" + QString::number(t));
        QMessageBox::information(this, "Ukonczone", "Bravo!: Czas" + QString::number(t));
        player.setScore(t, board->getBoard().size());

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

void PuzzleProject::createBoardLayout() {
    const auto& grid = board->getBoard();
    buttons.clear();

    while (QLayoutItem* item = gridLayout->takeAt(0)) {
        delete item->widget();
        delete item;
    }

    gridLayout->setSpacing(0); 

    int maxWidth = 0;
    for (const auto& row : grid)
        maxWidth = std::max(maxWidth, static_cast<int>(row.size()));

    int index = 0;
    for (int i = 0; i < grid.size(); ++i) {
        int rowSize = grid[i].size();
        int offset = (maxWidth - rowSize) / 2;

        for (int j = 0; j < rowSize; ++j) {
            QPushButton* button = new QPushButton(this);
            button->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
            button->setMinimumSize(40, 40);  // dopasowanie
            buttons.append(button);
            gridLayout->addWidget(button, i, j + offset);
            connect(button, &QPushButton::clicked, this, &PuzzleProject::onTileClicked);
        }
    }

    this->update(); // dla masek
}

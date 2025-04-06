#include "PuzzleProject.h"
#include "Player.h"
#include "StatisticsDialog.h"
#include "HexPuzzle.h"
#include "RankDialog.h"
#include <QVBoxLayout>
#include <QMessageBox>
using namespace std;
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
    if (dynamic_cast<HexPuzzle*>(board)) {
        updateBoardHex();
    }
    else {
        updateBoardClassic();
    }
    
}
void PuzzleProject::updateBoardClassic()
{
    const auto& grid = board->getBoard();
    int index = 0;
    int maxV = grid.size() * grid.size();
    //testLabel->setText(QString::number(grid.size()));
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid.size(); j++) {
            QPushButton* btn = buttons[index++];
            int val = grid[i][j];

            if (val == maxV) {
                btn->setText("");
                btn->setStyleSheet("background-color: #cccccc;");
            }
            else {
                btn->setText(QString::number(val));
                btn->setStyleSheet("background-color: #aaffaa;");
            }
        }
    }
}
void PuzzleProject::updateBoardHex() {

    const auto& grid = board->getBoard();
    //testLabel->setText(QString::number(grid.size()));
    int maxVal = 0;
    if (HexPuzzle* h = dynamic_cast<HexPuzzle*>(board)) {
        maxVal=h->getTileAmount();
    }
    //maxVal = ((grid.size()) * ((grid.size() * 3) )) / 2; // wzór na liczbe pol w polu hexagonalnym
    int index = 0;

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            QPushButton* btn = buttons[index++];
            int val = grid[i][j];

            
            bool up = (i < grid.size() / 2) ? (j % 2 == 0) : (j % 2 == 1);

            // Maska trójk¹ta
            int w = btn->width();
            int h = btn->height();
            QPolygon triangle;
            if (w > 0 && h > 0) {
                triangle = up
                    ? QPolygon({ QPoint(w / 2, 0), QPoint(0, h), QPoint(w, h) })
                    : QPolygon({ QPoint(0, 0), QPoint(w, 0), QPoint(w / 2, h) });
                btn->setMask(QRegion(triangle));
            }

            if (val == maxVal-2 || val == maxVal - 1) {
                btn->setText(QString::number(val));
                btn->setStyleSheet("background-color: #cccccc; border: none;");
            }
            else {
                QString color = up ? "#4CAF50" : "#2196F3";
                btn->setText(QString::number(val));
                btn->setStyleSheet(
                    "background-color: " + color + ";"
                    "color: white;"
                    "font-weight: bold;"
                    "font-size: 16px;"
                    "border: none;"
                    "margin: 0px; padding: 0px;");
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

        player.setScore(t, board->getSize(), (dynamic_cast<HexPuzzle*>(board) ? "hex" : "classic"));
        deactivateButtons();
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
    backButton = new QPushButton("Powrot do menu", this);

    layout->addWidget(undoButton);
    layout->addWidget(redoButton);
    layout->addWidget(saveButton);
    layout->addWidget(loadButton);
    layout->addWidget(themeButton);
    layout->addWidget(statsButton);
    layout->addWidget(rankingButton);
    layout->addWidget(backButton);

    connect(undoButton, &QPushButton::clicked, this, &PuzzleProject::handleUndo);
    connect(redoButton, &QPushButton::clicked, this, &PuzzleProject::handleRedo);
    connect(saveButton, &QPushButton::clicked, this, &PuzzleProject::handleSave);
    connect(loadButton, &QPushButton::clicked, this, &PuzzleProject::handleLoad);
    connect(themeButton, &QPushButton::clicked, this, &PuzzleProject::handleThemeToggle);
    connect(backButton, &QPushButton::clicked, this, &PuzzleProject::handleBackToMenu);
    connect(statsButton, &QPushButton::clicked, [this]() {
        StatisticsDialog dlg(player, this);
        dlg.exec();
        });
    connect(rankingButton, &QPushButton::clicked, [this]() {
        RankDialog dlg(this);
        dlg.exec();
        });

}
void PuzzleProject::handleBackToMenu() {
    player.saveToFile(); // zapisz dane gracza
    emit returnToMenu(); // sygnalizuj powrót do menu
    this->close();
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
    
    board->saveState(player.getPlayerName() + "_"+ to_string(board->getBoard().size())+"_"
    + (dynamic_cast<HexPuzzle*>(board) ? "hex" : "classic") +"_save.txt");
    QMessageBox::information(this, "Zapisano", "Stan gry zosta³ zapisany.");
}

void PuzzleProject::handleLoad() {
    if (board->loadState(player.getPlayerName() + "_" + to_string(board->getBoard().size()) + "_"
        + (dynamic_cast<HexPuzzle*>(board) ? "hex" : "classic") + "_save.txt"))
    {
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

    gridLayout->setSpacing(1); 

    int maxWidth = 0;
    for (const auto& row : grid)
        maxWidth = std::max(maxWidth, static_cast<int>(row.size()));

    int index = 0;
    for (int i = 0; i < grid.size(); ++i) {
        int rowSize = grid[i].size();
        int offset = (maxWidth - rowSize) / 2;

        for (int j = 0; j < rowSize; ++j) {
            QPushButton* button = new QPushButton(this);
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            button->setMinimumSize(50, 50); // wiêksze trójk¹ty
            buttons.append(button);
            gridLayout->addWidget(button, i, j + offset);
            connect(button, &QPushButton::clicked, this, &PuzzleProject::onTileClicked);
        }
    }

    this->update();
}
void PuzzleProject::deactivateButtons() {
    for (QPushButton* btn : buttons)
        btn->setEnabled(false); // pola planszy

    undoButton->setEnabled(false);
    redoButton->setEnabled(false);
    saveButton->setEnabled(false);
    loadButton->setEnabled(false);

}
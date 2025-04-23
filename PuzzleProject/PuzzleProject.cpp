#include "PuzzleProject.h"
#include "StatisticsDialog.h"
#include "RankDialog.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QThread>
#include <QApplication>

PuzzleProject::PuzzleProject(GameLogic* logic, QWidget* parent)
    : QMainWindow(parent), logic(logic) {
    ui.setupUi(this);

    // G³ówne okno aplikacji – widget centralny
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    // Tworzymy uk³ad siatki do rozmieszczenia kafelków planszy
    gridLayout = new QGridLayout();
    mainLayout->addLayout(gridLayout);

    timeLabel = new QLabel("Czas: 0.0s", this);
    mainLayout->addWidget(timeLabel);

    testLabel = new QLabel("Step:", this);
    mainLayout->addWidget(testLabel);

    // Tworzenie przycisków kontrolnych (zapis, cofnij itd.)
    createControlButtons(mainLayout);

    // Timer do aktualizacji zegara co 100 ms
    time = new QTimer(this);
    connect(time, &QTimer::timeout, this, &PuzzleProject::updateTime);
    time->start(100);

    // Inicjalizacja uk³adu planszy
    createBoardLayout();
    updateBoard();
}

PuzzleProject::~PuzzleProject() {}

// Aktualizacja planszy w zale¿noœci od typu
void PuzzleProject::updateBoard() {
    logic->getBoardType() == "hex" ? updateBoardHex() : updateBoardClassic();
}

// Aktualizacja klasycznej planszy (kwadratowe przyciski)
void PuzzleProject::updateBoardClassic() {
    const auto& grid = logic->getBoard();
    int index = 0;
    int maxV = grid.size() * grid.size();

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

// Aktualizacja planszy heksagonalnej (z trójk¹tnymi przyciskami)
void PuzzleProject::updateBoardHex() {
    const auto& grid = logic->getBoard();
    int maxVal = logic->getMaxTileValue();
    int index = 0;

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            QPushButton* btn = buttons[index++];
            int val = grid[i][j];

            bool up = (i < grid.size() / 2) ? (j % 2 == 0) : (j % 2 == 1);

            int w = btn->width();
            int h = btn->height();
            QPolygon triangle;
            if (w > 0 && h > 0) {
                triangle = up ? QPolygon({ QPoint(w / 2, 0), QPoint(0, h), QPoint(w, h) })
                    : QPolygon({ QPoint(0, 0), QPoint(w, 0), QPoint(w / 2, h) });
                btn->setMask(QRegion(triangle));
            }

            if (val == maxVal - 2 || val == maxVal - 1) {
                btn->setText("");
                btn->setStyleSheet("background-color: #cccccc; border: none;");
            }
            else {
                QString color = up ? "#4CAF50" : "#2196F3";
                btn->setText(QString::number(val));
                btn->setStyleSheet("background-color: " + color + "; color: white; font-weight: bold; font-size: 16px; border: none; margin: 0px; padding: 0px;");
            }
        }
    }
}

// Obs³uga klikniêcia w przycisk kafelka
void PuzzleProject::onTileClicked() {
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    if (!clickedButton) return;
    int index = buttons.indexOf(clickedButton);

    logic->move(index);
    updateBoard();

    // Jeœli gra zosta³a ukoñczona
    if (logic->isSolved()) {
        time->stop();
        double t = logic->getTime();
        timeLabel->setText("Gratulacje! Czas:" + QString::number(t));
        QMessageBox::information(this, "Ukonczone", "Bravo!: Czas" + QString::number(t));

        logic->recordWin(t);
        deactivateButtons();
    }
}

// Aktualizacja zegara gry
void PuzzleProject::updateTime() {
    timeLabel->setText("Czas:" + QString::number(logic->getTime()));
}

// Zapisanie danych gracza przy zamykaniu okna
void PuzzleProject::closeEvent(QCloseEvent* event) {
    logic->getPlayer().saveToFile();
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

    // Podpinanie akcji do przycisków
    connect(undoButton, &QPushButton::clicked, this, &PuzzleProject::handleUndo);
    connect(redoButton, &QPushButton::clicked, this, &PuzzleProject::handleRedo);
    connect(saveButton, &QPushButton::clicked, this, &PuzzleProject::handleSave);
    connect(loadButton, &QPushButton::clicked, this, &PuzzleProject::handleLoad);
    connect(themeButton, &QPushButton::clicked, this, &PuzzleProject::handleThemeToggle);
    connect(backButton, &QPushButton::clicked, this, &PuzzleProject::handleBackToMenu);
    connect(statsButton, &QPushButton::clicked, [this]() {
        StatisticsDialog dlg(logic->getPlayer(), this);
        dlg.exec();
        });
    connect(rankingButton, &QPushButton::clicked, [this]() {
        RankDialog dlg(this);
        dlg.exec();
        });

}

// Powrót do menu startowego
void PuzzleProject::handleBackToMenu() {
    logic->getPlayer().saveToFile();
    emit returnToMenu();
    close();
}

// Obs³uga przycisków cofania/przywracania
void PuzzleProject::handleUndo() {
    if (logic->canUndo()) {
        logic->undo();
        updateBoard();
    }
}

void PuzzleProject::handleRedo() {
    if (logic->canRedo()) {
        logic->redo();
        updateBoard();
    }
}

// Zapis i wczytanie stanu gry
void PuzzleProject::handleSave() {
    logic->saveState();
    QMessageBox::information(this, "Zapisano", "Stan gry zosta³ zapisany.");
}

void PuzzleProject::handleLoad() {
    if (logic->loadState()) {
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

// Tworzy uk³ad przycisków kafelków planszy
void PuzzleProject::createBoardLayout() {
    const auto& grid = logic->getBoard();
    buttons.clear();

    // Usuwanie poprzednich przycisków z siatki
    while (QLayoutItem* item = gridLayout->takeAt(0)) {
        delete item->widget();
        delete item;
    }

    gridLayout->setSpacing(1);

    // Ustalanie maksymalnej szerokoœci wiersza
    int maxWidth = 0;
    for (const auto& row : grid)
        maxWidth = std::max(maxWidth, static_cast<int>(row.size()));

    // Tworzenie przycisków i dodanie ich do uk³adu
    int index = 0;
    for (int i = 0; i < grid.size(); ++i) {
        int rowSize = grid[i].size();
        int offset = (maxWidth - rowSize) / 2;

        for (int j = 0; j < rowSize; ++j) {
            QPushButton* button = new QPushButton(this);
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            button->setMinimumSize(50, 50);
            buttons.append(button);
            gridLayout->addWidget(button, i, j + offset);
            connect(button, &QPushButton::clicked, this, &PuzzleProject::onTileClicked);
        }
    }

    this->update();
}

// Dezaktywacja przycisków po ukoñczeniu gry
void PuzzleProject::deactivateButtons() {
    for (QPushButton* btn : buttons)
        btn->setEnabled(false);

    undoButton->setEnabled(false);
    redoButton->setEnabled(false);
    saveButton->setEnabled(false);
    loadButton->setEnabled(false);
}

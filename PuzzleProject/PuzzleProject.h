#pragma once
#include <QtWidgets/QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QCloseEvent>
#include<string>
#include "ui_PuzzleProject.h"
#include "PuzzleBoard.h"
#include "Player.h"

/**
 * @brief Klasa GUI zarz¹dzaj¹ca interfejsem gry Puzzle.
 */
class PuzzleProject : public QMainWindow
{
    Q_OBJECT

public:
    PuzzleProject(PuzzleBase* board, Player player, QWidget* parent = nullptr);
    ~PuzzleProject();
protected:
    void closeEvent(QCloseEvent* event)override;

private:
    Ui::PuzzleProjectClass ui;
    PuzzleBase* board;
    Player player;

    QGridLayout* gridLayout;
    QVector<QPushButton*> buttons;

    QLabel* timeLabel;
    QLabel* testLabel;
    QTimer* time;

    int boardSize;

    void updateBoard();
    void updateBoardClassic();
    void updateBoardHex();
    void createBoardLayout();

    QPushButton* undoButton;
    QPushButton* redoButton;
    QPushButton* saveButton;
    QPushButton* loadButton;
    QPushButton* themeButton;
    QPushButton* statsButton;
    QPushButton* rankingButton;
    QPushButton* backButton;

    bool darkMode = false;

    void createControlButtons(QVBoxLayout* layout);
    void deactivateButtons();

private slots:
    void onTileClicked();
    void updateTime();

    void handleUndo();
    void handleRedo();
    void handleSave();
    void handleLoad();
    void handleThemeToggle();
    void handleBackToMenu();
signals:
    void returnToMenu();
};

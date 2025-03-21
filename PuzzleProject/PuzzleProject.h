#pragma once
#include <QtWidgets/QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QCloseEvent>
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
    PuzzleProject(int boardSize, Player player, QWidget* parent = nullptr);
    ~PuzzleProject();
protected:
    void closeEvent(QCloseEvent* event)override;

private:
    Ui::PuzzleProjectClass ui;
    PuzzleBoard* board;
    Player player;
    QGridLayout* gridLayout;
    QVector<QPushButton*> buttons;

    QLabel* timeLabel;
    QLabel* testLabel;
    QTimer* time;

    int boardSize;

    void updateBoard();

private slots:
    void onTileClicked();
    void updateTime();
};

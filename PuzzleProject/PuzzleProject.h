#pragma once
#include <QtWidgets/QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include "ui_PuzzleProject.h"
#include "PuzzleBoard.h"

/**
 * @brief Klasa GUI zarz¹dzaj¹ca interfejsem gry Puzzle.
 */
class PuzzleProject : public QMainWindow
{
    Q_OBJECT

public:
    PuzzleProject(QWidget* parent = nullptr);
    ~PuzzleProject();

private:
    Ui::PuzzleProjectClass ui;
    PuzzleBoard* board;
    QGridLayout* gridLayout;
    QVector<QPushButton*> buttons;

    QLabel* timeLabel;
    QTimer* time;

    int boardSize;

    void updateBoard();

private slots:
    void onTileClicked();
    void updateTime();
};

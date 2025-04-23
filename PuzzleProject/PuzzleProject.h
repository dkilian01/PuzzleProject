#pragma once
#include <QtWidgets/QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QCloseEvent>
#include "ui_PuzzleProject.h"
#include "GameLogic.h"

class PuzzleProject : public QMainWindow {
    Q_OBJECT

public:
    PuzzleProject(GameLogic* logic, QWidget* parent = nullptr);
    ~PuzzleProject();

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    Ui::PuzzleProjectClass ui;
    GameLogic* logic;

    QGridLayout* gridLayout;
    QVector<QPushButton*> buttons;
    QLabel* timeLabel;
    QLabel* testLabel;
    QTimer* time;

    QPushButton* undoButton;
    QPushButton* redoButton;
    QPushButton* saveButton;
    QPushButton* loadButton;
    QPushButton* themeButton;
    QPushButton* statsButton;
    QPushButton* rankingButton;
    QPushButton* backButton;


    bool darkMode = false;

    void updateBoard();
    void updateBoardClassic();
    void updateBoardHex();
    void createBoardLayout();
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

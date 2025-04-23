/**
 * @file PuzzleProject.h
 * @brief G³ówne okno GUI zarz¹dzaj¹ce gr¹ puzzle.
 *
 * Klasa odpowiada za wyœwietlanie planszy, kontrolki interfejsu.
 */
#pragma once
#include <QtWidgets/QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <QCloseEvent>
#include "ui_PuzzleProject.h"
#include "GameLogic.h"
 /**
  * @class PuzzleProject
  * @brief Klasa GUI zarz¹dzaj¹ca interfejsem gry Puzzle.
  */
class PuzzleProject : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Konstruktor g³ównego okna gry.
     * @param logic WskaŸnik na obiekt logiki gry (GameLogic).
     * @param parent WskaŸnik na okno nadrzêdne (domyœlnie nullptr).
     */
    PuzzleProject(GameLogic* logic, QWidget* parent = nullptr);

    /**
     * @brief Destruktor.
     */
    ~PuzzleProject();

protected:
    /**
     * @brief Obs³uga zamykania okna - zapisuje dane gracza.
     * @param event Zdarzenie zamkniêcia okna.
     */
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

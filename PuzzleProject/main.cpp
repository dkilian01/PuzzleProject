#include "PuzzleProject.h"
#include "Player.h"
#include "StartDialog.h"
#include "HexPuzzle.h"
#include <QtWidgets/QApplication>
#include<iostream>
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    while (true) {
        StartDialog dialog;
        if (dialog.exec() != QDialog::Accepted)break;

        int size = dialog.getBoardSize();
        QString playerName = dialog.getSelectedPlayer();
        Player player(playerName.toStdString());
        QString type = dialog.getBoardType();
        PuzzleBase* board = nullptr;

        if (type == "Klasyczna") {
            board = new PuzzleBoard(size);
            //static_cast<PuzzleBoard*>(board)->changeBoard();
        }
        else if (type == "Heksagonalna") {
            board = new HexPuzzle(size);
            //static_cast<HexPuzzle*>(board)->changeBoard();
        }
        PuzzleProject* window = new PuzzleProject(board, player);

        bool powrotDoMenu = false;
        QObject::connect(window, &PuzzleProject::returnToMenu, [&]() {
            powrotDoMenu = true;
            window->close();  // zamykamy okno gry
            });
        window->show();
        a.exec(); // Uruchamia GUI    
        if (!powrotDoMenu)
            break;  // u¿ytkownik zamkn¹³ okno bez chêci powrotu
    }
    return 0;
}

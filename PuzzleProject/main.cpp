
#include "PuzzleProject.h"
#include "Player.h"
#include "StartDialog.h"
#include "HexPuzzle.h"
#include "PuzzleBoard.h"
#include "GameLogic.h"
#include <QtWidgets/QApplication>
#include <memory>
using namespace std;
int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    while (true) {
        StartDialog dialog;
        if (dialog.exec() != QDialog::Accepted) break;

        int size = dialog.getBoardSize();
        QString playerName = dialog.getSelectedPlayer();
        Player player(playerName.toStdString());
        QString type = dialog.getBoardType();

        unique_ptr<PuzzleBase> board;
        if (type == "Klasyczna") {
            board = make_unique<PuzzleBoard>(size);
            board->changeBoard();
        }
        else if (type == "Heksagonalna") {
            board = make_unique<HexPuzzle>(size);
            board->changeBoard();
        }

        GameLogic* logic = new GameLogic(move(board), player);
        logic->start();

        PuzzleProject* window = new PuzzleProject(logic);
        bool powrotDoMenu = false;

        QObject::connect(window, &PuzzleProject::returnToMenu, [&]() {
            logic->getPlayer().saveToFile();
            powrotDoMenu = true;
            window->close();
            });

        window->show();
        a.exec();

        delete window;
        delete logic;

        if (!powrotDoMenu) break;
    }
    return 0;
}

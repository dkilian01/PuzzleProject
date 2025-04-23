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
    QApplication a(argc, argv);// Inicjalizacja aplikacji Qt (wymagane dla GUI)
    // G³ówna pêtla gry – pozwala wracaæ do menu po zakoñczeniu rozgrywki
    while (true) {
        StartDialog dialog;
        if (dialog.exec() != QDialog::Accepted) break;

        int size = dialog.getBoardSize();
        QString playerName = dialog.getSelectedPlayer();
        Player player(playerName.toStdString());
        QString type = dialog.getBoardType();

        // WskaŸnik na abstrakcyjn¹ bazow¹ klasê planszy
        unique_ptr<PuzzleBase> board;
        if (type == "Klasyczna") {
            board = make_unique<PuzzleBoard>(size);
            board->changeBoard();
        }
        else if (type == "Heksagonalna") {
            board = make_unique<HexPuzzle>(size);
            board->changeBoard();
        }
        // Tworzenie logiki gry (³¹czy planszê i gracza)
        GameLogic* logic = new GameLogic(move(board), player);
        logic->start();

        // Tworzenie okna gry z logik¹
        PuzzleProject* window = new PuzzleProject(logic);
        bool powrotDoMenu = false; // Flaga okreœlaj¹ca, czy wróciæ do menu po zakoñczeniu gry

        // Obs³uga sygna³u powrotu do menu – zapisuje gracza i zamyka okno
        QObject::connect(window, &PuzzleProject::returnToMenu, [&]() {
            logic->getPlayer().saveToFile();
            powrotDoMenu = true;
            window->close();
            });

        window->show(); // Wyœwietlenie okna gry
        a.exec();// Uruchomienie g³ównej pêtli zdarzeñ Qt

        delete window;
        delete logic;
        // Jeœli gracz nie chce wróciæ do menu – koñczymy program
        if (!powrotDoMenu) break;
    }
    return 0;
}

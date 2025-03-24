#include "RankDialog.h"

RankDialog::RankDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Ranking graczy");
    QVBoxLayout* layout = new QVBoxLayout(this);
    QTableWidget* table = new QTableWidget(this);
    layout->addWidget(table);

    vector<Player> players = Player::loadAllPlayers();
    table->setRowCount(players.size());
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({ "Gracz", "Gry", "Najlepszy czas", "Œredni czas" });

    for (int i = 0; i < players.size(); ++i) {
        const Player& p = players[i];
        table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(p.getPlayerName())));
        table->setItem(i, 1, new QTableWidgetItem(QString::number(p.getGamesPlayed())));
        table->setItem(i, 2, new QTableWidgetItem(QString::number(p.getBestTime())));
        table->setItem(i, 3, new QTableWidgetItem(QString::number(p.getAverageTime())));
    }

    table->resizeColumnsToContents();
}
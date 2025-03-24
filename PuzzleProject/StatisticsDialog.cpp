#include "StatisticsDialog.h"

StatisticsDialog::StatisticsDialog(const Player& player, QWidget* parent)
    : QDialog(parent) {

    setWindowTitle("Statystyki gracza");
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* nameLabel = new QLabel("Gracz: " + QString::fromStdString(player.getPlayerName()), this);
    QLabel* gamesLabel = new QLabel("Rozegrane gry: " + QString::number(player.getGamesPlayed()), this);
    QLabel* bestLabel = new QLabel("Najlepszy czas: " + QString::number(player.getBestTime()) + " s", this);
    QLabel* avgLabel = new QLabel("Œredni czas: " + QString::number(player.getAverageTime()) + " s", this);

    layout->addWidget(nameLabel);
    layout->addWidget(gamesLabel);
    layout->addWidget(bestLabel);
    layout->addWidget(avgLabel);
}
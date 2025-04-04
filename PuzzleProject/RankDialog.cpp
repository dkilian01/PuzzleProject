#include "RankDialog.h"

RankDialog::RankDialog(QWidget* parent) : QDialog(parent) {

    setWindowTitle("Ranking graczy");
    QVBoxLayout* layout = new QVBoxLayout(this);
    QTableWidget* table = new QTableWidget(this);
    layout->addWidget(table);

    vector<Player> players = Player::loadAllPlayers();

    struct RankRow {
        string name;
        string type;
        int size;
        int count;
        double avg;
        double best;
    };
    vector<RankRow> rows;

    for (const auto& p : players) {
        map<pair<string, int>, tuple<int, double, double>> stats;

        for (const auto& s : p.getScores()) {
            double time = get<0>(s);
            int size = get<1>(s);
            string type = get<2>(s);
            auto key = make_pair(type, size);

            if (stats.count(key) == 0)
                stats[key] = { 1, time, time };
            else {
                auto& [count, sum, best] = stats[key];
                count++;
                sum += time;
                if (time < best) best = time;
            }
        }

        for (const auto& [key, val] : stats) {
            rows.push_back({ p.getPlayerName(), key.first, key.second,
                             get<0>(val), get<1>(val) / get<0>(val), get<2>(val) });
        }
    }
    table->setRowCount(rows.size());
    table->setColumnCount(6);
    table->setHorizontalHeaderLabels({ "Gracz", "Typ","Rozmiar","Gry", "Najlepszy czas", "Œredni czas" });

    for (int i = 0; i < rows.size(); ++i) {
        table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(rows[i].name)));
        table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(rows[i].type)));
        table->setItem(i, 2, new QTableWidgetItem(QString::number(rows[i].size)));
        table->setItem(i, 3, new QTableWidgetItem(QString::number(rows[i].count)));
        table->setItem(i, 4, new QTableWidgetItem(QString::number(rows[i].best)));
        table->setItem(i, 5, new QTableWidgetItem(QString::number(rows[i].avg)));
    }

    table->resizeColumnsToContents();
}
#include "StatisticsDialog.h"

StatisticsDialog::StatisticsDialog(const Player& player, QWidget* parent)
    : QDialog(parent) {

    setWindowTitle("Statystyki gracza");
    QVBoxLayout* layout = new QVBoxLayout(this);
    QTableWidget* table = new QTableWidget(this);
    layout->addWidget(table);

    QLabel* nameLabel = new QLabel("Gracz: " + QString::fromStdString(player.getPlayerName()), this);

    // Pobranie wszystkich wyników gracza: (czas, rozmiar planszy, typ planszy)
    auto scores = player.getScores();

    // Mapa statystyk: klucz (typ, rozmiar planszy), wartoœæ (liczba gier, suma czasów, najlepszy czas)
    map<pair<string, int>, tuple<int, double, double>> stats;

    // Przetwarzanie wyników gracza
    for (const auto& s : scores) {
        double time = get<0>(s);
        int size = get<1>(s);
        string type = get<2>(s);
        auto key = make_pair(type, size);
        // Inicjalizacja danych statystycznych dla danej konfiguracji
        if (stats.count(key) == 0)
            stats[key] = { 1, time, time };
        else {
            // Uaktualnianie danych: zwiêksz licznik, dodaj czas, aktualizuj najlepszy czas
            auto& [count, sum, best] = stats[key];
            count++;
            sum += time;
            if (time < best) best = time;
        }
    }
    table->setRowCount(stats.size());
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels({ "Typ planszy", "Rozmiar", "Rozegrane gry", "Najlepszy czas", "Œredni czas" });

    int row = 0;
    for (const auto& [key, val] : stats) {
        const auto& [type, size] = key;
        const auto& [count, sum, best] = val;

        table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(type)));
        table->setItem(row, 1, new QTableWidgetItem(QString::number(size)));
        table->setItem(row, 2, new QTableWidgetItem(QString::number(count)));
        table->setItem(row, 3, new QTableWidgetItem(QString::number(best)));
        table->setItem(row, 4, new QTableWidgetItem(QString::number(sum / count)));
        row++;
    }

    table->resizeColumnsToContents();
}
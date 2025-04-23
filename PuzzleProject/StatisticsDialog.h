/**
 * @file StatisticsDialog.h
 * @brief Okno dialogowe wyœwietlaj¹ce statystyki konkretnego gracza.
 *
 * Prezentuje dane takie jak liczba rozegranych gier, œredni i najlepszy czas
 * dla ka¿dego typu i rozmiaru planszy danego gracza.
 */
#pragma once
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QTableWidget>
#include "Player.h"
 /**
  * @class StatisticsDialog
  * @brief Klasa GUI do prezentacji statystyk gracza w tabeli.
  */
class StatisticsDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Konstruktor dialogu statystyk.
     * @param player Obiekt gracza, którego statystyki maj¹ byæ wyœwietlone.
     * @param parent WskaŸnik na rodzica (domyœlnie nullptr).
     */
    StatisticsDialog(const Player& player, QWidget* parent = nullptr);
};

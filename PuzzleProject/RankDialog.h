/**
 * @file RankDialog.h
 * @brief Okno dialogowe wyœwietlaj¹ce ranking graczy.
 *
 * Prezentuje zbiorcze statystyki wszystkich graczy zapisanych w plikach wyników,
 * posortowane wed³ug typu planszy, rozmiaru i osi¹gniêæ.
 */
#pragma once
#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include "Player.h"
 /**
  * @class RankDialog
  * @brief Klasa GUI do prezentacji globalnego rankingu graczy.
  */
class RankDialog : public QDialog {
    Q_OBJECT

public:
    /**
     * @brief Konstruktor dialogu rankingu.
     * @param parent WskaŸnik na rodzica (domyœlnie nullptr).
     */
    RankDialog(QWidget* parent = nullptr);
};
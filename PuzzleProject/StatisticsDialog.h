
#pragma once
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QTableWidget>
#include "Player.h"

class StatisticsDialog : public QDialog {
    Q_OBJECT

public:
    StatisticsDialog(const Player& player, QWidget* parent = nullptr);
};

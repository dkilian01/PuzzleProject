#pragma once
#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include "Player.h"

class RankDialog : public QDialog {
    Q_OBJECT

public:
    RankDialog(QWidget* parent = nullptr);
};
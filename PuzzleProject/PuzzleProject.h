#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PuzzleProject.h"

class PuzzleProject : public QMainWindow
{
    Q_OBJECT

public:
    PuzzleProject(QWidget *parent = nullptr);
    ~PuzzleProject();

private:
    Ui::PuzzleProjectClass ui;
};

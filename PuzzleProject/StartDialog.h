#pragma once
#include <QDialog>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
class StartDialog : public QDialog {
    Q_OBJECT
public:
    explicit StartDialog(QWidget* parent = nullptr);
    int getBoardSize();
private:
    QSpinBox* sizeSelector;
};


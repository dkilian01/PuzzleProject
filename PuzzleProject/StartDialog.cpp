#include "StartDialog.h"
StartDialog::StartDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Wybierz rozmiar planszy");

    QVBoxLayout* layout = new QVBoxLayout(this);

    sizeSelector = new QSpinBox(this);
    sizeSelector->setRange(3, 10); // Zakres dozwolonych rozmiarów planszy
    sizeSelector->setValue(4);     // Domyœlna wartoœæ

    QPushButton* startButton = new QPushButton("Start gry", this);
    connect(startButton, &QPushButton::clicked, this, &StartDialog::accept);

    layout->addWidget(sizeSelector);
    layout->addWidget(startButton);
}

int StartDialog::getBoardSize() {
    return sizeSelector->value(); // Zwraca wybran¹ wartoœæ
}
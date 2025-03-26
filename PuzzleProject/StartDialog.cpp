#include "StartDialog.h"
#include <QLabel>
#include <QHBoxLayout>

StartDialog::StartDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Start");

    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* playerLabel = new QLabel("Wybierz istniej¹cego gracza lub wpisz nowego", this);
    layout->addWidget(playerLabel);

    playerList = new QListWidget(this);
    QDir dir(".");
    QStringList files = dir.entryList(QStringList() << "*_scores.txt", QDir::Files);
    for (const QString& file : files) {
        playerList->addItem(file.left(file.indexOf("_scores.txt"))); // Usuwamy rozszerzenie
    }
    layout->addWidget(playerList);

    newPlayer = new QLineEdit(this);
    newPlayer->setPlaceholderText("Wpisz nowego gracza...");
    layout->addWidget(newPlayer);

    connect(playerList, &QListWidget::itemClicked, this, &StartDialog::addNewPlayer);


    QLabel* sizeLabel = new QLabel("Rozmiar planszy:", this);
    layout->addWidget(sizeLabel);

    sizeSelector = new QSpinBox(this);
    sizeSelector->setRange(2, 10); // Zakres dozwolonych rozmiarów planszy
    sizeSelector->setValue(4);     // Domyœlna wartoœæ

    QLabel* typeLabel = new QLabel("Typ planszy:", this);
    layout->addWidget(typeLabel);

    boardTypeBox = new QComboBox(this);
    boardTypeBox->addItem("Klasyczna");
    boardTypeBox->addItem("Heksagonalna");
    layout->addWidget(boardTypeBox);

    QPushButton* startButton = new QPushButton("Start gry", this);
    connect(startButton, &QPushButton::clicked, this, &StartDialog::accept);

    layout->addWidget(sizeSelector);
    layout->addWidget(startButton);
}

int StartDialog::getBoardSize() {
    return sizeSelector->value(); // Zwraca wybran¹ wartoœæ
}

void StartDialog::addNewPlayer() {
    newPlayer->clear(); // Czyœci pole, jeœli u¿ytkownik wybierze istniej¹cego gracza
}

QString StartDialog::getSelectedPlayer() const {
    if (!newPlayer->text().isEmpty()) {
        return newPlayer->text(); // Nowa nazwa gracza
    }
    if (playerList->currentItem()) {
        return playerList->currentItem()->text(); // Wybrany istniej¹cy gracz
    }
    return "Anonim"; // Domyœlna nazwa, jeœli nic nie wybrano
}
QString StartDialog::getBoardType() const {
    return boardTypeBox->currentText();
}
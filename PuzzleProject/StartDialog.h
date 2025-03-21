#pragma once
#include <QDialog>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QDir>
class StartDialog : public QDialog {
    Q_OBJECT
public:
    explicit StartDialog(QWidget* parent = nullptr);
    int getBoardSize();

    QString getSelectedPlayer() const;

private slots:
    void addNewPlayer();

private:
    QSpinBox* sizeSelector;

    QListWidget* playerList; 
    QLineEdit* newPlayer;
    QPushButton* startButton;


};


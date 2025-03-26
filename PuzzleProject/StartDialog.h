#pragma once
#include <QDialog>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QDir>
#include <QComboBox>
class StartDialog : public QDialog {
    Q_OBJECT
public:
    explicit StartDialog(QWidget* parent = nullptr);
    int getBoardSize();

    QString getSelectedPlayer() const;
    QString getBoardType() const;

private slots:
    void addNewPlayer();

private:
    QSpinBox* sizeSelector;

    QListWidget* playerList; 
    QLineEdit* newPlayer;
    QPushButton* startButton;

    QComboBox* boardTypeBox;
};


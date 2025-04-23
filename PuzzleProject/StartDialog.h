/**
 * @file StartDialog.h
 * @brief Okno dialogowe s³u¿¹ce do wyboru gracza, rozmiaru i typu planszy.
 *
 * Umo¿liwia u¿ytkownikowi wybranie istniej¹cego gracza, utworzenie nowego,
 * a tak¿e skonfigurowanie parametrów gry.
 */
#pragma once
#include <QDialog>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QListWidget>
#include <QDir>
#include <QComboBox>
 /**
  * @class StartDialog
  * @brief Okno pocz¹tkowe do konfiguracji nowej gry puzzle.
  */
class StartDialog : public QDialog {
    Q_OBJECT
public:
    /**
     * @brief Konstruktor domyœlny.
     * @param parent WskaŸnik na rodzica (domyœlnie nullptr).
     */
    explicit StartDialog(QWidget* parent = nullptr);

    /**
     * @brief Pobiera wybrany rozmiar planszy.
     * @return Wartoœæ liczbowa z kontrolki QSpinBox.
     */
    int getBoardSize();

    /**
     * @brief Pobiera nazwê wybranego lub wpisanego gracza.
     * @return Nazwa gracza jako QString.
     */
    QString getSelectedPlayer() const;

    /**
     * @brief Pobiera typ wybranej planszy ("Klasyczna" lub "Heksagonalna").
     * @return Typ planszy jako QString.
     */
    QString getBoardType() const;

private slots:
    /**
     * @brief Czyœci pole nowego gracza po klikniêciu istniej¹cego.
     */
    void addNewPlayer();

    /**
     * @brief Aktualizuje mo¿liwy zakres rozmiaru w zale¿noœci od typu planszy.
     * @param type Tekst wybranego typu ("Klasyczna", "Heksagonalna").
     */
    void updateSizeRange(const QString& type);

    /**
     * @brief Waliduje dane i akceptuje dialog, jeœli s¹ poprawne.
     */
    void validateAndAccept();

private:
    QSpinBox* sizeSelector;

    QListWidget* playerList; 
    QLineEdit* newPlayer;
    QPushButton* startButton;

    QComboBox* boardTypeBox;
};


#include "PuzzleProject.h"
#include "StartDialog.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    StartDialog dialog;
    if (dialog.exec() == QDialog::Accepted) {
        int size = dialog.getBoardSize();
        PuzzleProject* window = new PuzzleProject(size);
        window->show();
        return a.exec(); // Uruchamia GUI
    }

}

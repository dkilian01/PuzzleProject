#include "PuzzleProject.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PuzzleProject w;
    w.show();
    return a.exec();
}

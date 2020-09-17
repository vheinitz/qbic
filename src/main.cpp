
#include <QApplication>

#include "qbicmain.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    PuzzleMain window;

    window.show();

    return app.exec();
}

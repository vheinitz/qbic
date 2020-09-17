#ifndef PUZZLEMAIN_H
#define PUZZLEMAIN_H

#include <QMainWindow>

namespace Ui {
class PuzzleMain;
}

class PuzzleMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit PuzzleMain(QWidget *parent = 0);
    ~PuzzleMain();

private:
    Ui::PuzzleMain *ui;
};

#endif // PUZZLEMAIN_H

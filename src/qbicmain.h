#ifndef PUZZLEMAIN_H
#define PUZZLEMAIN_H


#include <QMainWindow>
#include <QList>

namespace Ui {
class PuzzleMain;
}

class PiecesList;

class PuzzleMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit PuzzleMain(QWidget *parent = 0);
    ~PuzzleMain();

private slots:
    void on_bAddProgLane_clicked();

private:
    Ui::PuzzleMain *ui;
    QList <PiecesList*> _progLanes;
};

#endif // PUZZLEMAIN_H

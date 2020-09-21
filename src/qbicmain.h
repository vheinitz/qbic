#ifndef PUZZLEMAIN_H
#define PUZZLEMAIN_H


#include <QMainWindow>
#include <QList>

class Prog;

namespace Ui {
class QBicMain;
}

class PiecesList;

class QBicMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit QBicMain(QWidget *parent = 0);
    ~QBicMain();

private slots:
    void on_bAddProgLane_clicked();
	void removeProgLane( QObject* );

private:
    Ui::QBicMain *ui;
    QList <Prog*> _progLanes;
};

#endif // PUZZLEMAIN_H

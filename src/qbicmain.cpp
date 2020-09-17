#include "qbicmain.h"
#include "ui_qbicmain.h"
#include "proglane.h"
#include "pieceslist.h"
#include "wastebox.h"
PuzzleMain::PuzzleMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PuzzleMain)
{
    ui->setupUi(this);
	ProgLane *progLane = new ProgLane();


    PiecesList *sensors = new PiecesList(progLane->itemSize(), false, this);
	PiecesList *actors  = new PiecesList(progLane->itemSize(), false, this);


	sensors->load("sensor");
	actors->load("actor");

	ui->ltSensors->addWidget(sensors);
	ui->ltActors->addWidget(actors);


    /*PiecesList  * pl1 = new PiecesList(progLane->itemSize(), true, this);
	PiecesList  * pl2 = new PiecesList(progLane->itemSize(), true, this);
	PiecesList  * pl3 = new PiecesList(progLane->itemSize(), true, this);

    pl1->load("sensor");

	ui->ltProgr->addWidget(pl1);
	ui->ltProgr->addWidget(pl2);
	ui->ltProgr->addWidget(pl3);
    */
	ui->ltProgr->addWidget(new ProgLane());
	ui->ltUtils->addWidget(new WasteBox());


}

PuzzleMain::~PuzzleMain()
{
    delete ui;
}

int plcnt=0;
void PuzzleMain::on_bAddProgLane_clicked()
{
    PiecesList  * pl = new PiecesList(plcnt++, true, this);
    ui->ltProgr->addWidget( pl );
}

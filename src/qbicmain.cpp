#include "qbicmain.h"
#include "ui_qbicmain.h"
#include "prog.h"
#include "pieceslist.h"
#include "runtime_sim.h"
#include "wastebox.h"
QBicMain::QBicMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QBicMain)
{
    ui->setupUi(this);
	RuntimeSim *runtimeSim = new RuntimeSim();
	runtimeSim->show();


	PiecesList *sensors = new PiecesList( QListView::TopToBottom, false, this);
	PiecesList *actors  = new PiecesList( QListView::TopToBottom, false, this);


	sensors->load("sensor");
	actors->load("actor");

	ui->ltSensors->addWidget(sensors);
	ui->ltActors->addWidget(actors);

	ui->ltUtils->addWidget(new WasteBox());
}

QBicMain::~QBicMain()
{
    delete ui;
}

//int plcnt=0;
void QBicMain::on_bAddProgLane_clicked()
{
	Prog  * prog = new Prog;
	connect( prog, SIGNAL(  remove( QObject* )  ), this, SLOT(  removeProgLane( QObject* )  ) );
	_progLanes.append(prog);
    ui->ltProgr->addWidget( prog );
}

void QBicMain::removeProgLane( QObject*p )
{
	Prog *prog = qobject_cast<Prog*>(p);
	_progLanes.removeAll( prog );
    delete prog;
}
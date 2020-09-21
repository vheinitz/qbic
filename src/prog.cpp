#include "src/prog.h"
#include "ui_prog.h"
#include "pieceslist.h"
#include <QIcon>
#include <QPixmap>
#include <QListView>
#include <QStandardItemModel>


Prog::Prog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Prog)
{
    ui->setupUi(this);
	this->setMaximumHeight(100);
	PiecesList  * pl = new PiecesList( QListView::LeftToRight, true, this);
	ui->ltItemPieces->addWidget(pl);
	
	QStandardItemModel * events = new QStandardItemModel(this);

	events->appendRow( new QStandardItem( QIcon(QPixmap("res/switch_on.png").scaled(100,100)),"") );
	events->appendRow( new QStandardItem( QIcon(QPixmap("res/switch_off.png").scaled(100,100)),"") );
	events->appendRow( new QStandardItem( QIcon(QPixmap("res/switch_on_off.png").scaled(100,100)),"") );
	events->appendRow( new QStandardItem( QIcon(QPixmap("res/switch_off_on.png").scaled(100,100)),"") );
	QListView *view = new QListView(this);
	//view->setModel( events );
    view->setStyleSheet("QListView::item{height: 100px}");
    
	ui->cbEvent->setModel( events );
	ui->cbEvent->setView(view);
	ui->cbEvent->setIconSize(QSize(100,100));


	/*addPiece("res/switch_off.png;sensor" );
	addPiece("res/switch_off_on.png;sensor" );
	addPiece("res/switch_on.png;sensor" );
	addPiece("res/switch_on_off.png;sensor" );*/
}

Prog::~Prog()
{
    delete ui;
}

void Prog::on_bRemove_clicked()
{
	emit remove( this );
}

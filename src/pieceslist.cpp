

#include <QtGui>

#include "pieceslist.h"

PiecesList::PiecesList( QListView::Flow flow, bool dropable, QWidget *parent)
    : QListWidget(parent), m_itemSize(100,100),_dropable(dropable)
{
    setDragEnabled(true);
    setViewMode(QListView::IconMode);
    setIconSize(m_itemSize);
    setSpacing(10);
    setAcceptDrops(dropable);
    setDropIndicatorShown(true);
	setMinimumSize(m_itemSize);
	setWrapping(false);
	setFlow( flow );
    //setMaximumSize(100, 500);
}

void PiecesList::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("data/progitem"))
       event->accept();
    else
        event->ignore();
}

void PiecesList::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasFormat("data/progitem")) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else
        event->ignore();
}


void PiecesList::dropEvent(QDropEvent *ev)
{
	QPoint droppos = ev->pos();
    if (ev->mimeData()->hasFormat("data/progitem")) {
        QByteArray pieceData = ev->mimeData()->data("data/progitem");
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);

		QPixmap pixmap;
        QString type;
        dataStream >> pixmap >> type;
		//addPiece(pixmap, type);
		insertPiece(droppos,pixmap, type);

        ev->setDropAction(Qt::CopyAction);
        ev->accept();
    } else
        ev->ignore();
}

void PiecesList::load(QString galleryName)
{
	if ( galleryName == "actor" )
	{
		addPiece("res/lamp_off.png;actor" );
		addPiece("res/lamp_on.png;actor" );
		addPiece("res/mot_ccw.png;actor" );
		addPiece("res/mot_cw.png;actor" );
		addPiece("res/mot_off.png;actor" );
	}
	else if ( galleryName == "sensor" )
	{
		addPiece("res/switch_off.png;sensor" );
		addPiece("res/switch_off_on.png;sensor" );
		addPiece("res/switch_on.png;sensor" );
		addPiece("res/switch_on_off.png;sensor" );
	}
}

void PiecesList::addPiece(QString cfg)
{
	QPixmap pixmap = QPixmap(cfg.section(";",0,0));
	QString type = cfg.section(";",1,1);
    QListWidgetItem *pieceItem = new QListWidgetItem(this);
    pieceItem->setIcon(QIcon(pixmap));
    pieceItem->setData(Qt::UserRole, QVariant(pixmap));
    pieceItem->setData(Qt::UserRole+1, type);
    pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable
                        | Qt::ItemIsDragEnabled);
}

void PiecesList::addPiece(QPixmap pixmap, QString type)
{
    QListWidgetItem *pieceItem = new QListWidgetItem(this);
    pieceItem->setIcon(QIcon(pixmap));
    pieceItem->setData(Qt::UserRole, QVariant(pixmap));
    pieceItem->setData(Qt::UserRole+1, type);
    pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable
                        | Qt::ItemIsDragEnabled);
}

void PiecesList::insertPiece(QPoint pos, QPixmap pixmap, QString type)
{
    QListWidgetItem *pieceItem = new QListWidgetItem();
    pieceItem->setIcon(QIcon(pixmap));
    pieceItem->setData(Qt::UserRole, QVariant(pixmap));
    pieceItem->setData(Qt::UserRole+1, type);
    pieceItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable
                        | Qt::ItemIsDragEnabled);
	insertItem(  pos.x() / this->m_itemSize.width() , pieceItem);
}

void PiecesList::startDrag(Qt::DropActions /*supportedActions*/)
{
    QListWidgetItem *item = currentItem();

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    QPixmap pixmap = qvariant_cast<QPixmap>(item->data(Qt::UserRole));
    QPoint location = item->data(Qt::UserRole+1).toPoint();

    dataStream << pixmap << location;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("data/progitem", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(QPoint(pixmap.width()/2, pixmap.height()/2));
    drag->setPixmap(pixmap);

	

    if (_dropable && drag->exec(Qt::MoveAction) == Qt::MoveAction)
        delete takeItem(row(item));
	else 
		drag->exec(Qt::CopyAction);
}

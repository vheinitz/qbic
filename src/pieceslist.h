

#ifndef PIECESLIST_H
#define PIECESLIST_H

#include <QListWidget>

class PiecesList : public QListWidget
{
    Q_OBJECT

public:
    PiecesList(int itemSize, bool dropable=false, QWidget *parent = 0);

    void addPiece(QString cfg);
	void addPiece(QPixmap pixmap, QString type);

	void load(QString galleryName);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void startDrag(Qt::DropActions supportedActions);

    int m_itemSize;
	bool _dropable;
};

#endif

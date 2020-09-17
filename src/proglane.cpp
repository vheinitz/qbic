

#include <QtGui>

#include "ProgLane.h"

ProgLane::ProgLane( QWidget *parent)
    : QWidget(parent)
{
    setAcceptDrops(true);
    setMinimumSize(400, itemSize());
    setMaximumSize(400, itemSize());
}

void ProgLane::clear()
{
    piecePixmaps.clear();
    pieceRects.clear();
    highlightedRect = QRect();
    inPlace = 0;
    update();
}

void ProgLane::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("data/progitem"))
        event->accept();
    else
        event->ignore();
}

void ProgLane::dragLeaveEvent(QDragLeaveEvent *event)
{
    QRect updateRect = highlightedRect;
    highlightedRect = QRect();
    update(updateRect);
    event->accept();
}

void ProgLane::dragMoveEvent(QDragMoveEvent *event)
{
    QRect updateRect = highlightedRect.unite(targetSquare(event->pos()));

    if (event->mimeData()->hasFormat("data/progitem")
        && findPiece(targetSquare(event->pos())) == -1) {

        highlightedRect = targetSquare(event->pos());
        event->setDropAction(Qt::MoveAction);
        event->accept();
    } else {
        highlightedRect = QRect();
        event->ignore();
    }

    update(updateRect);
}

void ProgLane::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("data/progitem")
        && findPiece(targetSquare(event->pos())) == -1) {

        QByteArray pieceData = event->mimeData()->data("data/progitem");
        QDataStream dataStream(&pieceData, QIODevice::ReadOnly);
        QRect square = targetSquare(event->pos());
        QPixmap pixmap;
        QPoint location;
        dataStream >> pixmap >> location;

        piecePixmaps.append(pixmap);
        pieceRects.append(square);

        highlightedRect = QRect();
        update(square);

        event->setDropAction(Qt::MoveAction);
        event->accept();

    } else {
        highlightedRect = QRect();
        event->ignore();
    }
}

int ProgLane::findPiece(const QRect &pieceRect) const
{
    for (int i = 0; i < pieceRects.size(); ++i) {
        if (pieceRect == pieceRects[i]) {
            return i;
        }
    }
    return -1;
}

void ProgLane::mousePressEvent(QMouseEvent *event)
{
    QRect square = targetSquare(event->pos());
    int found = findPiece(square);

    if (found == -1)
        return;

    QPixmap pixmap = piecePixmaps[found];
    piecePixmaps.removeAt(found);
    pieceRects.removeAt(found);

    update(square);

    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);

    dataStream << pixmap;

    QMimeData *mimeData = new QMimeData;
    mimeData->setData("data/progitem", itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setHotSpot(event->pos() - square.topLeft());
    drag->setPixmap(pixmap);

    if (!(drag->exec(Qt::MoveAction) == Qt::MoveAction)) {
        piecePixmaps.insert(found, pixmap);
        pieceRects.insert(found, square);
        update(targetSquare(event->pos()));
    }
}

void ProgLane::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.fillRect(event->rect(), Qt::white);

    if (highlightedRect.isValid()) {
        painter.setBrush(QColor("#ffcccc"));
        painter.setPen(Qt::NoPen);
        painter.drawRect(highlightedRect.adjusted(0, 0, -1, -1));
    }

    for (int i = 0; i < pieceRects.size(); ++i) {
        painter.drawPixmap(pieceRects[i], piecePixmaps[i]);
    }
    painter.end();
}

const QRect ProgLane::targetSquare(const QPoint &position) const
{
    return QRect(position.x()/itemSize() * itemSize(), position.y()/itemSize() * itemSize(), itemSize(), itemSize());
}

int ProgLane::itemSize() const
{
    return 128;
}


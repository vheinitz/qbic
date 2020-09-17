
#ifndef PROGLANE_H
#define PROGLANE_H

#include <QList>
#include <QPoint>
#include <QPixmap>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
class QMouseEvent;
QT_END_NAMESPACE


#include <QListWidget>



class ProgLane : public QWidget
{
    Q_OBJECT

public:
    ProgLane( QWidget *parent = 0);
    void clear();

    int itemSize() const;



protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    int findPiece(const QRect &pieceRect) const;
    const QRect targetSquare(const QPoint &position) const;

    QList<QPixmap> piecePixmaps;
    QList<QRect> pieceRects;
    QRect highlightedRect;
    int inPlace;
};

#endif



#include <QtGui>

#include "wastebox.h"

WasteBox::WasteBox( QWidget *parent)
    : QWidget(parent)
{
    setAcceptDrops(true);
    setMinimumSize(100, 100);
    setMaximumSize(100, 100);
}


void WasteBox::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("data/progitem")) {
		event->setDropAction(Qt::MoveAction);
        event->accept();

    } else {
        event->ignore();
    }
}

void WasteBox::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("data/progitem"))
        event->accept();
    else
        event->ignore();
}

void WasteBox::dragLeaveEvent(QDragLeaveEvent *event)
{
	update(this->rect());
    event->accept();
}

void WasteBox::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.fillRect(event->rect(), Qt::white);

	QRect highlightedRect= this->rect();

    if (highlightedRect.isValid()) {
        painter.setBrush(QColor("#ffcccc"));
        painter.setPen(Qt::NoPen);
        painter.drawRect(highlightedRect.adjusted(0, 0, -1, -1));
    }

    
    painter.end();
}


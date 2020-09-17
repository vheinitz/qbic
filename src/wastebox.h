
#ifndef WASTEBOX_H
#define WASTEBOX_H

#include <QList>
#include <QPoint>
#include <QPixmap>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
class QMouseEvent;
QT_END_NAMESPACE

class WasteBox : public QWidget
{
    Q_OBJECT

public:
    WasteBox( QWidget *parent = 0);

protected:
    void dropEvent(QDropEvent *event);
	void paintEvent(QPaintEvent *event);
	void dragEnterEvent(QDragEnterEvent *event);
	void dragLeaveEvent(QDragLeaveEvent *event);

};

#endif

#ifndef PROG_H
#define PROG_H

#include <QWidget>

namespace Ui {
class Prog;
}

class Prog : public QWidget
{
    Q_OBJECT

public:
    explicit Prog(QWidget *parent = 0);
    ~Prog();
	void load(QString galleryName);

private slots:
    void on_bRemove_clicked();

private:
    Ui::Prog *ui;
};

#endif // PROG_H

#ifndef RUNTIME_SIM_H
#define RUNTIME_SIM_H


#include <QWidget>
#include <QList>

namespace Ui {
class RuntimeSim;
}

class RuntimeSim: public QWidget
{
    Q_OBJECT

public:
    explicit RuntimeSim(QWidget *parent = 0);
    ~RuntimeSim();

private slots:


private:
    Ui::RuntimeSim *ui;

};

#endif // RUNTIME_SIM_H

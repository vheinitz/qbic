#ifndef RUNTIME_SIM_H
#define RUNTIME_SIM_H


#include <QWidget>
#include <QList>

namespace Ui {
class RuntimeSim;
}

class QCheckBox;
class QLineEdit;

class RuntimeSim: public QWidget
{
    Q_OBJECT

public:
    explicit RuntimeSim(QWidget *parent = 0);
    ~RuntimeSim();

private slots:
	void updatePins();
	void processDigitalInput( bool );
	void processAnalogInput( QString );


private:
    Ui::RuntimeSim *ui;
	QList <QCheckBox*> _digitalPins;
	QList <QLineEdit*> _analogPins;

};

#endif // RUNTIME_SIM_H

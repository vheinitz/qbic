#include "runtime_sim.h"
#include "ui_runtime_sim.h"
#include <QCheckBox>
#include <QLineEdit>

RuntimeSim::RuntimeSim(QWidget *parent) :
    QWidget(parent),
		ui(new Ui::RuntimeSim)
{
    ui->setupUi(this);

	for(int i=2; i<=12; i++)
	{
		QCheckBox *cb = new QCheckBox( QString("D%1").arg(i) );
		ui->ltDigital->addWidget(cb);
	}

	for(int i=0; i<=5; i++)
	{
		QLineEdit *le = new QLineEdit( );
		ui->ltAnalog->addWidget(le);
	}

}

RuntimeSim::~RuntimeSim()
{
    delete ui;
}

#include "runtime_sim.h"
#include "ui_runtime_sim.h"
#include <QCheckBox>
#include <QLineEdit>
#include <QTimer>
#include <ctime>
#include <QDateTime>

extern "C"
{
#define D_IS_SET		1
#define D_IS_RESET		2
#define A_EQUAL			3
#define A_LESS_EQUAL	4
#define A_LESS			5
#define A_GREATER_EQUAL 6
#define A_GREATER		7

#define D_SET		1
#define D_RESET		2
#define D_WRITE		3
#define CMD_PAUSE	4

	void RunMachine();
};

#define SIMMODE 1

int runtime_start();

int digitalPins[12]={0};
int analogPins[5]={0};

qint64 StartTimeStamp = QDateTime::currentMSecsSinceEpoch();


RuntimeSim::RuntimeSim(QWidget *parent) :
    QWidget(parent),
		ui(new Ui::RuntimeSim)
{
    ui->setupUi(this);

	_digitalPins.append(0);
	_digitalPins.append(0);
	for(int i=2; i<=12; i++)
	{
		QCheckBox *cb = new QCheckBox( QString("D%1").arg(i) );
		cb->setProperty("DigitalPin", i);
		ui->ltDigital->addWidget(cb);
		_digitalPins.append(cb);
		connect( cb, SIGNAL(clicked(bool)), this , SLOT(processDigitalInput( bool )) );
	}

	for(int i=0; i<=5; i++)
	{
		QLineEdit *le = new QLineEdit( );
		le->setProperty("AnalogPin", i);
		ui->ltAnalog->addWidget(le);
		_analogPins.append(le);
		connect( le, SIGNAL(textEdited(QString)), this , SLOT(processAnalogInput( QString )) );
	}

	runtime_start();
	QTimer::singleShot( 10, this, SLOT(updatePins()) );
}

RuntimeSim::~RuntimeSim()
{
    delete ui;
}

void RuntimeSim::updatePins()
{
	RunMachine();

	for (int i=0; i< sizeof(digitalPins)/sizeof(digitalPins)[0]; i++)
	{
		if ( _digitalPins.at(i) )
		{
			_digitalPins.at(i)->setChecked( digitalPins[i] );
		}
	}
	QTimer::singleShot( 10, this, SLOT(updatePins()) );
}

void RuntimeSim::processDigitalInput( bool val )
{
	int id = sender()->property( "DigitalPin" ).toInt();

	digitalPins[id] = val;

}

void RuntimeSim::processAnalogInput( QString val )
{
	int id = sender()->property( "AnalogPin" ).toInt();

	analogPins[id] = val.toInt();
}

/////////////////// C /////////////////////////////

int digitalRead(int id)
{
	return digitalPins[id];
}

void digitalWrite(int id, int val)
{
	digitalPins[id] = val;
}

void analogWrite(int id, int val)
{
	analogPins[id] = val;
}

int analogRead(int id)
{
	return analogPins[id];
}

int millis()
{
	return QDateTime::currentMSecsSinceEpoch() - StartTimeStamp;
	
}


//RUNTIME
extern "C"
{
  static const int lanesCnt=10;
  static const int stepsCnt=20;

  static const int inputVarCnt=10;

  typedef struct{
    int command;
    int param1;
    int param2;
  } TProgStep;

  typedef struct{
    int command;
    int param1;
    int param2;
  } TSensorCommand;

  typedef struct{
    int curStep;
    int pausedTill;
    TSensorCommand sensorCommand;
    TProgStep progSteps[stepsCnt];
  
  } TProgLanes;

  int InputVars[inputVarCnt];

  TProgLanes progLanes[lanesCnt];
  int curLane=0;
  
  void executeCommand( TProgLanes * progLane, TProgStep *progStep)
  {
    switch (progStep->command)
    {
    case D_SET:
      digitalWrite(progStep->param1, 1);
      break;
    case D_RESET:
      digitalWrite(progStep->param1, 0);
      break;
    case D_WRITE:
      analogWrite(progStep->param1, progStep->param2);
      break;
    case CMD_PAUSE:
		progLane->pausedTill = millis() + progStep->param1 * 1000 + progStep->param2;
      break;
    default:
      break;
    }
  }



  int conditionHit( TSensorCommand * sensorCommand  )
  {
    switch (sensorCommand->command)
    {
    case D_IS_SET:
      return digitalRead(sensorCommand->param1);
    case D_IS_RESET:
      return digitalRead(sensorCommand->param1)==0;
    case A_EQUAL:
      return analogRead(sensorCommand->param1) == sensorCommand->param2;
    case A_LESS_EQUAL:
      return analogRead(sensorCommand->param1) <= sensorCommand->param2;
    case A_LESS:
      return analogRead(sensorCommand->param1) < sensorCommand->param2;
    case A_GREATER_EQUAL:
      return analogRead(sensorCommand->param1) >= sensorCommand->param2;
    case A_GREATER:
      return analogRead(sensorCommand->param1) > sensorCommand->param2;
    }
    return 1;
  }

  void load()
  {
    progLanes[0].sensorCommand.command=1;
	progLanes[0].sensorCommand.param1=2;
	progLanes[0].progSteps[0].command = D_RESET;
	progLanes[0].progSteps[0].param1 = 2;
	progLanes[0].progSteps[1].command = D_SET;
	progLanes[0].progSteps[1].param1 = 3;
	progLanes[0].progSteps[2].command = CMD_PAUSE;
	progLanes[0].progSteps[2].param1 = 3;
	progLanes[0].progSteps[2].param2 = 0;
	
	progLanes[0].progSteps[3].command = D_RESET;
	progLanes[0].progSteps[3].param1 = 3;


	progLanes[1].sensorCommand.command=2;
	progLanes[1].sensorCommand.param1=2;
	progLanes[1].progSteps[0].command = D_RESET;
	progLanes[1].progSteps[0].param1 = 3;

	progLanes[2].sensorCommand.command=A_GREATER;
	progLanes[2].sensorCommand.param1=0;
	progLanes[2].sensorCommand.param2=100;

	progLanes[2].progSteps[0].command = D_SET;
	progLanes[2].progSteps[0].param1 = 8;

	progLanes[2].progSteps[1].command = D_SET;
	progLanes[2].progSteps[1].param1 = 9;

	progLanes[2].progSteps[2].command = D_RESET;
	progLanes[2].progSteps[2].param1 = 10;

	///
	progLanes[3].sensorCommand.command=A_LESS;
	progLanes[3].sensorCommand.param1=0;
	progLanes[3].sensorCommand.param2=10;

	progLanes[3].progSteps[0].command = D_RESET;
	progLanes[3].progSteps[0].param1 = 8;

	progLanes[3].progSteps[1].command = D_RESET;
	progLanes[3].progSteps[1].param1 = 9;

	progLanes[3].progSteps[2].command = D_SET;
	progLanes[3].progSteps[2].param1 = 10;

	
  }

  void setup()
  {
    for(int i=0; i<lanesCnt; i++)
    {
      TProgLanes * progLane = &progLanes[i];
      progLane->pausedTill=-1;
      progLane->curStep=-1;                 // -1 means sequence is not running
      progLane->sensorCommand.command = -1; // means, the lane not used
      for(int s=0; s<stepsCnt; s++)
      {
        TProgStep * progStep = &progLane->progSteps[s];
        progStep->command=-1;
      }
    }
  }

  ///////////////////
  void RunMachine()
  {
	while(1)
    {
      TProgLanes * progLane = &progLanes[curLane];
      if ( progLane->sensorCommand.command >= 0  )
      {
	    int ts = millis();
		if ( progLane->pausedTill >=0 )
		{
			if ( progLane->pausedTill > ts )
			{
				curLane++;
				continue;
			}
			else
			{
				progLane->pausedTill = -1;
				progLane->curStep++;
				curLane++;
				continue;
			}
		}
        //Already running
        if ( progLane->curStep > -1 && progLane->curStep < stepsCnt )
        {
          executeCommand ( progLane, &progLane->progSteps[progLane->curStep] );
          progLane->curStep++;
          if ( progLane->progSteps[progLane->curStep].command == -1 )
          {
            progLane->curStep = -1;
          }
        }
        else
        {
          if ( conditionHit( &progLane->sensorCommand ) )
          {
            progLane->curStep=0; // Start on next iteration
          }
        }
      }
      curLane++;
      if (curLane>=lanesCnt) curLane=0;

	  if (SIMMODE) break;
    }
  }

  void loop()
  {
    int attempts=0;
    for (attempts=0; attempts<5;attempts++)
	{
		
	}

	RunMachine();
    
  }

};

int runtime_start()
{
	
	setup();
	load();
	loop();

	return 0;
}
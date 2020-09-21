
#include <QApplication>

#include "qbicmain.h"

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);
    QBicMain window;

    window.show();

    return app.exec();
}

int digitalRead(int)
{
	return 0;
}

void digitalWrite(int, int)
{
	
}

void analogWrite(int, int)
{
}

int analogRead(int)
{
	return 0;
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
  
  void executeCommand( TProgStep *progStep)
  {
    switch (progStep->command)
    {
    case 1:
      digitalWrite(progStep->param1, 1);
      break;
    case 2:
      digitalWrite(progStep->param1, 0);
      break;
    case 3:
      analogWrite(progStep->param1, progStep->param2);
      break;
    default:
      break;
    }
  }

  int conditionHit( TSensorCommand * sensorCommand  )
  {
    switch (sensorCommand->command)
    {
    case 1:
      return digitalRead(sensorCommand->param1);
    case 2:
      return digitalRead(sensorCommand->param1)==0;
    case 3:
      return analogRead(sensorCommand->param1) == InputVars[sensorCommand->param2];
    case 6:
      return analogRead(sensorCommand->param1) <= InputVars[sensorCommand->param2];
    case 7:
      return analogRead(sensorCommand->param1) < InputVars[sensorCommand->param2];
    case 8:
      return analogRead(sensorCommand->param1) >= InputVars[sensorCommand->param2];
    case 9:
      return analogRead(sensorCommand->param1) > InputVars[sensorCommand->param2];
    }
    return 1;
  }

  void load()
  {
    progLanes[0].sensorCommand.command=1;
    progLanes[0].sensorCommand.command=1;
    progLanes[0].progSteps[0].command = 1;
    progLanes[0].progSteps[1].command = 2;
    progLanes[0].progSteps[2].command = 3;
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

  void loop()
  {
    int attempts=0;
    for (attempts=0; attempts<5;attempts++)
	{
		
	}
    while(1)
    {
      TProgLanes * progLane = &progLanes[curLane];
      if ( progLane->sensorCommand.command >= 0  )
      {
        //Already running
        if ( progLane->curStep > -1 && progLane->curStep < stepsCnt )
        {
          executeCommand ( &progLane->progSteps[progLane->curStep] );
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
    }
  }

};

int _main()
{
	
	setup();
	load();
	loop();

	return 0;
}
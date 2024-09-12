#include "stdafx.h"
#include "GameTestClient_Other.h"


static unsigned g_maxAllowedChatLoopbackTime = 20.0; // если за столько секунд нам не пришло обратно наше же сообщение, ассертим
static unsigned g_maxAllowedChatConnectTime = 20.0; // если за столько секунд не залогинились, ассертим

namespace gtc
{

StepResult Client_Login::MainStep()
{
  StepResult result = TestClientBase::MainStep();
  if ( !result.Ok() || result.Handled() )
    return result;

  switch(stage_)
  {
    default:
      return StepResult( false, true );

    case Stage::LOGIN_FINISHED:
      if( transport_ ) 
      {
        userId_ = transport_->GetUserId(); // quick hack (пока никто не говорит нам id)

        LOG_D(0) << "success: login finished for user " << params.user << ", userId " << userId_;

        //// к сожалению, релогин пока реализовать не удается (транспорт дохнет на Read Error'ах)
        //transport_->Logout();
        timeLoginFinished_ = timer::Now();
        stage_ = Stage::LOGIN_WAIT_AFTER;
      }
      return StepResult( true, true );

    case Stage::LOGIN_WAIT_AFTER:
      //if( timer::Now() - timeLoginFinished_ > 1 )
      return StepResult( true, false ); // можно прибивать клиента

      //// к сожалению, релогин пока реализовать не удается (транспорт дохнет на Read Error'ах)
      //{// relogin after pause
      //  LOG_D(0) << "user " << params.user << " relogging";
      //  stage_ = Stage::NONE;
      //}
      //bres = true;
      break;
  }
}











StepResult Client_Replay::MainStep()
{
  StepResult result = Client_GS::MainStep();
  if ( !result.Ok() || result.Handled() )
    return result;

  switch(stage_)
  {
    default:
      return StepResult( false, true );

    case Stage::LOGIN_FINISHED:
      stage_ = Stage::GAME; 
      timePlaySessionStarted = timer::Now();
      return StepResultOk();

    case Stage::GAME:
      // command replay
      if ( replay.HasReplay() )
      {
        NCore::ReplaySegment::Commands::iterator cmd;
        if( replay.GetCurrentCommand( cmd ) )
        {// не пора ли проиграть?
          while( timer::Now() - timePlaySessionStarted > replay.GetCommandTimestamp( cmd ) )
          {// пора отослать команду
            // в этом режиме просто распечатываем команды (т.к. ни в какой мы не в сессии, только залогинились) 
            LOG_D(0) << "replay cmd time(ofs): " << (*cmd)->TimeSent() - replay.GetStartTime() << ", time(sent): " << (*cmd)->TimeSent();

            if( !replay.GetNextCommand( cmd ) ) // давайте следующую команду
              break;
          }
        }
      }
      return PollGame();
  }
}


bool Client_Replay::LoadReplay( const char * replayFileName, int replayClientId )
{ 
  return replay.LoadReplay( replayFileName, replayClientId );
}
} //namespace gtc

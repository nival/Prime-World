#include "stdafx.h"
#include "ForgeRollRequest.h"
#include "HttpGatewayLog.inl"
#include "Server/Roll/RRollBalancer.auto.h"
#include "Server/Roll/RRollInstance.auto.h"


namespace HttpGateway
{

static float s_rollRequestTimeout = 30.0f;
REGISTER_VAR( "http_gateway_roll_req_timeout", s_rollRequestTimeout, STORAGE_NONE );

static int s_rollMaxTries = 16;
REGISTER_VAR( "http_gateway_roll_max_tries", s_rollMaxTries, STORAGE_NONE );

static float s_rollRetryCooldown = 60.0f;
REGISTER_VAR( "http_gateway_roll_retry_cooldown", s_rollRetryCooldown, STORAGE_NONE );


ForgeRollRequest::ForgeRollRequest( const roll::SForgeRollData & _data, rpc::IfaceRequester<roll::RIBalancer> * _balancer ) :
data( _data ),
now( 0 ),
state( EForgeRollRequestState::New ),
balancer( _balancer ),
stateExpires( -1 ), cooldownEnds( 0 ),
retryIndex( 0 )
{
}



bool ForgeRollRequest::Poll( timer::Time _now )
{
  now = _now;

  CheckStateExpire();

  switch ( state )
  {
    case EForgeRollRequestState::New:
      Switch( EForgeRollRequestState::WaitingBalancer );
      return true;

    case EForgeRollRequestState::WaitingBalancer:
      if ( balancer->isopen() )
      {
        balancer->iface()->AllocateInstance( this, &ForgeRollRequest::OnRollInstance );
        Switch( EForgeRollRequestState::WaitingRollInstance );
      }
      return true;

    case EForgeRollRequestState::WaitingRollInstance:
      return true;

    case EForgeRollRequestState::WaitingRoll:
      return true;

    case EForgeRollRequestState::Cooldown:
      if ( now > cooldownEnds ) {
        SVC_LOG_MSG.Trace( "Retrying roll request. uid=%d, roll_id=%016x, try=%d", data.uid, data.rollId, retryIndex );
        SwitchWoExpire( EForgeRollRequestState::New );
        cooldownEnds = 0;
      }
      return true;

    default:
    case EForgeRollRequestState::Done:
    case EForgeRollRequestState::Failed:
      return false;
  }
}



void ForgeRollRequest::CheckStateExpire()
{
  if ( stateExpires < 0 )
    return;
  if ( now < stateExpires )
    return;

  SVC_LOG_ERR.Trace( "Roll operation timed out! uid=%d, roll_id=%016x, st=%d", data.uid, data.rollId, (int)state );

  switch ( state )
  {
    case EForgeRollRequestState::WaitingBalancer:
    case EForgeRollRequestState::WaitingRollInstance:
    case EForgeRollRequestState::WaitingRoll:
      TryRetry();
      break;

    default:
      SwitchWoExpire( EForgeRollRequestState::Failed );
  }
}



void ForgeRollRequest::Switch( EForgeRollRequestState::Enum st )
{
  state = st;
  stateExpires = now + s_rollRequestTimeout;
}



void ForgeRollRequest::SwitchWoExpire( EForgeRollRequestState::Enum st )
{
  state = st;
  stateExpires = -1;
}



void ForgeRollRequest::OnRollInstance( roll::RIInstance * _inst )
{
  if ( !_inst ) {
    SVC_LOG_ERR.Trace( "Could not allocate roll instance. uid=%d, roll_id=%016x", data.uid, data.rollId );
    TryRetry();
    return;
  }

  SVC_LOG_MSG.Trace( "Roll instance allocated. uid=%d, roll_id=%016x", data.uid, data.rollId );

  instance = _inst;
  instance->ForgeRoll( this, data );
  Switch( EForgeRollRequestState::WaitingRoll );
}



void ForgeRollRequest::RollResults( const vector<roll::SUserAward> & _award )
{
  NI_ALWAYS_ASSERT( "Should not be called" );

  Switch( EForgeRollRequestState::Failed );
}



void ForgeRollRequest::ForgeRollAck()
{
  SVC_LOG_MSG.Trace( "Forge roll request delivered to roll service. uid=%d, roll_id=%016x", data.uid, data.rollId );

  Switch( EForgeRollRequestState::Done );
}



void ForgeRollRequest::RollFailed()
{
  SVC_LOG_ERR.Trace( "Failed to deliver forge roll request to roll service! uid=%d, roll_id=%016x", data.uid, data.rollId );

  //FIXME: Retry?

  Switch( EForgeRollRequestState::Failed );
}



void ForgeRollRequest::TryRetry()
{
  if ( retryIndex < s_rollMaxTries )
  {
    ++retryIndex;
    SwitchWoExpire( EForgeRollRequestState::Cooldown );
    cooldownEnds = now + s_rollRetryCooldown;
  }
  else
  {
    SVC_LOG_ERR.Trace( "Max retries reached, removing forge roll request. uid=%d, roll_id=%016x", data.uid, data.rollId );
    SwitchWoExpire( EForgeRollRequestState::Failed );
  }
}

} //namespace HttpGateway

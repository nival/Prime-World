#include "stdafx.h"
#include "RollSeClient.h"
#include "Server/WebClient/WebJsonClient.h"
#include "RollConfig.h"
#include "System/SafeTextFormatStl.h"
#include "RollLog.h"
#include <json/reader.h>
#include <json/writer.h>


namespace roll
{

    SeClientWorker::SeClientWorker( IConfigProvider * _cfg ) :
config( _cfg )
{
    packetAwardsSize = _cfg->Cfg()->packetAwardsSize;
    sendPacketAwards = _cfg->Cfg()->sendPacketAwards;
    httpClient = webClient::NewJsonClient( config->Cfg()->seDumpJson, config->Cfg()->sePrettyJson ); //TEMP: pretty verbose json
}



void SeClientWorker::AddMessage( SeMessageBase * _msg )
{
    threading::MutexLock lock( lineMutex );
    line.push_back ( _msg );

    _msg->SetStatus( ESeMsgStatus::Waiting );
}

void SeClientWorker::PacketWorker()
{
    if ( line.empty()){
        Sleep( 10 );
        return;
    }
    int packetCount = 0; 
    Messages pack; 
    while (!line.empty() && packetCount <= packetAwardsSize){

        StrongMT<SeMessageBase> msg = Pop();

        if ( !msg ) {
            Sleep( 10 );
            continue;
        }
        pack.push_back(msg);

        packetCount++;
    }

    try
    {
        if ( DeliverPacket(pack) )
        {
            SetStatusForPack( ESeMsgStatus::Delivered, pack );
            return ;
        }

    }
    catch( const std::runtime_error & err )
    {
        ROLL_LOG_ERR( "Catched runtime error exception: %s", err.what() );
    }
    RollBackPacket( pack );


}

bool SeClientWorker::DeliverPacket(const Messages& pack)
{
    StrongMT<RollConfig> cfg = config->Cfg();
    string url = NI_STRFMT( "%s?method=send_nl&sender=%s&is_packet=%s", cfg->seUrl, cfg->seSender, sendPacketAwards );
    ROLL_LOG_DBG( "Delivering packet SE message. url=%s, packet size: %d", url , pack.size());

    try
    {
        Json::Value frame ( Json::arrayValue  );
        for(Messages::const_iterator it = pack.begin(); it!= pack.end(); ++it)
        {
            SeMessageBase* msg = (*it);

            Json::Value jsonMsg( Json::objectValue );

            Json::Value val( Json::objectValue );
            msg->FormJson( val );
            
            //Json::Value request( Json::arrayValue );
            //request.append( val );
            jsonMsg["request"] = val;

            msg->FormUrlForPacket(jsonMsg);

            frame.append(jsonMsg);


        }
        Json::Value answer;
        if ( !httpClient->PerformJsonPOST( url.c_str(), frame, answer ) )
            return false;

        int ec = answer["ec"].asInt();
        if ( ec == 0 ) 
        {
            ROLL_LOG_DBG( "SE pack message delivered. %s");
            return true;
        }

        Json::Value errMsg = answer["em"];
        if ( errMsg.type() == Json::stringValue )
            ROLL_LOG_ERR( "SE message was not delivered! se_err_code=%d, msg=\"%s\"", ec, errMsg.asString() );
        else
            ROLL_LOG_ERR( "SE message was not delivered! se_err_code=%d", ec );

    }
    catch( const std::runtime_error & err )
    {
        ROLL_LOG_ERR( "Catched runtime error exception: %s", err.what() );
        return false;
    }
    catch( const char * err )
    {
        ROLL_LOG_ERR( "Catched const char * exception: %s", err );
        return false;
    }

    return false;

}

void SeClientWorker::SetStatusForPack(ESeMsgStatus::Enum st, Messages & pack)
{
    
    for(Messages::const_iterator it = pack.begin(); it!= pack.end(); ++it)
    {
        SeMessageBase* msg = (*it);
        msg->SetStatus( st );
    }

}

void SeClientWorker::RollBackPacket( const Messages & pack)
{
    ROLL_LOG_DBG( "Rolling back failed packet of SE message.");
    for(Messages::const_iterator it = pack.begin(); it!= pack.end(); ++it)
    {
        RollBack( (*it) );
    }

}


void SeClientWorker::SingleWorker()
{
    StrongMT<SeMessageBase> msg = Pop();

    if ( !msg ) {
        Sleep( 10 );
        return;
    }

    try
    {
        if ( Deliver( msg ) ) {
            msg->SetStatus( ESeMsgStatus::Delivered );
            return;
        }
    }
    catch( const std::runtime_error & err )
    {
        ROLL_LOG_ERR( "Catched runtime error exception: %s", err.what() );
    }

    RollBack( msg );
}

void SeClientWorker::Work( volatile bool & isRunning )
{
    while ( isRunning )
    {
        if (sendPacketAwards)
        {
            PacketWorker();
        }
        else
        {
            SingleWorker();
        }

    }
}



StrongMT<SeMessageBase> SeClientWorker::Pop()
{
    timer::Time t = timer::Now();

    threading::MutexLock lock( lineMutex );

    if ( line.empty() )
        return 0;

    for ( Messages::iterator it = line.begin(); it != line.end(); ++it )
    {
        StrongMT<SeMessageBase> msg = *it;
        if ( !msg->NextRetry() || ( t > msg->NextRetry() ) ) {
            msg->DelayRetry( t );
            line.erase( it );
            return msg;
        }
    }

    return 0;
}



bool SeClientWorker::Deliver( SeMessageBase * msg )
{
    StrongMT<RollConfig> cfg = config->Cfg();
    string url = NI_STRFMT( "%s?method=send_nl&sender=%s", cfg->seUrl, cfg->seSender);
    msg->FormUrl( url );

    ROLL_LOG_DBG( "Delivering SE message. %s, %s, url=%s", msg->GetLogId(), msg->GetLogExtInfo(), url );

    try
    {

        Json::Value arrItem( Json::objectValue );
        msg->FormJson( arrItem );

        Json::Value request( Json::arrayValue );
        request.append( arrItem );

        Json::Value answer;
        if ( !httpClient->PerformJsonPOST( url.c_str(), request, answer ) )
            return false;

        int ec = answer["ec"].asInt();
        if ( ec == 0 ) {
            ROLL_LOG_DBG( "SE message delivered. %s", msg->GetLogId() );
            return true;
        }

        Json::Value errMsg = answer["em"];
        if ( errMsg.type() == Json::stringValue )
            ROLL_LOG_ERR( "SE message was not delivered! %s, se_err_code=%d, msg=\"%s\"", msg->GetLogId(), ec, errMsg.asString() );
        else
            ROLL_LOG_ERR( "SE message was not delivered! %s, se_err_code=%d", msg->GetLogId(), ec );
    }
    catch( const std::runtime_error & err )
    {
        ROLL_LOG_ERR( "Catched runtime error exception: %s", err.what() );
        return false;
    }
    catch( const char * err )
    {
        ROLL_LOG_ERR( "Catched const char * exception: %s", err );
        return false;
    }

    return false;
}



void SeClientWorker::RollBack( SeMessageBase * msg )
{
    ROLL_LOG_DBG( "Rolling back failed SE message. %s, cooldown=%.1f", msg->GetLogId(), msg->RetryCooldown() );

    threading::MutexLock lock( lineMutex );

    line.push_back( msg );
}

} //namespace roll

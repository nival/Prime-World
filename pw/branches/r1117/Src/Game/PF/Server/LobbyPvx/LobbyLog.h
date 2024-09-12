#ifndef LOBBYLOG_H_INCLUDED
#define LOBBYLOG_H_INCLUDED

//
//Shortcuts for ugly logging macroses
//

#define LOBBY_SVC_CHNL "lobby"

#define LOBBY_LOG_MSG LOG_M( LOBBY_SVC_CHNL ).Trace
#define LOBBY_LOG_DBG LOG_D( LOBBY_SVC_CHNL ).Trace
#define LOBBY_LOG_ERR LOG_E( LOBBY_SVC_CHNL ).Trace
#define LOBBY_LOG_WRN LOG_W( LOBBY_SVC_CHNL ).Trace

#endif // LOBBYLOG_H_INCLUDED

#ifndef NEWLOGINLOG_H_INCLUDED
#define NEWLOGINLOG_H_INCLUDED

//
//Shortcuts for ugly logging macroses
//

#define NEWLOGIN_SVC_CHNL "newlogin"

#define NEWLOGIN_LOG_MSG LOG_M( NEWLOGIN_SVC_CHNL ).Trace
#define NEWLOGIN_LOG_DBG LOG_D( NEWLOGIN_SVC_CHNL ).Trace
#define NEWLOGIN_LOG_ERR LOG_E( NEWLOGIN_SVC_CHNL ).Trace
#define NEWLOGIN_LOG_WRN LOG_W( NEWLOGIN_SVC_CHNL ).Trace

#endif // NEWLOGINLOG_H_INCLUDED

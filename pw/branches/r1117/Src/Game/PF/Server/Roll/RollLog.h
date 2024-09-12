#ifndef ROLLLOG_H_INCLUDED
#define ROLLLOG_H_INCLUDED

//
//Shortcuts for ugly logging macroses
//

#define ROLL_SVC_CHNL "roll"

#define ROLL_LOG_MSG LOG_M( ROLL_SVC_CHNL ).Trace
#define ROLL_LOG_DBG LOG_D( ROLL_SVC_CHNL ).Trace
#define ROLL_LOG_ERR LOG_E( ROLL_SVC_CHNL ).Trace
#define ROLL_LOG_WRN LOG_W( ROLL_SVC_CHNL ).Trace

#endif ROLLLOG_H_INCLUDED

#ifndef INCLUDED_QIXLOGGER_H
#define INCLUDED_QIXLOGGER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "ace/Synch.h"
#include <fstream>
#include <string>

class ACE_INET_Addr;


/**
* @class Logger
* @brief inteface for logger object
*
* @author  Alexander Libman
* @version 1.0
*
*/
class Logger 
{
public:

    enum
    {
        LOG_ZERO       = 0x0000,
        LOG_NL_BEFORE  = 0x0001,
        LOG_NL_AFTER   = 0x0002,
        LOG_TIMESTAMP  = 0x0004,
        LOG_ALL        = 0xFFFF
    };
    
    Logger ();
    virtual ~Logger ();

    /// get date stamp in format YYYYMMDD
    static void  getDateStamp (char * strDate);

    /// get time stamp in format HH:MM:SS.MLS
    static void  getTimeStamp (char * strTime);

    bool open  (const char * fileName);
    void close ();

    bool write (const char * data, 
                size_t len = 0,
                int  flags = LOG_ZERO);

    int  getFlags () const  { return m_flags;}
    void setFlags (int flg) { ACE_SET_BITS (m_flags, flg); }
    void clrFlags (int flg) { ACE_CLR_BITS (m_flags, flg); }
    

protected:

    //typedef ACE_SYNCH_MUTEX  Mutex;
    typedef ACE_SYNCH_NULL_MUTEX  Mutex;

    Mutex          m_mtx;
    std::string    m_fileName;
    std::ofstream  m_out;
    int            m_flags;
};


#endif // INCLUDED_LOGGER_H
//==============================End of File ====================================


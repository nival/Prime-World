#include "Logger.h"

#include "ace/Date_Time.h"
#include "ace/INET_Addr.h"
#include "ace/OS_NS_stdio.h"
#include "ace/OS_NS_sys_stat.h"
#include "ace/ACE.h"

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
void 
Logger::getDateStamp (char * strDate)
{
    ACE_Date_Time time;

    sprintf (strDate, "%04d%02d%02d",
        (int) time.year(),
        (int) time.month(),
        (int) time.day());

}

void 
Logger::getTimeStamp (char * strTime)
{
    ACE_Date_Time time;

    sprintf (strTime, "%02d:%02d:%02d.%03d",
        (int) time.hour(),
        (int) time.minute(),
        (int) time.second(),
        (int) (time.microsec()/1000));

}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
Logger::Logger ()
: m_mtx        ()
, m_fileName   ()
, m_out        ()
, m_flags      (LOG_ZERO)
{
}
Logger::~Logger ()
{
    close();
}

bool
Logger::open (const char * fileName)
{
    {
        ACE_GUARD_RETURN (Mutex, guard, m_mtx, false);

        if (m_out.is_open ())
            return false;

        char dateBuf [16];

        getDateStamp (dateBuf);

        m_fileName = fileName;
        m_fileName.append (".");
        m_fileName.append (dateBuf);

        const char * strName = m_fileName.c_str();

        ACE_OS::mkdir (ACE::dirname (strName , '/'));
    
        m_out.open (strName,
                    std::ios_base::out | 
                    std::ios_base::app |
                    std::ios_base::binary);

        if (! m_out.is_open ())
            return false;
    }

    return write ("OPEN  LOG ============================",
                  0, 
                  LOG_TIMESTAMP | LOG_NL_AFTER);
}

void
Logger::close ()
{
    write ("CLOSE LOG ============================",
           0, 
           LOG_NL_BEFORE | LOG_TIMESTAMP | LOG_NL_AFTER);

    ACE_GUARD(Mutex, guard, m_mtx);
    if (m_out.is_open ())
    {
        m_out.close ();
    }
}



bool
Logger::write (const char * data, size_t len, int flags)
{
    ACE_GUARD_RETURN (Mutex, guard, m_mtx, false);

    ACE_SET_BITS (flags, m_flags);

    if (ACE_BIT_ENABLED (flags, LOG_NL_BEFORE))
    {
        m_out << std::endl;
    }

    if (ACE_BIT_ENABLED (flags, LOG_TIMESTAMP))
    {
        char  timeBuf [16];
        getTimeStamp (timeBuf);
        m_out << timeBuf 
        << " ";
    }

    if (len == 0)
        len = strlen(data);

    m_out.write (data, len);

    if (ACE_BIT_ENABLED (flags, LOG_NL_AFTER))
    {
        m_out << std::endl;
    }

    m_out.flush ();
    return m_out.good ();
}





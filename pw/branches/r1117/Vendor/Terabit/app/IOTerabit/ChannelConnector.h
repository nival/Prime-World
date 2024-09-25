#ifndef TERABIT_CHANNELCONNECTOR_H 
#define TERABIT_CHANNELCONNECTOR_H 

#include "IOTerabit/IOTERABIT_Export.h"
#include "IOTerabit/BaseConnector.h"


namespace Terabit {

class ChannelManager;
class ProtocolFactory;
class IOThreadPool;

/**
 * @class Connector
 * @brief universal asynchronous connector
 *
 * Connector - asynchronously establish outgoing connections
 * and  provides creation Channel and Procotol objects with
 * the help of ChannelManager,  and ProtocolFactory.
 *
 */
class IOTERABIT_Export ChannelConnector : public BaseConnector
{
public:
    ChannelConnector (IOThreadPool &     task,
                      ProtocolFactory &  protocol_factory, 
                      ChannelManager &   manager);

    virtual ~ChannelConnector (void);

public:
    IOThreadPool &   task (void) const { return task_; }
    ChannelManager & manager (void) const { return manager_; }

    ProtocolFactory & protocol_factory (void) const 
    {
        return protocol_factory_;
    }


    int    get_log_level (void) const { return this->log_level_;}
    void   set_log_level (int level)  { this->log_level_ = level;}

    bool   is_safe_to_delete (void) const
    {
        return (this->get_pending_count() == 0);
    }

    int    start (const ACE_Addr & addr, const void *act);


private:

    virtual int on_connect_completed ( const TRB_Asynch_Connect::Result&  result);

    IOThreadPool &    task_;
    ProtocolFactory & protocol_factory_;
    ChannelManager &  manager_;
    int               log_level_;

};

}  //namespace Terabit 

#endif // TERABIT_CHANNELCONNECTOR_H 


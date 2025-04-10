#ifndef TERABIT_CHANNELMANAGER_H 
#define TERABIT_CHANNELMANAGER_H 

#include "IOTerabit/IOTERABIT_Export.h"
#include "IOTerabit/AsynchChannel.h"
#include "IOTerabit/IOThreadPool.h"

#include "TProactor/Monitor_T.h"
#include "ace/SString.h"


namespace Terabit {

/**
  * @class ChannelManager
  * @brief provides registration, control and management 
  * of all active connections
  *
  * @li ChannelManager is responsible for creation and registration
  *     of Channel objects. It delegates Channel object construction 
  *     to the appropriate AsynchChannelFactory::create_connection() method 
  *     and then inserts the created Channel object into an internal collection
  *     of active connections.
  * @li When Channel object is destroyed, it notifies its ChannelManager, 
  *     which then removes the Channel object from its collection
  *     of active connections and calls the appropriate
  *     AsynchChannelFactory::destroy_connection() method.
  * @li ChannelManager periodically checks the "health" of each 
  *     Channel according to  "watch dog" timeout property. 
  * @li Upon receipt of a stop request, ChannelManager prohibits creation 
  *     of new Channels and initiates termination of all existing Channels. 
  * @li ChannelManager sets up and propagates the logger level for all connections.
  * @li ChannelManager accumulates connection statistics that can be used 
  *     for performance evaluation.
  *
  */
class IOTERABIT_Export ChannelManager : public TRB_Handler
{
    typedef ACE_SYNCH_MUTEX              Mutex;
    typedef ACE_SYNCH_CONDITION          Condition;
    typedef Monitor_T<Mutex,Condition>   Monitor;
    typedef Guard_Monitor_T<Monitor>     Guard_Monitor;
    typedef Guard_Monitor::Save_Guard    Save_Guard;

    
    friend class AsynchChannel;

    enum State
    {
        ST_INIT   = 0x0000,   // BEFORE OPEN
        ST_ACTIVE = 0x0001,   // OPERATIONAL
        ST_CANCEL = 0x0002,   // IN CANCEL
        ST_CLOSED = 0x0004    // CLOSED
    };

    enum Flags
    {
        FLG_CHECK_ACTIVE = 0x0001,
        FLG_CLOSE_ACTIVE = 0x0002,
        FLG_FREE_CHANNEL = 0x0004
    };

public:

    struct Statistic 
    {
    public:
        ACE_UINT64  total_snd_;        // Total bytes successfully sent
        ACE_UINT64  total_rcv_;        // Total bytes successfully received
        ACE_UINT64  total_w_;          // Number of performed write operations
        ACE_UINT64  total_r_;          // Number of performed read operations
        ACE_UINT64  total_channels_;   // total channels created (history)
        u_int       max_channels_;     // max allowed number of simultaneous channels
        u_int       peak_channels_;    // max reached number of simultaneous channels
        u_int       current_channels_; // current number of active channels

        Statistic (size_t max_channels = (size_t)-1)
            : total_snd_        (0)    
            , total_rcv_        (0)  
            , total_w_          (0)  
            , total_r_          (0)  
            , total_channels_   (0)
            , max_channels_     (max_channels)  
            , peak_channels_    (0) 
            , current_channels_ (0)
        {}

        void print(const ACE_TCHAR *mgr_name);
    };


    ChannelManager (const ACE_TCHAR *       name,
                    IOThreadPool &          task,
                    AsynchChannelFactory &  factory);

    virtual ~ChannelManager  (void);

    const ACE_TCHAR *get_name (void) const;
    IOThreadPool &   get_task (void) const;

    MessageBlockFactory *get_message_block_factory ();
    bool set_message_block_factory (MessageBlockFactory * mb_factory);

    /// @brief return statistic
    void  get_statistic(Statistic & stat);

    /// @brief print statistic into log
    void  print_statistic(void);

    /// @brief set channels limit
    void  set_max_channels(size_t max_channels);



   
    /// @brief get log level
    /// 
    /// @retval 0 - maximum logging full trace
    /// @retval 1 - medium  logging 
    /// @retval 2 - minumum logging, only errors
    int   get_log_level (void) const;

    /// @brief set log level
    /// 
    /// @param logLevel may be:
    /// @li 0 - maximum logging full trace
    /// @li 1 - medium  logging 
    /// @li 2 - minumum logging, only errors
    void  set_log_level (int level);

    /// @brief get watch dog timeout 
    const ACE_Time_Value& get_timeout (void) const;

    /// @brief set watch dog timeout 
    void  set_timeout (const ACE_Time_Value & timeout);

    /// @brief wait till all connections are destroyed and
    /// watch dog timer is cancelled
    int    wait (void);

    /// @brief activate watch dog timer
    int    open ();

    /// @brief cancel all active connections and watch dog timer
    /// this method propagates cancel command to all 
    /// active connections and prevents creation of new connections
    void   close (void);

    /// @brief cancel all active connections 
    /// this method propagates cancel command to all 
    /// active connections, but does not cancel timere and 
    /// does not prevents creation of new connections
    void   close_channels (void);

    /// @brief check all active connections, called on watch dog timeout
    void   check_channels (void);


    /// @brief called when new incoming connection is accepted
    /// or outgoing connection is established
    AsynchChannel *allocate_channel ();

    /// @brief called to deregister and destroy terminated connection
    void    free_channel (AsynchChannel *channel);

    // virtual from TRB_Handler
    virtual void handle_time_out (const ACE_Time_Value&  tv,
                                  const void            *pArg );


private:
    // channels control
    void check_channels_internal (Guard_Monitor& guard);
    void close_channels_internal (Guard_Monitor& guard);
    void free_channel_internal (AsynchChannel *channel);


    // watch dog timer contol
    void cancel_timer_internal (void);
    void start_timer_internal (void);


    Monitor                      monitor_;
    IOThreadPool &               task_;
    AsynchChannelFactory &       factory_;
    ACE_TString                  name_;
    Statistic                    stats_;
    State                        state_; 
    int                          flags_;
    long                         timer_id_;   // active timer id or -1
    ACE_Time_Value               timeout_;    // watch dog timeout
    int                          log_level_;  // log level  
    AsynchChannelList            active_channels_;
    AsynchChannelList::iterator  check_iterator_;
    MessageBlockFactory         *mb_factory_;

};

// ===============================================================
//  inline implementations
// ===============================================================
inline const ACE_TCHAR *
ChannelManager::get_name () const
{
    return this->name_.c_str ();
}

inline IOThreadPool & 
ChannelManager::get_task (void) const
{
    return this->task_;
}

inline MessageBlockFactory *
ChannelManager::get_message_block_factory ()
{
    return this->mb_factory_;
}


inline  int
ChannelManager::get_log_level (void) const 
{ 
    return this->log_level_;
}

inline void 
ChannelManager::set_log_level (int level) 
{ 
    this->log_level_ = level;
}

inline const ACE_Time_Value& 
ChannelManager::get_timeout (void) const
{
    return this->timeout_;
}

inline void 
ChannelManager::set_timeout (const ACE_Time_Value & timeout)
{
    this->timeout_ = timeout;
}

inline void
ChannelManager::set_max_channels(size_t max_channels)
{
    this->stats_.max_channels_ = max_channels;
}

}  //namespace Terabit 


#endif // TERABIT_CHANNELMANAGER_H 

#ifndef CHAT_PROTOCOL_H
#define CHAT_PROTOCOL_H

#include "IOTerabit/AsynchChannel.h"
#include "IOTerabit/Protocol.h"
#include "IOTerabit/WrkThreadPool_T.h"

#include "BufferFactory.h"
#include <map>

class ChatProtocol;

class Job
{
public:
    Job (ChatProtocol      *chat = 0,
         ACE_Message_Block *mb = 0 );

    ~Job ();
   
         
    void cancel (); 
    void set (Job & other);
    void execute ();
    void reset ();

private:
    ChatProtocol       *chat_;
    ACE_Message_Block  *mb_;
};

typedef Terabit::WrkThreadPool_T<Job>  JobThreadPool;
   
// *************************************************************
//   Chat Room 
// *************************************************************

class ChatProtocol :
    public Terabit::ProtocolFactory,
    public Terabit::Protocol
{

public:
    typedef ACE_SYNCH_MUTEX              Mutex;
    typedef ACE_SYNCH_CONDITION          Condition;
    typedef Monitor_T<Mutex,Condition>   Monitor;
    typedef Guard_Monitor_T<Monitor>     Guard_Monitor;
    typedef Guard_Monitor::Save_Guard    Save_Guard;


    ChatProtocol(JobThreadPool &  job_pool,
                 const ACE_TCHAR *name,
                 int              logLevel = 2);

    virtual ~ChatProtocol();

    JobThreadPool & get_job_pool () 
    {
        return job_pool_; 
    }


    void process_message(ACE_Message_Block *mb);
    
    // ProtocolFactory interface
    virtual Terabit::Protocol *create_protocol (const void *act);
    virtual void destroy_protocol  (Terabit::Protocol *protocol);

    virtual int  validate_connection (bool  success,
                                      const ACE_Addr& remote,
                                      const ACE_Addr& local,
                                      const void *act);
    virtual Terabit::MessageBlockFactory *get_message_block_factory ();

private:
    // Protocol interface
    virtual void reset ();
    virtual int on_channel_opened (Terabit::AsynchChannel *channel);
    virtual void on_channel_closed (Terabit::AsynchChannel *channel);

    // this is main parsing method
    virtual int on_read_completed (Terabit::AsynchChannel *channel,
                                   const char    *data,
                                   size_t         length);

    virtual int on_write_completed (Terabit::AsynchChannel *channel);


    // called from on_read_completed
    int enqueue_message(Terabit::AsynchChannel *channel,
                        const char             *payload,
                        size_t                  length);

    
private:

    struct ChannelData 
    {
        int  count_;
        bool flg_del_;
    };
    typedef std::map<Terabit::AsynchChannel *, ChannelData> ChannelMap;

    Monitor          mon_;
    ChannelMap       channels_;

    BufferFactory    mb_factory_;
    JobThreadPool&   job_pool_;
}; 


#endif  // CHAT_PROTOCOL_H


#ifndef TOPIC_H
#define TOPIC_H

#include "TProactor/Double_List_T.h"
#include "IOTerabit/AsynchChannel.h"
#include "BufferFactory.h"


//#include "IOTerabit/Protocol.h"
//#include "IOTerabit/WrkThreadPool_T.h"

#include <map>


   
// *************************************************************
//  Topic
// *************************************************************

class Topic : public RefCount
{

public:
    typedef ACE_SYNCH_MUTEX              Mutex;
    typedef ACE_SYNCH_CONDITION          Condition;
    typedef Monitor_T<Mutex,Condition>   Monitor;
    typedef Guard_Monitor_T<Monitor>     Guard_Monitor;
    typedef Guard_Monitor::Save_Guard    Save_Guard;


    Topic(const ACE_TCHAR *name);

    virtual ~Topic();

    LinkD_T <Topic> * get_link () const;


    void process_message(ACE_Message_Block *mb);
    
    virtual Terabit::MessageBlockFactory *get_message_block_factory ();

private:
    // Protocol interface

    // called from on_read_completed
    int enqueue_message(Terabit::AsynchChannel *channel,
                        const char             *payload,
                        size_t                  length);

    
private:
      /// link element
    mutable LinkD_T <Topic> link_;

    ACE_Message_Queue<ACE_MT_SYNCH> msg_queue_;  

    Monitor          mon_;
    SubscriberList   subscribers_;
    ChannelMap       channels_;

    BufferFactory    mb_factory_;
    JobThreadPool&   job_pool_;
}; 

// *************************************************************
//  Topics
// *************************************************************

class Topics 
{

public:
    typedef ACE_SYNCH_MUTEX              Mutex;
    typedef ACE_SYNCH_CONDITION          Condition;
    typedef Monitor_T<Mutex,Condition>   Monitor;
    typedef Guard_Monitor_T<Monitor>     Guard_Monitor;
    typedef Guard_Monitor::Save_Guard    Save_Guard;
    typedef std::map <const char *, TopicPtr> TopicMap;   

private:

};


LinkD_T<Topic> * 
Topic::get_link () const
{
    return 

class Topic2Link 
{
public :
    LinkD_T <Topic> * 
    operator () (const  Topic *x)  const 
    {
        return x->get_link ();
    }
};



#endif  // TOPIC

//
#include "ace/Synch_T.h"
#include "ace/Get_Opt.h"
#include "ace/Task_T.h"
//#include "ace/ARGV.h"
#include "TProactor/Monitor_T.h"

#include <iostream>
//#include <algorithm>

typedef ACE_SYNCH_MUTEX            Mutex;
typedef ACE_SYNCH_CONDITION        Condition;
typedef Monitor_T<Mutex,Condition> Monitor;
typedef Guard_Monitor_T<Monitor>   Guard_Monitor;
typedef Guard_Monitor::Save_Guard  Save_Guard;


class MyTask : public ACE_Task_Base
{
public:

    MyTask ()
    : monitor_     ()
    , num_threads_ (0)
    , flg_stop_     (false)
    {}

    virtual ~MyTask()
    {
        stopAndWait ();
    }

    virtual int svc (void);

    bool start (int num_threads);
    bool stop  ();
    bool stopAndWait  ();
    bool waitForOneSec ();


private:
    Monitor   monitor_;
    int       num_threads_;
    volatile bool flg_stop_;
};

bool
MyTask::waitForOneSec ()
{
    Guard_Monitor guard(this->monitor_);
    ACE_Time_Value tv (1, 0);

    ACE_ASSERT (guard.locked ());
    ACE_ERROR ((LM_DEBUG,
           ACE_TEXT ("(%t) MyTask::begin wait\n")));

    int rc = guard.wait (&tv, false);

    ACE_ERROR ((LM_DEBUG,
           ACE_TEXT ("(%t) MyTask::end wait rc=%d\n"), rc));

    return (rc==0);
}


bool
MyTask::start (int num_threads)
{
    Guard_Monitor guard(this->monitor_);

    if (num_threads == 0)
    {
        ACE_ERROR ((LM_ERROR,
           ACE_TEXT ("(%t) MyTask::start - invalid parameter\n")));

        return false;
    }

    if (this->num_threads_ != 0)
    {
        ACE_ERROR ((LM_ERROR,
           ACE_TEXT ("(%t) MyTask::start - already started\n")));
        return false;
    }

    flg_stop_ = false;

    // activate "numThreads" 
    if (this->activate (THR_NEW_LWP| THR_JOINABLE, num_threads) < 0)
    {
        ACE_ERROR ((LM_ERROR,
            ACE_TEXT ("(%t) MyTask::start - unable to activate\n")));
        return false;
    }
    
    while (num_threads_ != num_threads)
    {
        guard.wait ();
    }

    ACE_ASSERT (guard.locked ());

    return true;
}

bool
MyTask::stop ()
{
    Guard_Monitor guard(this->monitor_);
    flg_stop_ = true;
    return true;
}

bool
MyTask::stopAndWait ()
{
    {
        Guard_Monitor guard(this->monitor_);

        ACE_ASSERT (guard.locked ());
        flg_stop_ = true;

        while (num_threads_ != 0)
        {
            guard.wait ();
        }
        ACE_ASSERT (guard.locked ());
    }

    this->wait ();
    return true;
}

int
MyTask::svc ()
{
    Guard_Monitor guard(this->monitor_);

    int num = ++num_threads_;

    ACE_ERROR ((LM_ERROR,
        ACE_TEXT ("(%t) MyTask::begin thread %d\n"),
        num));

    guard.signal ();


    while (!flg_stop_)
    {
        ACE_ASSERT (guard.locked ());
        {
            Save_Guard saver (guard, Save_Guard::RELEASE);
            ACE_ASSERT (!guard.locked ());

            {
                Save_Guard saver2 (guard, Save_Guard::ACQUIRE);
                ACE_ASSERT (guard.locked ());
            }
            ACE_ASSERT (!guard.locked ());

            ACE_OS::sleep (1);
        }
    }

    --num_threads_;
    ACE_ERROR ((LM_ERROR,
        ACE_TEXT ("(%t) MyTask::end thread %d , remain %d\n"),
        num, num_threads_));

    guard.signal ();
    ACE_ASSERT (guard.locked ());

    return 0;
}

// ******************************************************************
//
// ******************************************************************
bool getCmd(std::string & str )
{
    char buf[512];

    do                
    {                
        errno=0;      
        std::cout.flush();
        std::cin.clear();  
        std::cin.getline(buf, sizeof(buf)-8);
    } while (errno!=0);
    str = buf;

    return true;
}

int
ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
    bool flgExit = false;
    MyTask task;

    for ( ; !flgExit ; )
    {
        std::cout << "\nS -start Task"
                  << "\nP -stop  Task"
                  << "\nW -stop  1 sec"
                  << "\nQ/E - Exit ==>" ;

        std::string cmd;
        getCmd (cmd);
        if (cmd.size () == 0)
        {
            continue;
        }


        char c1 = toupper (cmd[0]);
        switch ( c1 )
        {
        case 'S':
            task.start (::atoi(cmd.c_str()+1));
            break;
        case 'P' :
            task.stopAndWait();
            break;
        case 'W':
            task.waitForOneSec ();
            break;
        case 'Q' :
        case 'E' : 
            flgExit = true;
            break;
        }
    }

    return 0;
}



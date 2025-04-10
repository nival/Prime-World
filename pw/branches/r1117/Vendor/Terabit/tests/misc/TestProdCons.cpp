//====================================================================
//
//====================================================================
#include <iostream>
#include <string>
#include "Thread_Pool_T.h"

static const unsigned int MAX_NUM_THREADS = 1000;
static const unsigned long MAX_MESSAGES = 0x7FFFFFFFL;

long    time_to_run = 5;
int     debug_level = 0;
size_t  low_mark = 20000;
size_t  high_mark = 1000;
size_t  num_threads = 5;
size_t  num_messages = 100000;


class Data : public std::string
{
public:
    Data (const char * str = "") : std::string (str) {}

    Data (const std::string & str) : std::string (str) {}

    Data (const Data & other) : std::string (other)  {}

    bool call ()
    {
        if (debug_level == 0)
        {
            ACE_ERROR ((LM_DEBUG, "(%t) Data::call %s\n", this->c_str()));
        }
        return true;
    }
};

typedef Thread_Pool_T<Data> DataThreadPool;
typedef Activator_T<Data>   DataActivator;

void usage (char * name)
{
    std::cout << "Usage:" 
        << std::endl
        << name 
        << " Lnnn Hnnn Pnnn Cnnn Tnnn Dnnn" << std::endl
        << " L low water-mark"  << std::endl
        << " H high water-mark" << std::endl
        << " T number threads" << std::endl
        << " M number messages to process" << std::endl
        << " D debug level : 2-min, 1-medium, 0-full" << std::endl;

    exit (-1);
}

bool getCmd(std::string & str )
{
    char buf[512];

    do                
    {                
        errno=0;      
        std::cout.flush();
        std::cin.clear();  
        std::cin.getline(buf, sizeof(buf)-8);
        
	    str = buf;

    }while (errno!=0 || str.length()==0);

    return true;
}


int run ()
{
    
    DataThreadPool myTask;  

    if (!myTask.start (num_threads, DataActivator()))
        return -1;

    bool flgExit = false;

    Data data;
    


    for ( ; !flgExit ; )
    {
		ACE_ERROR ((LM_INFO,
            "\n------------------------"
            "\nA NN activate  1-READER, 2-WRITER, 3-BOTH"
            "\nD NN deactivate 1-READER, 2-WRITER, 3-BOTH"
            "\nP NNNN put NNNN messages"
            "\nL set Log Level 2-min/1-medium/0-max"
            "\nQ Exit ==>"));

        std::string cmd;
        getCmd (cmd);

        char c = toupper (cmd[0]);

        cmd.erase (0,1);
        while (cmd.size ()!= 0  && isspace(cmd[0]))
        {
            cmd.erase (0,1);
        }

        switch ( c )
        {
        case 'L' :
            debug_level = atoi (cmd.c_str());
            break;
        case 'A' :
            myTask.getQueue().activate (atoi (cmd.c_str()));
            break;
        case 'D' :
            myTask.getQueue().deactivate (atoi (cmd.c_str()));
            break;
        case 'P' :
            data = cmd;
            num_messages = atoi (cmd.c_str());
            if (num_messages <= 0)
                num_messages = 1;

            for (size_t i=0; i < num_messages; ++i)
            {
                char buf [512];
                sprintf (buf, "msg_%Ld", (long long) i);
                data = buf;
                myTask.putq (data);
            }
            break;

        case 'Q' : 
            flgExit = true;
            break;
        }
    }

    const DataThreadPool::Queue & engine = myTask.getQueue ();
    
    size_t num_get = engine.get_total_get();
    size_t num_put = engine.get_total_put();
    size_t num_empty_sig = engine.get_num_empty_signals ();
    size_t num_full_sig  = engine.get_num_full_signals ();

    
    std::cout << "Messages: Sent="
            << num_put
            << " Recv="
            << num_get
            << std::endl
            << "Signals : NotEmpty="
            << num_empty_sig
            << " NotFull="
            << num_full_sig
            << std::endl;
    return 0;
}


void 
parse_args (int argc, char* argv[])
{
    int i = 1;
   
    for ( ; i < argc; ++i )
    {
        char * cur = argv[i];

        switch (toupper(*cur))
        {
        case 'D': 
            debug_level = atol(cur+1);
            break;
        case 'L':
            low_mark = atol(cur+1);
            break;
        case 'H':
            high_mark = atol(cur+1);
            break;
            break;
        case 'T':
            num_threads = atol(cur+1);
            break;
        case 'M':
            num_messages = atol(cur+1);
            break;
		case '\r':
		case '\n':
		    break;
        default:
            usage(argv[0]);
            break;
        }
    }

    if (high_mark < low_mark)             high_mark = low_mark;

    if (num_threads == 0)                 num_threads = 1;
    if (num_threads > MAX_NUM_THREADS)    num_threads = MAX_NUM_THREADS;

    if (num_messages > MAX_MESSAGES)      num_messages = MAX_MESSAGES;
    
    std::cout << "===== TaskPool Parameters =====" 
        << std::endl 
        << " LOW_MARK="  << low_mark
        << " HIGH_MARK=" << high_mark
        << " Threads="   << num_threads
        << std::endl;
}

int
main (int argc, char* argv[])
{
    parse_args (argc, argv);

    int rc = run ();

    return rc;
}


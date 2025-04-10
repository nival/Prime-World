
#include "ace/Get_Opt.h"
#include "ace/ARGV.h"
#include "TProactor/Double_List_T.h"

#include <iostream>
#include <algorithm>

// ******************************************************************
//
// ******************************************************************
class ElemS 
{
private:
    int     m_i;
    mutable LinkS_T<ElemS> m_link;
    
public: 
    ElemS (int i) : m_i (i) {}
    void dump (const char *txt) 
    {
        ACE_DEBUG ((LM_DEBUG, "%s m_i=%d this=%@ next_=%@\n",
            txt, m_i, this, m_link.get() ));
    }

    int value () const { return m_i;}

    LinkS_T<ElemS> * get_link ()  const { return & m_link; }

    // functor-convertor of object reference to link reference
    class ElemSToLink 
    {
    public:
        LinkS_T <ElemS> * operator () (const ElemS * el) const
        {
            return el->get_link () ;
        }
    };
};

typedef Single_List_T<ElemS, ElemS::ElemSToLink> ElemSList;

void dump (ElemSList & list, ElemSList::iterator it)
{
    //std::for_each (list.begin(), list.end (), std::mem_fun <void,ElemS> ( &ElemS::dump));
    ACE_DEBUG ((LM_DEBUG, "S: size=%d begin=%@ end=%@ front=%@ back=%@ itr=%@\n",
        (int) list.size(), *list.begin(), *list.end(), 
        list.front(), list.back (), *it 
        ));

    ElemSList::iterator it1 = list.begin();
    ElemSList::iterator it2 = list.end();
    for (int i=1; it1 != it2 ; ++i, ++it1)
    {
        ACE_DEBUG((LM_INFO, "%d. ", i));
        if (it1 == it)
            (*it1)->dump ("==>");
        else
            (*it1)->dump ("   ");
    }

}

typedef Single_Queue_T<ElemS, ElemS::ElemSToLink> ElemSQueue;

void dump (ElemSQueue & queue, ElemSQueue::iterator it)
{
    //std::for_each (queue.begin(), queue.end (), std::mem_fun <void,ElemS> ( &ElemS::dump));
    ACE_DEBUG ((LM_DEBUG, "Q: size=%d begin=%@ end=%@ front=%@ back=%@ itr=%@\n",
        (int) queue.size(), *queue.begin(), *queue.end(), 
        queue.front(), queue.back (), *it 
        ));

    ElemSQueue::iterator it1 = queue.begin();
    ElemSQueue::iterator it2 = queue.end();
    for (int i=1; it1 != it2 ; ++i, ++it1)
    {
        ACE_DEBUG((LM_INFO, "%d. ", i));
        if (it1 == it)
            (*it1)->dump ("==>");
        else
            (*it1)->dump ("   ");
    }

}

// ******************************************************************
//
// ******************************************************************

class ElemD 
{
private:
    int m_i;
    mutable LinkD_T<ElemD> m_link;
    
public: 
    ElemD (int i) : m_i (i) {}
    void dump (const char *txt) 
    {
        ACE_DEBUG ((LM_DEBUG, "%s m_i=%d this=%@ next_=%@ prev_=%@\n",
            txt, m_i, this, m_link.next(), m_link.prev() ));
    }

    int value () const { return m_i;}

    LinkD_T<ElemD> * get_link ()  const { return & m_link; }

    // functor-convertor of object reference to link reference
    class ElemDToLink 
    {
    public:
        LinkD_T <ElemD> * operator () (const ElemD * el) const
        {
            return  el->get_link ();
        }
    };
};

typedef Double_List_T<ElemD, ElemD::ElemDToLink> ElemDList;


void dump (ElemDList & list, ElemDList::iterator it)
{
    //std::for_each (list.begin(), list.end (), std::mem_fun <void,ElemD> ( &ElemD::dump));
    ACE_DEBUG ((LM_DEBUG, "D: size=%d begin=%@ end=%@ front=%@ back=%@ itr=%@\n",
        (int) list.size(), *list.begin(), *list.end(), 
        list.front(), list.back (), *it 
        ));

    ElemDList::iterator it1 = list.begin();
    ElemDList::iterator it2 = list.end();
    for (int i=1; it1 != it2 ; ++i, ++it1)
    {
        ACE_DEBUG((LM_INFO, "%d. ", i));
        if (it1 == it)
            (*it1)->dump ("==>");
        else
            (*it1)->dump ("   ");
    }

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
testSingleList()
{
    bool flgExit = false;

    int  cnt = 0;

    ElemSList list;
    ElemSList::iterator itr = list.begin();

   
    for ( ; !flgExit ; )
    {
        dump (list, itr);
        std::cout << "\nI[B|E] - Insert at Begin|End"
                  << "\nR[B|E|V] - Remove at Begin|End|Value-Addr"
                  << "\nSNNNN  - set iterator to pos NNNN"
                  << "\nF      - find iterator"
                  << "\nLNNNN  - splice with list NNNN"
                  << "\nP - print list"
                  << "\nE - Exit ==>" ;

        std::string cmd;
        getCmd (cmd);
        if (cmd.size () == 0)
        {
            continue;
        }


        char c1 = toupper (cmd[0]);
        char c2 = toupper (cmd[1]);
        ElemS * node = 0;


        switch ( c1 )
        {
        case 'F':
            {
              node = list.find (*itr);
              ACE_DEBUG ((LM_DEBUG, "Found node=%@\n", node));
            }
            break;

        case 'I' :
            switch (c2)
            {
            case 'B':
                list.push_front (new ElemS(++cnt));
                itr = list.begin();
                break;
            case 'E':
                list.push_back (new ElemS(++cnt));
                itr = list.end();
                break;
            default:
                break;
            }
            break;

        case 'R' :
            switch (c2)
            {
            case 'R':
                node = list.pop_front();
                ACE_ASSERT (node == 0 || node->get_link()->is_free ());
                if (node != 0)
                {
                    list.push_front (node);
                    node = 0;
                }
                itr = list.begin ();
                break;
            case 'E':
                node = list.pop_back ();
                ACE_ASSERT (node == 0 || node->get_link()->is_free ());
                itr = list.end ();
                break;
            case 'B':
                node = list.pop_front ();
                ACE_ASSERT (node == 0 || node->get_link()->is_free ());
                itr = list.begin();
                break;
            case 'V':
                node = list.remove(*itr);
                ACE_ASSERT (node == 0 || node->get_link()->is_free ());
                itr = list.begin();
                break;
            default:
                break;
            }
            ACE_DEBUG ((LM_DEBUG, "Deleting node=%@\n", node));
            delete node;
            break;

        case 'P' :
            dump (list, itr);
            break;
       case 'S' :
            {
               size_t pos = atoi(cmd.c_str() + 1) -1;
               if (pos > list.size ())
               {
                   pos = list.size ();
               }

               itr = list.begin();

               for ( size_t i=0; i < pos; ++i, ++itr)
               {
               }
            }    
            break;
       case 'L' :
            {
               size_t pos = atoi(cmd.c_str() + 1);
               ElemSList list2;
               for (size_t i=0; i < pos; ++i)
               {
                   list2.push_back (new ElemS(++cnt));
               }
               list.splice (list2);
               dump (list2, list2.begin ());
            }
            break;


        case 'E' : 
            flgExit = true;
            break;
        }
    }

    return 0;
}

int
testQueue()
{
    bool flgExit = false;

    int  cnt = 0;

    ElemSQueue queue;
    ElemSQueue::iterator itr = queue.begin();

   
    for ( ; !flgExit ; )
    {
        dump (queue, itr);
        std::cout << "\nI[B|E] - Insert at Begin|End"
                  << "\nR[B|E|V] - Remove at Begin|End|Value-Addr"
                  << "\nSNNNN  - set iterator to pos NNNN"
                  << "\nF      - find iterator"
                  << "\nLNNNN  - splice with list NNNN"
                  << "\nP - print list"
                  << "\nE - Exit ==>" ;

        std::string cmd;
        getCmd (cmd);
        if (cmd.size () == 0)
        {
            continue;
        }


        char c1 = toupper (cmd[0]);
        char c2 = toupper (cmd[1]);
        ElemS * node = 0;


        switch ( c1 )
        {
        case 'F':
            {
              node = queue.find (*itr);
              ACE_DEBUG ((LM_DEBUG, "Found node=%@\n", node));
            }
            break;

        case 'I' :
            switch (c2)
            {
            case 'B':
                queue.push_front (new ElemS(++cnt));
                itr = queue.begin();
                break;
            case 'E':
                queue.push_back (new ElemS(++cnt));
                itr = queue.end();
                break;
            default:
                break;
            }
            break;

        case 'R' :
            switch (c2)
            {
            case 'E':
                node = queue.pop_back ();
                ACE_ASSERT (node == 0 || node->get_link()->is_free ());
                itr = queue.end ();
                break;
            case 'B':
                node = queue.pop_front ();
                ACE_ASSERT (node == 0 || node->get_link()->is_free ());
                itr = queue.begin();
                break;
            case 'V':
                node = queue.remove (*itr);
                ACE_ASSERT (node == 0 || node->get_link()->is_free ());
                itr = queue.begin();
                break;
            default:
                break;
            }
            ACE_DEBUG ((LM_DEBUG, "Deleting node=%@\n", node));
            delete node;
            break;

        case 'P' :
            dump (queue, itr);
            break;
       case 'S' :
            {
               size_t pos = atoi(cmd.c_str() + 1) -1;
               if (pos > queue.size ())
               {
                   pos = queue.size ();
               }

               itr = queue.begin();

               for ( size_t i=0; i < pos; ++i, ++itr)
               {
               }
            }    
            break;

       case 'L' :
            {
               size_t pos = atoi(cmd.c_str() + 1) ;
               ElemSList list2;
               for (size_t i=0; i < pos; ++i)
               {
                   list2.push_back (new ElemS(++cnt));
               }
               queue.splice (list2);
            }
            break;

        case 'E' : 
            flgExit = true;
            break;
        }
    }

    return 0;
}
int
testDoubleList()
{
    bool flgExit = false;

    int  cnt = 0;

    ElemDList list;
    ElemDList::iterator itr = list.begin();

   
    for ( ; !flgExit ; )
    {
        dump (list, itr);
        std::cout << "\nI[B|E|I] - Insert at Begin|End|Iterator"
                  << "\nR[B|E|I] - Remove at Begin|End|Iterator"
                  << "\nSNNNN   - set iterator to pos NNNN"
                  << "\nLNNNN   - splice with list NNNN"
                  << "\nP - print list"
                  << "\nE - Exit ==>" ;

        std::string cmd;
        getCmd (cmd);
        if (cmd.size () == 0)
        {
            continue;
        }


        char c1 = toupper (cmd[0]);
        char c2 = toupper (cmd[1]);
        ElemD * node = 0;


        switch ( c1 )
        {
        case 'I' :
            switch (c2)
            {
            case 'B':
                itr = list.push_front (new ElemD(++cnt));
                break;
            case 'E':
                itr = list.push_back (new ElemD(++cnt));
                break;
            case 'I':
            default:
                itr = list.insert (new ElemD(++cnt), itr);
                break;
            }
            break;

        case 'R' :
            switch (c2)
            {
            case 'E':
                node = list.pop_back ();
                ACE_ASSERT (node == 0 || node->get_link()->is_free ());
                itr = list.end ();
                break;
            case 'B':
                node = list.pop_front ();
                ACE_ASSERT (node == 0 || node->get_link()->is_free ());
                itr = list.begin();
                break;
            case 'I':
            default:
                node = itr.remove();
                ACE_ASSERT (node == 0 || node->get_link()->is_free ());
                break;
            }
            ACE_DEBUG ((LM_DEBUG, "Deleting node=%@\n", node));
            delete node;
            break;

        case 'P' :
            dump (list, itr);
            break;
       case 'S' :
            {
               size_t pos = atoi(cmd.c_str() + 1) -1;
               if (pos > list.size ())
               {
                   pos = list.size ();
               }

               itr = list.begin();

               for ( size_t i=0; i < pos; ++i, ++itr)
               {
               }
            }    
            break;
       case 'L' :
            {
               size_t pos = atoi(cmd.c_str() + 1);
               ElemDList list2;
               for (size_t i=0; i < pos; ++i)
               {
                   list2.push_back (new ElemD(++cnt));
               }
               list.splice (list2);
            }
            break;

        case 'E' : 
            flgExit = true;
            break;
        }
    }

    //list.clear ();
        
    return 0;
}
  
int
ACE_TMAIN (int argc, ACE_TCHAR *argv[])
{
    bool flgExit = false;

    for ( ; !flgExit ; )
    {
        std::cout << "\nS -test Single List"
                  << "\nD -test Double List"
                  << "\nQ -test Queue"
                  << "\nE - Exit ==>" ;

        std::string cmd;
        getCmd (cmd);
        if (cmd.size () == 0)
        {
            continue;
        }


        char c1 = toupper (cmd[0]);
        switch ( c1 )
        {
        case 'S' :
            testSingleList ();
            break;
        case 'Q' :
            testQueue ();
            break;
        case 'D' :
            testDoubleList ();
            break;
        case 'E' : 
            flgExit = true;
            break;
        }
    }

    return 0;
}



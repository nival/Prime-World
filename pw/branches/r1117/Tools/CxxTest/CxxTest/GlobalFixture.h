#ifndef __cxxtest__GlobalFixture_h__
#define __cxxtest__GlobalFixture_h__

#include "LinkedList.h"

namespace CxxTest 
{
    class GlobalFixture : public Link
    {
    public:
        virtual bool setUpWorld() { return true; }
        virtual bool tearDownWorld() { return true; }
        virtual bool setUp() { return true; }
        virtual bool tearDown() { return true; }
        
        GlobalFixture() {}
        ~GlobalFixture() {}
        
        //HACK: all lists going to CxxRunner
        //static GlobalFixture *firstGlobalFixture();
        //static GlobalFixture *lastGlobalFixture();
				GlobalFixture *nextGlobalFixture() { return (GlobalFixture *)next(); }
				GlobalFixture *prevGlobalFixture() { return (GlobalFixture *)prev(); }

    private:
				//HACK: all lists going to CxxRunner
        //static List _list;
    };
    
    //HACK: GlobalFixtureList declared here defined in CxxRunner
    class GlobalFixtureList : public List
    {
    public:
				GlobalFixture *firstGlobalFixture() { return (GlobalFixture *)head(); }
				GlobalFixture *lastGlobalFixture() { return (GlobalFixture *)tail(); }
    };
}

#endif // __cxxtest__GlobalFixture_h__


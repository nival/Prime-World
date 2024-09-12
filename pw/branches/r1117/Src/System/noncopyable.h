#ifndef _NONCOPYABLE_H_
#define _NONCOPYABLE_H_

/**
*	Class NonCopyable is a base class.  
*	Derive your own class from NonCopyable when you want to prohibit copy construction and copy assignment.
*/
class NonCopyable
{
protected:
	NonCopyable () {}
private:
	NonCopyable( const NonCopyable& );
	NonCopyable& operator = ( const NonCopyable& );
};

#endif	// _NONCOPYABLE_H_


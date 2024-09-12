#ifndef _REMINDER_H_
#define _REMINDER_H_

#ifndef _SHIPPING
# define Stringize( L )		  #L
# define MkString( M, L )         M(L)
# define $Line					    MkString( Stringize, __LINE__ )
# define REMINDER( L )      message(__FILE__ "(" $Line ") : REMINDER > "  L )
#else
# define REMINDER( L ) 
#endif

#endif 	// _REMINDER_H_


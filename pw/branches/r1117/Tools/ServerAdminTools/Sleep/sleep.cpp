#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

int main( int argc, char ** argv )
{
  if ( argc == 2 ) {
    double wait = atof( argv[1] );
    if ( wait > 0 ) {
      printf( "Sleeping %g second...\n", wait );
      Sleep( (int)( wait * 1000.0 ) );
      return 0;
    }
  }
  
  printf( "Usage: sleep.exe <time_in_seconds>\n" );
  return 1;
}

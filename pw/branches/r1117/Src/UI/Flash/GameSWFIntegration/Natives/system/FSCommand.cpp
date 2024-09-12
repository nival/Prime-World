#include "TamarinPCH.h"

#include "../../FlashMovie.h"

#include "FSCommand.h"

namespace avmplus
{

void FSCommandClass::_fscommand(AvmString command, AvmString args)
{
  flash::Movie* movie = ((flash::FlashMovieAvmCore*) core())->GetMovie();

  movie->OnFSCommand( command, args );
}

}
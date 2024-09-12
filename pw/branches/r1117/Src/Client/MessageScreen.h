#ifndef MESSAGESCREEN_H_INCLUDED
#define MESSAGESCREEN_H_INCLUDED

#include "DefaultScreenBase.h"
#include "MessageDialog.h"

namespace UI
{
  class MessageScreenLogic;
};

namespace NMainLoop
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MessageScreen : public NMainLoop::DefaultScreenBase
{
	NI_DECLARE_REFCOUNT_CLASS_1( MessageScreen, NMainLoop::DefaultScreenBase );

public:
	MessageScreen();

  void Configure( IMessageScreenCallback * _callback, const string & _screenId );
  void SetScreenTransparent( bool transp ) { screenTransparent = transp; }

	virtual bool Init( UI::User * uiUser );

	virtual bool IsTransparent() const { return screenTransparent; }
	virtual bool IsModal() const { return true; }

  IMessageScreenCallback * GetCallback() const { return callback ? callback : NULL; }

private:
  bool MsgOnEscapeKey();

  Strong<UI::MessageScreenLogic> logic;
  Strong<IMessageScreenCallback> callback;
  string screenId;
  bool screenTransparent;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //MESSAGESCREEN_H_INCLUDED

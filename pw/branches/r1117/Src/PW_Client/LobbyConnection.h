#ifndef LOBBYCONNECTION_H_35CC26E9_818D
#define LOBBYCONNECTION_H_35CC26E9_818D

/**************************************************************************
!!! Этот класс не имеет ничего общего с lobby-сервисом и lobby-клиентом !!!
!!! Это обманка                                                         !!!
!!! This class has nothing to do with lobby service and client          !!!
!!! This is a cheap fake                                                !!!
**************************************************************************/


_interface ICastle : public IBaseInterfaceST
{
  NI_DECLARE_CLASS_1( ICastle, IBaseInterfaceST )

  virtual void Update( float seconds ) = 0;
  virtual void StartRender() = 0;
  virtual void ReturnToCastle() = 0;
  virtual void QuitGame() = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Strong<ICastle> CreateCastleLink( int port, const char* castleCmdLine, HINSTANCE _instance, HWND _sessionWnd );
Strong<ICastle> CreateDummyCastleLink();

#endif //#define LOBBYCONNECTION_H_35CC26E9_818D
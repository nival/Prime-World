#ifndef ISOCIALCONNECTION_H_224E6AF9_413
#define ISOCIALCONNECTION_H_224E6AF9_413

namespace NGameX
{

_interface ISocialConnection : public IBaseInterfaceST
{
  virtual bool AddFriend( __int64 auid ) = 0;
  virtual bool CreateComplaint( __int64 toauid, int category, const nstl::wstring& text, const nstl::wstring& _logs, int kills, int deaths, int assists, 
                                       int points, int prime, int leave, int distance, int afks ) = 0;
  virtual bool ChoosePartyAgain(const nstl::vector<__int64>& auids, const unsigned __int64 sessionId, const unsigned __int64 timeLeft, const bool agreed) = 0;
  virtual bool SendTeam(__int64 auid, const nstl::vector<__int64>& team_auids)=0;
  virtual void Step() = 0;
  virtual void Share() = 0;
  virtual void Share( int _x, int _y, int _width, int _height ) = 0;

  virtual void OnProtectionError() = 0;

private:
    NI_DECLARE_CLASS_1( ISocialConnection, IBaseInterfaceST );
};

}

#endif //#define ISOCIALCONNECTION_H_224E6AF9_413

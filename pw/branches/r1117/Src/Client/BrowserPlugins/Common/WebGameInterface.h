
#ifndef __WEBGAMEINTERFACE_H_
#define __WEBGAMEINTERFACE_H_

#ifndef ITF_STRINGIZE
#define ITF_STRINGIZE(a)  #a
#endif //ITF_STRINGIZE
#define ITF_WGI_NAME GiveWebGameInterface
#define ITF_WGI_NAME_S ITF_STRINGIZE(GiveWebGameInterface)

class IWebGameInterface
{
public:
  virtual bool    Init(char const *cmdLine) = 0;                   //UTF-8 command line parameter from browser. cmdLine can be NULL. Method can fail. WE should start loginf data on this call.
  virtual LRESULT CallWindowProc(HWND, UINT, WPARAM, LPARAM) = 0;  //Windows procedure
  virtual bool    Start(HWND hwnd) = 0;                            //Means we should start rendering into this HWND now!!!
  virtual bool    Stop() = 0;                                      //Means we should stop rendering into this HWND now!!!
  virtual bool    Resize(HWND hwnd) = 0;                           //Means window was resized: happens of reload or actual resize
  virtual bool    SetWindow(HWND hwnd) = 0;                        //Means HWND was changed because browser said so. After return we should stop render to old hwnd and can render to new. if HWND is NULL we should pause sender until new SetWindow.
  virtual void    Release() {};                                    //Release interface
protected:
private:
};

#endif //__WEBGAMEINTERFACE_H_
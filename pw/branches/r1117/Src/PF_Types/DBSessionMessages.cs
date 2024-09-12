using libdb.DB;
using System.ComponentModel;

namespace PF_GameLogic.DBSessionMessages
{
  public class ClientHardwareErrorMessages
  {
    [Description( "Общее сообщение о несовместимости с железом" )]
    public TextRef errorMessage = new TextRef();

    [Description( "Причина 1: сообщение о нехватке памяти" )]
    public TextRef lowMemoryError = new TextRef();

    [Description( "Причина 2: неподдерживаются шейдеры 3.0" )]
    public TextRef shader3compatibilityError = new TextRef();
  }

  public class DXErrorMessages
  {
    [Description("Dialog title")]
    public TextRef title = new TextRef();

    [Description("Общее сообщение об ошибке DX (D3DERR_INVALIDCALL)")]
    public TextRef errorMessage = new TextRef();

    [Description("сообщение о нехватке памяти (E_OUTOFMEMORY)")]
    public TextRef lowMemoryMessage = new TextRef();

    [Description("сообщение о нехватке видеопамяти (D3DERR_OUTOFVIDEOMEMORY)")]
    public TextRef lowVidMemMessage = new TextRef();
  }

  public class SessionMessages : DBResource
  {
    [Description( "Сообщения о несовместимости с железом" )]
    public ClientHardwareErrorMessages clientHardwareErrorMessages;

    [Description("Сообщения о проблемах графического движка")]
    public DXErrorMessages dxErrorMessages;

  }
}

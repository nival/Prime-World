using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ServiceModel;

namespace Zzima
{
    [ServiceContract(SessionMode = SessionMode.Allowed)]
    public interface IFromClientToServerMessages
    {
      [OperationContract(IsOneWay = true)]
      void ReportProgress(int percent);
    }

    [ServiceContract( SessionMode = SessionMode.Allowed )]
    public interface IFromServerToClientMessages
    {
      [OperationContract( IsOneWay = true )]
      void NotifyNeedToCancel( bool sentFlag );
    }
}

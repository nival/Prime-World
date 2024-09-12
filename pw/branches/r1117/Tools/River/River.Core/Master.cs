using System;

namespace River.Core
{
  public delegate void SetBotIDCallback( long id );

  public interface IMaster
	{
		long Connect( IBot bot, SetBotIDCallback SetID );
    void Disconnect(long botId);
    void ExecuteSuite(string filename, string tag, string suite, Guid suiteID, DateTime? timestart, DateTime? timestop);
    void HaltSuite( Guid suiteID );
    void HaltSuite(string tag);
    void HaltAllSuites();
    string[] SuitesInfo();

    void Ping();
	}
}

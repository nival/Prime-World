using System;
using System.Collections.Generic;
using BusinessLogic.DBManagement;
using BusinessLogic.Queuing;

namespace BusinessLogic.Game
{
  public class SessionWriter : ISessionWriter
  {
    private IDBManagementStorage storage;

    public SessionWriter()
    {
      this.storage = new DBManagementStorage(new TaskExecutor { Name = "SessionWriter" });
    }

    public SessionWriter(IDBManagementStorage dbManagementStorage)
    {
      if (dbManagementStorage == null) throw new ArgumentNullException("dbManagementStorage");
      this.storage = dbManagementStorage;
    }

    public bool IsRunning
    {
      get { return storage.IsRunning; }
    }

    public void MMakingCancelled(MMakingPlayerInfo mmplayer, DateTime timestamp)
    {
      storage.WriteMMakingCancelled(mmplayer, timestamp);
    }

    public void MMakingSession(ulong persistentId, int status, int manoeuvresFaction, int basket, string map, DateTime timestamp, IEnumerable<MMakingPlayerInfo> mmplayers)
    {
      storage.WriteMMakingSession(persistentId, status, manoeuvresFaction, basket, map, timestamp, mmplayers);
    }

    public void SessionStart(long persistentId, string map, string server, string serveraddress, string cluster, int sessionType, DateTime timestamp, IEnumerable<SessionStartPlayerInfo> players)
    {
      storage.WriteSessionStart(persistentId, map, server, serveraddress, cluster, sessionType, timestamp, players);
    }

    public void SessionResult(long persistentId, int result, int sideWon, int surrendervote, DateTime timestamp, IEnumerable<SessionResultPlayerInfo> players)
    {
      storage.WriteSessionResult(persistentId, result, sideWon, surrendervote, timestamp, players);
    }

    public void SessionRelayInfo(long persistentId, long playerid, string relayAddress)
    {
      storage.WriteSessionRelayInfo(persistentId, playerid, relayAddress);
    }

    private bool disposed;

    public void Dispose()
    {
      Dispose(true);
      GC.SuppressFinalize(this);
    }

    ~SessionWriter()
    {
      Dispose(false);
    }

    private void Dispose(bool disposing)
    {
      if (!disposed)
      {
        if (disposing)
        {
          storage.Dispose();
        }
        disposed = true;
      }
    }
  }
}
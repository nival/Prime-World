using System;
using System.Collections.Generic;
using DAL;
using DAL.Entities;
using DAL.Repositories;
using System.Linq;
using log4net;

namespace GameDataImporter
{
  public interface IDatabaseInteraction
  {
    void Update<TEntity>(IEnumerable<TEntity> data, IRepository<TEntity> repo) 
      where TEntity : DictionaryEntity;

    bool CheckVersion(int version);
  }
  
  public class DatabaseInteraction : IDatabaseInteraction
  {
    private static ILog _log = LogManager.GetLogger(typeof (DatabaseInteraction));

    public DatabaseInteraction(string connectionString)
    {
      var context = new DALContext(connectionString);
      if (!NHibernateHelper.Init(context))
      {
        _log.Warn("NHibernate already initialized.");
      }
    }

    public void Update<TEntity>(IEnumerable<TEntity> data, IRepository<TEntity> repo)
      where TEntity : DictionaryEntity
    {
      List<TEntity> dbitems = repo.GetAll().ToList();
      foreach (TEntity item in data)
      {
        string itemInfo = String.Format("{0} id = {1}, name = \"{2}\"", item.GetType().Name, item.Id, item.Name);

        var dbitem = dbitems.Find(i => i.Id == item.Id);
        if (dbitem == null)
        {
          _log.Debug("Importing object : " + itemInfo);
          repo.Add(item);
        }
        else
        {
          dbitems.Remove(dbitem);

          if (item != dbitem)
          {
            _log.Debug("Updating object : " + itemInfo);
            repo.Update(item);
          }
        }
      }

      if (dbitems.Exists(e => !e.Deleted))
      {
        foreach (var dbitem in dbitems.Where(e => !e.Deleted))
        {
          _log.DebugFormat("Deleting object : {0} id = {1}, name = \"{2}\"", dbitem.GetType().Name, dbitem.Id, dbitem.Name);
          dbitem.Deleted = true;
          repo.Update(dbitem);
        }
      }
    }

    public bool CheckVersion(int version)
    {
      int dbVersion = NHibernateHelper.DBVersion;
      if (version != dbVersion)
        _log.ErrorFormat("Wrong version of management database: expected = {0}, found = {1}", version, dbVersion);

      return version == dbVersion;
    }
  }
}
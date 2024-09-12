using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using log4net;
using NHibernate;
using NHibernate.Cfg;
using DAL.Entities;
using NHibernate.Tool.hbm2ddl;

namespace DAL
{
  public class NHibernateHelper
  {
    private static ILog _log = LogManager.GetLogger(typeof (NHibernateHelper));

    private static volatile ISessionFactory _sessionFactory;
    private static DALContext _context;
    private static object locker = new object();

    internal static ISessionFactory SessionFactory
    {
      get
      {
        if (_sessionFactory == null)
          lock (locker)
          {
            if (_context == null)
              throw new DALException("DAL context not implemented.");

            if (_sessionFactory == null)
            {
              var configuration = new Configuration();
              configuration.Configure();
              configuration.AddAssembly(typeof (NHibernateHelper).Assembly);
              configuration.SetProperty("connection.connection_string", _context.ConnectionString);
              _sessionFactory = configuration.BuildSessionFactory();
            }
          }

        return _sessionFactory;
      }
    }

    public static bool Init(DALContext context)
    {
      if (context == null) throw new ArgumentNullException("context");
      if (_context != null) return false;

      lock(locker)
      {
        _context = context;
        return true;
      }
    }

    public static ISession OpenSession()
    {
      return SessionFactory.OpenSession();
    }

    public static void DBMigrate()
    {
      var cfg = new Configuration();
      cfg.Configure();
      cfg.AddAssembly(typeof(NHibernateHelper).Assembly);
      new SchemaExport(cfg).Execute(false, true, false);
    }

    public static int DBVersion
    {
      get
      {
        try
        {
          return OpenSession().GetNamedQuery("DBVersion").UniqueResult<int>();
        }
        catch (Exception ex)
        {
          _log.Error("Failed to select dbversion()", ex);
          return -1;
        }
      }
    }
  }
}

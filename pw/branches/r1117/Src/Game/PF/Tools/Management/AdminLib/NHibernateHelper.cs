using System;
using NHibernate;
using NHibernate.Cfg;
using NHibernate.Tool.hbm2ddl;

namespace AdminLib
{
  public class NHibernateHelper
  {
    private static volatile ISessionFactory _sessionFactory;
    private static DBContext _context;
    private static readonly object locker = new object();

    private static ISessionFactory SessionFactory
    {
      get
      {
        if (_sessionFactory == null)
          lock (locker)
          {
            if (_context == null)
              throw new Exception("Database context not implemented.");

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

    public static bool Init(DBContext context)
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
      get { return OpenSession().GetNamedQuery("DBVersion").UniqueResult<int>(); }
    }
  }
}

using System;
using System.Collections.Generic;
using log4net;
using NHibernate;
using NHibernate.Criterion;

namespace DAL.Repositories
{
  public interface IRepository<T> : IDisposable
  {
    void Add(T obj);
    void Update(T obj);
    void Remove(T obj);
    T GetById(int id);
    T GetById(long id);
    T CheckAndGetById(int id);
    T CheckAndGetById(long id);
    IEnumerable<T> GetAll();
  }
  
  public class Repository<T> : IRepository<T>
    where T : class
  {
    private static ILog _log = LogManager.GetLogger(typeof(Repository<T>).Assembly, "Repository<T>");

    private ISession currentSession;

    protected ISession Session
    {
      get
      {
        if (currentSession == null)
          currentSession = NHibernateHelper.OpenSession();
        return currentSession;
      }
    }

    protected ICriterion EqOrNull(string property, object value)
    {
      if (value == null)
        return Restrictions.IsNull(property);
      return Restrictions.Eq(property, value);
    }

    public virtual void Add(T obj)
    {
      using (ITransaction tran = Session.BeginTransaction())
      {
        Session.Save(obj);
        tran.Commit();
      }
      _log.Debug("Added new object " + obj);
    }

    public void Update(T obj)
    {
      using (ITransaction tran = Session.BeginTransaction())
      {
        Session.Merge(obj);
        tran.Commit();
      }
      _log.Debug("Updated object " + obj);
    }

    public void Remove(T obj)
    {
      using (ITransaction tran = Session.BeginTransaction())
      {
        Session.Delete(obj);
        tran.Commit();
      }
      _log.Debug("Removed object " + obj);
    }

    public virtual T GetById(int id)
    {
      return Session.Get<T>(id);
    }

    public virtual T GetById(long id)
    {
      return Session.Get<T>(id);
    }

    public T CheckAndGetById(int id)
    {
      var result = GetById(id);
      if (result == null)
        throw new DALException(String.Format("Object {0} (id={1}) was not found", typeof(T).Name, id));
      return result;
    }

    public T CheckAndGetById(long id)
    {
      var result = GetById(id);
      if (result == null)
        throw new DALException(String.Format("Object {0} (id={1}) was not found", typeof(T).Name, id));
      return result;
    }

    public IEnumerable<T> GetAll()
    {
      return Session.CreateCriteria<T>().List<T>();
    }

    public void Dispose()
    {
      Session.Close();
    }
  }
}

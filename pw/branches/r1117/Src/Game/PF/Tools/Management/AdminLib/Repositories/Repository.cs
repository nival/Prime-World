using System;
using System.Collections.Generic;
using NHibernate;
using NHibernate.Criterion;

namespace AdminLib.Repositories
{
  public interface IRepository<T> : IDisposable
  {
    void Add(T obj);
    void Update(T obj);
    void Remove(T obj);
    T GetById(int id);
    int GetTotalCount();
    IEnumerable<T> GetAll();
  }
  
  public abstract class Repository<T> : IRepository<T>
    where T : class
  {
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

    public void Add(T obj)
    {
      using (ITransaction tran = Session.BeginTransaction())
      {
        Session.Save(obj);
        tran.Commit();
      }
    }

    public void Update(T obj)
    {
      using (ITransaction tran = Session.BeginTransaction())
      {
        Session.Merge(obj);
        tran.Commit();
      }
    }

    public void Remove(T obj)
    {
      using (ITransaction tran = Session.BeginTransaction())
      {
        Session.Delete(obj);
        tran.Commit();
      }
    }

    public T GetById(int id)
    {
      return Session.Get<T>(id);
    }

    public IEnumerable<T> GetAll()
    {
      return Session.CreateCriteria<T>().List<T>();
    }

    public int GetTotalCount()
    {
      return Session.CreateCriteria<T>()
        .SetProjection(Projections.Count(Projections.Id()))
        .UniqueResult<int>();
    }

    public void Dispose()
    {
      Session.Close();
    }
  }
}

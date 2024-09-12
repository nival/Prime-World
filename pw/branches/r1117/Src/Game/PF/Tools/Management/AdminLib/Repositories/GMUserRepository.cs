using System;
using AdminLib.Entities;
using NHibernate.Criterion;

namespace AdminLib.Repositories
{
  public interface IGMUserRepository : IRepository<GMUser>
  {
    GMUser GetByUserName(string username);
    int GetSuperUserQuantity();
//    int GetNumberOfUsers();
  }

  public class GMUserRepository : Repository<GMUser>, IGMUserRepository
  {
    public GMUser GetByUserName(string username)
    {
      return Session.CreateCriteria<GMUser>()
        .Add(Restrictions.Eq("UserName", username))
        .UniqueResult<GMUser>();
    }
    public int GetSuperUserQuantity()
    {
      return (int)Session.CreateCriteria<GMUser>()
        .Add( Restrictions.Eq( "Superuser", true ) )
        .SetProjection( Projections.Count( "Superuser" ) ).UniqueResult();
    }

/*    public int GetNumberOfUsers()
    {
      return Session.CreateCriteria<GMUser>()
        //.SetProjection(Projections.Count("UserId"))
        .SetProjection(Projections.Count(Projections.Id()))
        .UniqueResult<int>();
    }*/
  }
}
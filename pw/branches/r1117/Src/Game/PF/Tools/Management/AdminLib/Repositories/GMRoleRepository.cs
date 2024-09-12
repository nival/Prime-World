using System;
using System.Linq;
using AdminLib.Entities;
using NHibernate.Criterion;

namespace AdminLib.Repositories
{
  public interface IGMRoleRepository : IRepository<GMRole>
  {
    GMRole GetByRoleName(string role);
    bool AddPermission(GMRole role, int permissionid);
    bool RemovePermission(GMRole role, int permissionid);
    bool AddUser(GMRole role, int userid);
    bool RemoveUser(GMRole role, int userid);
    bool CheckNoUsersReferThatRole( GMRole role );
  }

  public class GMRoleRepository : Repository<GMRole>, IGMRoleRepository
  {
    public GMRole GetByRoleName(string role)
    {
      return Session.CreateCriteria<GMRole>()
        .Add(Restrictions.Eq("RoleName", role))
        .UniqueResult<GMRole>();
    }
    public bool CheckNoUsersReferThatRole( GMRole role )
    {
      int quant = (int)Session.CreateCriteria<GMUsersInRoles>()
        .Add( Restrictions.Eq( "RoleId", role.RoleId ) )
        .SetProjection( Projections.Count( "RoleId" ) ).UniqueResult();
      return quant == 0;
    }

    public bool AddPermission(GMRole role, int permissionid)
    {
      if (role.Permissions.Any(p => p.PermissionId == permissionid))
        return true;
      
      var permission = Session.Get<GMPermission>(permissionid);
      if (permission == null)
        return false;

      using (var tran = Session.BeginTransaction())
      {
        role.Permissions.Add(permission);
        Session.Update(role);
        tran.Commit();
      }
      return true;
    }

    public bool RemovePermission(GMRole role, int permissionid)
    {
      if (!role.Permissions.Any(p => p.PermissionId == permissionid))
        return true;

      var permissiontoremove = role.Permissions.First(p => p.PermissionId == permissionid); 
      if (permissiontoremove == null)
        return false;

      using (var tran = Session.BeginTransaction())
      {
        bool removing = role.Permissions.Remove(permissiontoremove);
        Session.SaveOrUpdate(role);
        tran.Commit();
        return removing;
      }
    }

    public bool AddUser(GMRole role, int userid)
    {
      if (role.Users.Any(p => p.UserId == userid))
        return true;

      var user = Session.Get<GMUser>(userid);
      if (user == null)
        return false;

      using (var tran = Session.BeginTransaction())
      {
        role.Users.Add(user);
        Session.Update(role);
        tran.Commit();
      }
      return true;
    }

    public bool RemoveUser(GMRole role, int userid)
    {
      if (!role.Users.Any(p => p.UserId == userid))
        return true;

      var usertoremove = role.Users.First(p => p.UserId == userid);
      if (usertoremove == null)
        return false;

      using (var tran = Session.BeginTransaction())
      {
        bool removing = role.Users.Remove(usertoremove);
        Session.SaveOrUpdate(role);
        tran.Commit();
        return removing;
      }
    }
  }

}
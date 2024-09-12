using System;
using System.Collections.Generic;
using System.Linq;
using AdminLib.Entities;

namespace AdminLib.Repositories
{
  public interface IGMPermissionRepository : IRepository<GMPermission>
  {
    void FillPermissions(IEnumerable<string> permissions);
  }

  public class GMPermissionRepository : Repository<GMPermission>, IGMPermissionRepository
  {
    public void FillPermissions(IEnumerable<string> permissions)
    {
      IEnumerable<GMPermission> gmpermissions = GetAll();
      IEnumerable<GMRole> gmroles = Session.CreateCriteria<GMRole>().List<GMRole>();
      
      // remove unnecessary permissions
      foreach (GMPermission gmPermission in gmpermissions)
      {
        if (!permissions.Any(p => String.Compare(p, gmPermission.PermissionName, true) == 0))
        {
          foreach (var role in gmroles.Where(r => r.Permissions.Contains(gmPermission)))
          {
            role.Permissions.Remove(gmPermission);
          }
          Remove(gmPermission);
        }
      }

      // add new permissions
      gmpermissions = GetAll();
      foreach (string permission in permissions)
      {
        if (!gmpermissions.Any(p => p.PermissionName.ToLower() == permission.ToLower()))
        {
          Add(new GMPermission {PermissionName = permission});
        }
      }
    }
  }
}

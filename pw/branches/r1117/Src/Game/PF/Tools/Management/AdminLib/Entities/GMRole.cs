using System.Collections.Generic;

namespace AdminLib.Entities
{
  public class GMRole
  {
    public virtual int RoleId { get; set; }
    public virtual string RoleName { get; set; }
    public virtual string Description { get; set; }
    public virtual string Locale { get; set; }
    public virtual string Muid { get; set; }
    public virtual IList<GMUser> Users { get; set; }
    public virtual IList<GMPermission> Permissions { get; set; }
  }
}
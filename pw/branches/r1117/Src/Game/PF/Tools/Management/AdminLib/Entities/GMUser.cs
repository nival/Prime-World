using System.Collections.Generic;

namespace AdminLib.Entities
{
  /// <summary>
  /// User of game management tools.
  /// </summary>
  public class GMUser
  {
    public virtual int UserId { get; set; }
    public virtual string UserName { get; set; }
    public virtual string FullName { get; set; }
    public virtual string Email { get; set; }
    public virtual bool Superuser { get; set; }
    public virtual IList<GMRole> Roles { get; set; }
  }
}
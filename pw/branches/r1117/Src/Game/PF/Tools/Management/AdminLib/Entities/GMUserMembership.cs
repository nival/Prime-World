using System;

namespace AdminLib.Entities
{
  public class GMUserMembership
  {
    public virtual GMUser GMUser { get; set; }
    public virtual string Password { get; set; }
    public virtual DateTime CreateDate { get; set; }
    public virtual DateTime LastLoginDate { get; set; }
  }
}
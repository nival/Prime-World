namespace AdminLib.Entities
{
  public class GMUsersInRoles
  {
    public virtual int Id { get; set; }
    public virtual int RoleId { get; set; }
    public virtual int UserId { get; set; }
  }
}
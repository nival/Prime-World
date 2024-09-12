using System;

namespace DAL.Entities
{
  /*
  public class GmEditPlayer : DictionaryEntity
  {
    public virtual long player { get; set; }
    public virtual string gmlogin { get; set; }
    public virtual string field { get; set; }
    public virtual string oldvalue { get; set; }
    public virtual string newvalue { get; set; }
    public virtual DateTime operationdate { get; set; }
  }
  public class GmLockCharacter : DictionaryEntity
  {
    public virtual long player { get; set; }
    public virtual string gmlogin { get; set; }
    public virtual int character { get; set; }
    public virtual DateTime operationdate { get; set; }
  }
  public class GmUnlockCharacter : DictionaryEntity
  {
    public virtual long player { get; set; }
    public virtual string gmlogin { get; set; }
    public virtual int character { get; set; }
    public virtual DateTime operationdate { get; set; }
  }
  public class GmAddTalent : DictionaryEntity
  {
    public virtual long player { get; set; }
    public virtual string gmlogin { get; set; }
    public virtual int talent { get; set; }
    public virtual DateTime operationdate { get; set; }
  }
  public class GmDeleteTalent : DictionaryEntity
  {
    public virtual long player { get; set; }
    public virtual string gmlogin { get; set; }
    public virtual int talent { get; set; }
    public virtual DateTime operationdate { get; set; }
  }*/

  public class LogInOut : DictionaryEntity
  {
    public virtual long player { get; set; }
    public virtual string server { get; set; }
    public virtual string cluster { get; set; }
    public virtual DateTime startTime { get; set; }
    public virtual DateTime endTime { get; set; }
  }
}

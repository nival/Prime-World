namespace Unity.Components.SoundsManager
{
  public enum SourceType
  {
    NotSetted = 0,
    Music,
    //Music subchannel for plays 2nd music channel 
    //clip while first one is ignored
    MusicAvoidingFade,
    UI,
    Voice
  }
}

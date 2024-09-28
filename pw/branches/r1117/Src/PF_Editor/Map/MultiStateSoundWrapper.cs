using DBTypes;

namespace PF_Editor.Map
{
  public class MultiStateSoundWrapper
  {
    public DBFMODEventDesc N
    {
      get { return sound[0]; }
    }

    public DBFMODEventDesc A
    {
      get { return sound[1]; }
    }

    public DBFMODEventDesc B
    {
      get { return sound[2]; }
    }

    private DBFMODEventDesc[] sound = new DBFMODEventDesc[3];

    public MultiStateSoundWrapper(MultiStateObject _mso)
    {
      //в MultiStateSoundWrapper нет проверок, т.к. все проверки были сделаны в ControllableVisualObject.IsMultiStateSoundObject в вызывающем коде, враппер используется только в нем
      for( int i = 0; i < _mso.sceneObjects.Count; ++i )
      {
        var component = _mso.sceneObjects[i].Get().attached[0].component.Get() as DBSoundSceneComponent;

        if(component != null)
        {
          sound[i] = component.desc;
        }
      }
    }
  }
}

using System.Collections.Generic;    
using libdb.DB;

namespace UI.DBPreferences
{
  public enum ControlVarType
  {
    CheckBox,
    ComboBoxInterval,
    Slider,
    DisplayModeComboBox
  }

  public class ComboBoxDescription
  {
    public float value = 0;
    public TextRef userName;
  }

  [IndexField("varId")]
  public class PrefVariable
  {
    public string varId;
    public string commandName;
    public ControlVarType controlVarType = ControlVarType.CheckBox; 
    public List<ComboBoxDescription> comboBoxDescription = new List<ComboBoxDescription>();
    public string applyCommandName;
    public string enabledFromOtherVarId;
  }

  [IndexField("varId")]
  public class NameValue
  {
    public string varId;
    public int value = -1000;
  }

  [IndexField("presetName")]
  public class PreferencesPreset
  {
    public string presetName;
    public List<NameValue> data = new List<NameValue>();
  }


  public class Preferences: DBResource
  {
    public List< PrefVariable > variables = new List< PrefVariable >();
    public List<PreferencesPreset> presets = new List<PreferencesPreset>();
  }

}
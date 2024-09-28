#include "stdafx.h"
#include "PreferencesProcessor.h"
#include "DBPreferences.h"
#include "Render/renderer.h"
#include "FlashContainer2.h"
#include "System/nalgoritm.h"
#include "System/niterator.h"
#include "libdb/DbResourceCache.h"

namespace
{
  struct DisableAssertionLoadingFilesGuard : NonCopyable
  {
    DisableAssertionLoadingFilesGuard()
      : initial(NDb::GetDbResourceCache().EnableAssertionLoadingFiles(false))
    {
    }
    ~DisableAssertionLoadingFilesGuard()
    {
      NDb::GetDbResourceCache().EnableAssertionLoadingFiles(initial);
    }
  private:
    const bool initial;
  };
}

namespace UI
{
using NGlobal::VariantValue;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace
{
const VariantValue GetVar( const string &name )
{
  return NGlobal::GetVar( name );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T>
void SetVar( const string &name, const T &val )
{
  NGlobal::SetVar( name, val, STORAGE_DONT_CARE );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class T, class Compare>
int findIntervalNum( const vector<T> &arr, T val, Compare cmp, const string &debugVarName )
{
  int i = 0;

  while( i < arr.size() && !cmp(val, arr[i]) ) 
    ++i;

  if( i <= 0 )
  {
    DebugTrace( "Pref value too low. Please, check config variable '%s'", debugVarName.c_str() );
    return 0;
  }

  if( i == arr.size() && arr.back() != val )
   DebugTrace( "Pref value too high. Please, check config variable '%s'",  debugVarName.c_str() );

  return i - 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class PrefVarBase
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PrefVarBase: public IPrefVar
{
  NI_DECLARE_REFCOUNT_CLASS_1( PrefVarBase, BaseObjectST );
  
public:
  PrefVarBase( FlashInterface *pFlash, const string &varId ): 
    pFlash(pFlash), varId(varId)
  {}

protected:
  void SetControlValue( int value, bool isEnabled )
  {
    pFlash->CallMethod( "SetControlValue", varId, value, isEnabled );
  }

private:
  FlashInterface * const pFlash;
  const string varId;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class StdVarBase
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class StdVarBase: public PrefVarBase
{
public:
  StdVarBase( FlashInterface *pFlash, const string &varId, const string &varName ): 
    PrefVarBase(pFlash, varId), varName(varName), isEnabled(true)
  {}
  
  virtual bool GetEnabledStateForDependents() const 
  { 
    return GetVar(varName).Get<bool>();   
  }
    
  virtual void UpdateCurValue( int newVal )
  { 
    SetVar( varName, convertValueFromUI(newVal) );
    SetControlValue( newVal, isEnabled );
  }
  
  virtual void UpdateEnabledState( bool isEnabled )
  {      
    this->isEnabled = isEnabled;
    SetControlValue( GetCurrValue(), isEnabled );
  }
  
  virtual int GetCurrValue() const
  {
    return convertValueToUI( GetVar(varName) );
  }
  
protected:
  const string &GetVarNameForDebug() const { return varName; }
 
private:
  virtual int convertValueToUI( const VariantValue &val ) const = 0;
  virtual const VariantValue convertValueFromUI( int val ) const = 0;
 
private:
  const string varName;
  bool isEnabled;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class CheckBoxControl
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CheckBoxControl: public StdVarBase
{
public:
  CheckBoxControl( FlashInterface *pFlash, const string &varId, const NDb::PrefVariable &desc ):  
    StdVarBase( pFlash, varId, desc.commandName )
  {
    pFlash->CallMethod( "AddCheckBoxControl", varId );
  }
  
private:
  virtual int convertValueToUI( const VariantValue &val ) const
  {
    return val.GetInt64();
  }
  
  virtual const VariantValue convertValueFromUI( int val ) const
  {
    return VariantValue(val);
  }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class ComboBoxControl
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ComboBoxControl: public StdVarBase
{
public:
  ComboBoxControl( FlashInterface *pFlash, const string &varId, const NDb::PrefVariable &desc ):  
      StdVarBase( pFlash, varId, desc.commandName )
  {
    vector<wstring> labels;
  
    for( int i = 0; i < desc.comboBoxDescription.size(); ++i )
    {
      valueIntervals.push_back( desc.comboBoxDescription[i].value );
      labels.push_back( desc.comboBoxDescription[i].userName.GetText() );
    }
  
    pFlash->CallMethod( "AddComboBoxControl", varId, labels );
  }

private:
  virtual int convertValueToUI( const VariantValue &val ) const
  {
    NI_ASSERT( valueIntervals.size() >= 2, "Size is too small" );      

    if( valueIntervals[0] < valueIntervals[1])
      return findIntervalNum( valueIntervals, val.GetFloat(), less(), GetVarNameForDebug() );
    else
      return findIntervalNum( valueIntervals, val.GetFloat(), greater(), GetVarNameForDebug() );
  }

  virtual const VariantValue convertValueFromUI( int val ) const
  {
    NI_ASSERT( val >= 0 && val < valueIntervals.size(), "Incorrect pref value" );   
    return VariantValue(valueIntervals[val]);
  }

private:
  vector<float> valueIntervals;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class SliderControl
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SliderControl: public StdVarBase
{
public:
  SliderControl( FlashInterface *pFlash, const string &varId, const NDb::PrefVariable &desc ):  
    StdVarBase( pFlash, varId, desc.commandName )
  {
    pFlash->CallMethod( "AddSliderControl", varId, valuesCount );
  }

private:
  virtual int convertValueToUI( const VariantValue &val ) const
  {
    //Минимальное значение, представимое на интервале, используем для округления
    const float discrValue = 1.0f / (valuesCount - 1);
    return static_cast<int>( val.GetFloat() * (valuesCount - 1) + discrValue / 2 );
  }

  virtual const VariantValue convertValueFromUI( int val ) const
  {
    return VariantValue( static_cast<float>(val) / (valuesCount - 1) );
  }
  
  static const int valuesCount = 100;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class DisplayModeComboBoxControl
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DisplayModeComboBoxControl: public PrefVarBase
{
private:
  struct DisplayMode
  {
    unsigned int width;
    unsigned int height;
        
    wstring ToString() const
    {
      return NStr::StrFmtW( L"%u x %u", width, height );
    }
  };
  
  struct DisplayModeCmp
  {
    bool operator()( const DisplayMode &dm1, const DisplayMode &dm2 ) const
    {
      return (dm1.width > dm2.width) || (!(dm2.width > dm1.width) && dm1.height > dm2.height);
    }
  };

  typedef set<DisplayMode, DisplayModeCmp> DisplayModes;
  typedef vector<wstring>  DisplayModesDesc;

public:
  DisplayModeComboBoxControl( FlashInterface *pFlash, const string &varId, const NDb::PrefVariable &desc ):  
    PrefVarBase( pFlash, varId ), isEnabled(true)
  {  
    const int count = Render::GetRenderer()->GetModesCount();

    for( int i = 0; i < count; ++i )
    {
      DisplayMode dm;
      unsigned int refreshRate;
     
      Render::GetRenderer()->GetMode( i, dm.width, dm.height, refreshRate );
      
      if( !Render::GetRenderer()->NeedToFilterResolutionFromUser(dm.width, dm.height) )
        displayModes.insert(dm);
    }
        
    displayModes.insert( GetCurDisplayMode() );
    
    DisplayModesDesc displayModesDesc;
    
    for( DisplayModes::const_iterator it = displayModes.begin(); it != displayModes.end(); ++it )
      displayModesDesc.push_back( it->ToString() );
    
    pFlash->CallMethod( "AddComboBoxControl", varId, displayModesDesc );
  }

private:
  virtual bool GetEnabledStateForDependents() const 
  { 
    return true;   
  }

  virtual void UpdateCurValue( int newVal )
  { 
    if( newVal < 0 || newVal >= displayModes.size() )
    {
      NI_ALWAYS_ASSERT("Incorrect pref value" );  
      return;    
    }
    
    DisplayModes::const_iterator it = displayModes.begin();
    
    advance( it, newVal );
    SetCurDisplayMode( *it );
		SetControlValue(newVal, isEnabled);
  }

  virtual void UpdateEnabledState( bool isEnabled )
  {      
    this->isEnabled = isEnabled;
    SetControlValue( GetCurrValue(), isEnabled );
  }
  
  virtual int GetCurrValue() const
  {
     return FindDisplayModeIndex( GetCurDisplayMode() );
  }
  
  private:
    DisplayMode GetCurDisplayMode() const
    {
      DisplayMode dm;
      Render::GetResolution( dm.width, dm.height );

      return dm;
    }
    
    void SetCurDisplayMode( const DisplayMode &dm )
    {
      Render::SetResolution( dm.width, dm.height );
    }
    
    int FindDisplayModeIndex( const DisplayMode &dm ) const
    {
      DisplayModes::const_iterator it = displayModes.find( dm );

      if( it == displayModes.end() )
      {
        NI_ALWAYS_ASSERT( NStr::StrFmt("Display mode %d x %d is not valid", dm.width, dm.height) );
        return 0;
      }

      return distance( displayModes.begin(), it );   
    }
  
private:
  DisplayModes displayModes;
  bool isEnabled;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Strong<IPrefVar> createControl( FlashInterface *pFlash, const string &varId, const NDb::PrefVariable &desc )
{
  switch( desc.controlVarType )
  {
    case NDb::CONTROLVARTYPE_CHECKBOX: return new CheckBoxControl( pFlash, varId, desc );
    case NDb::CONTROLVARTYPE_COMBOBOXINTERVAL: return new ComboBoxControl( pFlash, varId, desc );
    case NDb::CONTROLVARTYPE_SLIDER: return new SliderControl( pFlash, varId, desc );
    case NDb::CONTROLVARTYPE_DISPLAYMODECOMBOBOX: return new DisplayModeComboBoxControl( pFlash, varId, desc ); 
    
    default:
      NI_ALWAYS_ASSERT( NStr::StrFmt("Unknown NDb::ControlVarType %d", desc.controlVarType) );
      return NULL;
  }
}

} //anonymous namespace
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const char szUpdateFlashCommand[] = "PreferenceComponentSetValue";
static const char szApplyFlashCommand[] = "PreferenceComponentsApply";
static const char szCancelFlashCommand[] = "PreferenceComponentsCancel";
static const char szLoadPresetFlashCommand[] = "PreferenceComponentsLoadPreset";
static const char szShortcutRebindFlashCommand[] = "PreferenceShortcutRebind";
static const char szShortcutsApplyFlashCommand[] = "PreferenceShortcutsApply";

PreferencesProcessor::PreferencesProcessor( UI::FlashContainer2 * flashWnd, const char* className ):
  FlashInterface(flashWnd, className), pPresets(0)
{
  flashWnd->AddFSListner( szUpdateFlashCommand, this );
  flashWnd->AddFSListner( szApplyFlashCommand, this );
  flashWnd->AddFSListner( szCancelFlashCommand, this );
  flashWnd->AddFSListner( szLoadPresetFlashCommand, this );
  flashWnd->AddFSListner( szShortcutRebindFlashCommand, this );
  flashWnd->AddFSListner( szShortcutsApplyFlashCommand, this );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PreferencesProcessor::Init( const NDb::Preferences &desc )
{
  variables.clear();
  
  for( int i = 0; i < desc.variables.size(); ++i )
  {
    VarData val;

    val.pDesc = &desc.variables[i];
    val.pAbstract = createControl(this, val.pDesc->varId, desc.variables[i]);
    val.defaultValue = -1;
    
    variables.insert( Variables::value_type( val.pDesc->varId, val ) );  
  }
  
  for( Variables::const_iterator it = variables.begin(); it != variables.end(); ++it )
    it->second.pAbstract->UpdateEnabledState( CalcEnabledState(it->second.pDesc->enabledFromOtherVarId) );
    
  StoreAllValues();
  
  pPresets = &desc.presets;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PreferencesProcessor::StoreAllValues()
{
  for( Variables::const_iterator it = variables.begin(); it != variables.end(); ++it )
    it->second.defaultValue = it->second.pAbstract->GetCurrValue();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool PreferencesProcessor::CanBeCanceled( const VarData &var )
{
  //Настройки, которые применяются мгновенно, нельзя отменить по диздоку
  return !var.pDesc->applyCommandName.empty();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool PreferencesProcessor::NeedToApplyCommand( const VarData &var )
{
  return !var.pDesc->applyCommandName.empty() && 
         var.pAbstract->GetCurrValue() != var.defaultValue; 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PreferencesProcessor::RestoreAllValues()
{
  for( Variables::const_iterator it = variables.begin(); it != variables.end(); ++it )
  {
    if( CanBeCanceled(it->second) )  
      UpdateValue( it->second, it->second.defaultValue );         
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PreferencesProcessor::RestorePreset( const string &name )
{
  NI_ASSERT( pPresets != 0, "" );
  
  for( int i = 0; i < pPresets->size(); ++i )
    if( (*pPresets)[i].presetName == name )
    { 
      RestorePreset( (*pPresets)[i] );
      return;
    }
    
  NI_ALWAYS_ASSERT( NStr::StrFmt("Can't find preset name '%s'", name.c_str()) );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PreferencesProcessor::RestorePreset( int index )
{
  NI_ASSERT( pPresets != 0, "" );

  if( index < 0 || index >= pPresets->size() )
  {
    NI_ALWAYS_ASSERT( NStr::StrFmt("Can't find preset index %d", index) );
    return;
  }
  
  RestorePreset( (*pPresets)[index] );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PreferencesProcessor::RestorePreset( const NDb::PreferencesPreset &preset )
{
  DebugTrace( "RestorePreset: %s", preset.presetName.c_str() );

  for( int j = 0; j < preset.data.size(); ++j )
    UpdateValue( preset.data[j].varId, preset.data[j].value );   
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool PreferencesProcessor::CalcEnabledState( const string &varId ) const
{
  if( varId.empty() ) 
    return true;

  Variables::const_iterator it = variables.find( varId );
  
  if( it == variables.end() )
  {
    NI_ALWAYS_ASSERT( NStr::StrFmt("Can't find varName '%s'", varId.c_str()) )
    return true;
  }

  return it->second.pAbstract->GetEnabledStateForDependents();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PreferencesProcessor::UpdateEnabledState( const string &enabledFromVarId, bool isEnabled )
{
  for( Variables::const_iterator it = variables.begin(); it != variables.end(); ++it )
    if( it->second.pDesc->enabledFromOtherVarId == enabledFromVarId )
      it->second.pAbstract->UpdateEnabledState( isEnabled );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PreferencesProcessor::UpdateValue( const VarData &var, int value )
{
  if( value == var.pAbstract->GetCurrValue() )
    return;

  var.pAbstract->UpdateCurValue( value );
  UpdateEnabledState( var.pDesc->varId, var.pAbstract->GetEnabledStateForDependents() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PreferencesProcessor::UpdateValue( const string &varId, int value )
{
  Variables::const_iterator it = variables.find(varId);

  if( it == variables.end() )
  {
    NI_ALWAYS_ASSERT( NStr::StrFmt("Invalid varId %s", varId.c_str()) );
    return;
  }
  
  UpdateValue( it->second, value );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool PreferencesProcessor::NeedToApply() const
{
  for( Variables::const_iterator it = variables.begin(); it != variables.end(); ++it )
    if( NeedToApplyCommand(it->second) )
      return true;
      
  return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PreferencesProcessor::ApplyValuesOnly()
{
  for( Variables::const_iterator it = variables.begin(); it != variables.end(); ++it )
    if( it->second.pAbstract->GetCurrValue() != it->second.defaultValue )
      it->second.pAbstract->UpdateEnabledState( true );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PreferencesProcessor::Apply()
{
  const DisableAssertionLoadingFilesGuard dalf;

  typedef set<string> ApplyCommands;
  ApplyCommands applyCommands;

  for( Variables::const_iterator it = variables.begin(); it != variables.end(); ++it )
    if( NeedToApplyCommand(it->second) )
      applyCommands.insert( it->second.pDesc->applyCommandName );  

  for( ApplyCommands::iterator it = applyCommands.begin(); it != applyCommands.end(); ++it )
  {
    DebugTrace( "RunCommand: %s", it->c_str() );
    const bool result = NGlobal::RunCommand( NStr::ToUnicode(*it) );  
    NI_ASSERT( result, NStr::StrFmt("Command execution failed: %s", it->c_str()) );
  }
  
  StoreAllValues();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PreferencesProcessor::Cancel()
{
  const DisableAssertionLoadingFilesGuard dalf;

  RestoreAllValues();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PreferencesProcessor::ApplyShortcuts()
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PreferencesProcessor::ShortcutRebind( const wchar_t* command )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void PreferencesProcessor::OnFSCommand( UI::FlashContainer2* _wnd, const char* listenerID,  const char* args, const wchar_t * argsW  )
{
  if( strcmp(listenerID, szApplyFlashCommand) == 0 )
  {
    Apply();
  }
  else if( strcmp(listenerID, szCancelFlashCommand) == 0 )
  {
    Cancel();
  }
  else if( strcmp(listenerID, szShortcutRebindFlashCommand) == 0 )
  {
    ShortcutRebind(argsW);
  }
  else if( strcmp(listenerID, szShortcutsApplyFlashCommand) == 0 )
  {
    ApplyShortcuts();
  }
  else if( strcmp(listenerID, szUpdateFlashCommand) == 0 )
  {
    string varId; 
        
    for( ; *args != '\0' && *args != ' ';  ++args )
      varId += *args;     
    
    int value;
    
    sscanf_s( args, "%d", &value );
    UpdateValue( varId, value );
  }
  else if( strcmp(listenerID, szLoadPresetFlashCommand) == 0 )
  {  
    RestorePreset( args );
  }
  else
  {
    NI_ALWAYS_ASSERT( NStr::StrFmt("Unknown flash command: %s", listenerID) );
    return; 
  }
  
  CallMethod( "ActivateAbilityToChange", NeedToApply() ); 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace UI

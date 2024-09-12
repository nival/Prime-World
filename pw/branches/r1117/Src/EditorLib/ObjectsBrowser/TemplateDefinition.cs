using System;
using libdb.DB;
using libdb.Diagnostics;
using libdb.UndoRedo;

namespace DBTypes
{
  public enum TemplateModifiable
  {
    None = 0,
    Modifiable = 1,
    NonNull = 2,
    NonBrowse = 3,
  };

  public class TemplateModifiableProperty : libdb.ICompositeDBValue, libdb.IChangeable
  {
    private DBResource owner = null;
    public DBResource GetOwner() { return owner; }

    private TemplateModifiableProperty __parent = null;

    public event EventHandler Changed;

    protected void FireChangedEvent( object sender, EventArgs e )
    {
      if ( Changed != null ) Changed( sender, e );
    }

    private UndoRedo<string> _name;
    private UndoRedo<string> _field;
    private UndoRedo<TemplateModifiable> _modifiable;

    public string name { get { return _name.Get(); } set { _name.Set( value ); } }

    public string field { get { return _field.Get(); } set { _field.Set( value ); } }

    public TemplateModifiable modifiable { get { return _modifiable.Get(); } set { _modifiable.Set( value ); } }

    private void Initialize( DBResource owner )
    {
      _name = new UndoRedo<string>( owner, string.Empty );
      _field = new UndoRedo<string>( owner, string.Empty );
      _modifiable = new UndoRedo<TemplateModifiable>( owner, TemplateModifiable.None );
      _name.Changed += FireChangedEvent;
      _field.Changed += FireChangedEvent;
      _modifiable.Changed += FireChangedEvent;
    }

    public TemplateModifiableProperty()
    {
      Initialize( GetOwner() );
    }

    public TemplateModifiableProperty( DBResource owner )
    {
      this.owner = owner;
      Initialize( GetOwner() );
    }

    public TemplateModifiableProperty( DBResource owner, TemplateModifiableProperty source )
      : this( owner, source, true ) { }

    protected TemplateModifiableProperty( DBResource owner, TemplateModifiableProperty source, bool fireEvent )
    {
      _name = new UndoRedo<string>( owner, source.name );
      _field = new UndoRedo<string>( owner, source.field );
      _modifiable = new UndoRedo<TemplateModifiable>( owner, source.modifiable );
      _name.Changed += FireChangedEvent;
      _field.Changed += FireChangedEvent;
      _modifiable.Changed += FireChangedEvent;
      this.owner = owner;
      if ( fireEvent )
        FireChangedEvent( this, EventArgs.Empty );
    }

    public virtual void Assign( object _source )
    {
      TemplateModifiableProperty source = _source as TemplateModifiableProperty;
      if ( null == source || this == source )
        return;
      DataBase.UndoRedoManager.Start( "Assign for TemplateModifiableProperty" );
      name = source.name;
      field = source.field;
      modifiable = source.modifiable;
      DataBase.UndoRedoManager.Commit();
    }

    public virtual void SetParent( object _newParent )
    {
      TemplateModifiableProperty newParent = _newParent as TemplateModifiableProperty;
      if ( newParent == null && this.__parent != null )
        Assign( this );
      this.__parent = newParent;

      _name.SetParent( newParent == null ? null : newParent._name );
      _field.SetParent( newParent == null ? null : newParent._field );
      _modifiable.SetParent( newParent == null ? null : newParent._modifiable );
    }

    public virtual void Reset()
    {
      _name.Reset();
      _field.Reset();
      _modifiable.Reset();
    }

    public virtual bool IsDerivedFromParent()
    {
      if ( __parent == null )
        return true;
      return
        _name.IsDerivedFromParent()
        && _field.IsDerivedFromParent()
        && _modifiable.IsDerivedFromParent()
        ;
    }

    public virtual void ResetField( string fieldName )
    {
      if ( fieldName == "name" )
        _name.Reset();
      else if ( fieldName == "field" )
        _field.Reset();
      else if ( fieldName == "modifiable" )
        _modifiable.Reset();
      else
        Log.AlwaysAssert( "Field with name {0} not found", fieldName );
    }

    public virtual bool IsFieldDerivedFromParent( string fieldName )
    {
      if ( __parent == null )
        return true;
      if ( fieldName == "__parent" )
        return __parent == null;
      if ( fieldName == "name" )
        return _name.IsDerivedFromParent();
      if ( fieldName == "field" )
        return _field.IsDerivedFromParent();
      if ( fieldName == "modifiable" )
        return _modifiable.IsDerivedFromParent();
      else
      {
        Log.AlwaysAssert( "Field with name {0} not found", fieldName );
        return true;
      }
    }
    public virtual bool HasParent()
    {
      return __parent != null;
    }
  }

  public class TemplateDefinition : DBResource
  {
    private UndoRedoDBPtr<TemplateDefinition> ___parent;
    [HideInOutliner]
    public new DBPtr<TemplateDefinition> __parent
    {
      get { return ___parent.Get(); }
      set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } }
    }

    private UndoRedo<string> _name;
    private UndoRedo<string> _namePattern;
    private UndoRedoDBPtr<DBResource> _templateObject;
    private UndoRedoAssignableList<TemplateModifiableProperty> _fields;

    public string name { get { return _name.Get(); } set { _name.Set( value ); } }

    public string namePattern { get { return _namePattern.Get(); } set { _namePattern.Set( value ); } }

    public DBPtr<DBResource> templateObject { get { return _templateObject.Get(); } set { _templateObject.Set( value ); } }

    public libdb.IChangeableList<TemplateModifiableProperty> fields { get { return _fields; } set { _fields.Assign( value ); } }

    private void Initialize( DBResource owner )
    {
      ___parent = new UndoRedoDBPtr<TemplateDefinition>( owner );
      _name = new UndoRedo<string>( owner, string.Empty );
      _namePattern = new UndoRedo<string>( owner, string.Empty );
      _templateObject = new UndoRedoDBPtr<DBResource>( owner );
      _fields = new UndoRedoAssignableList<TemplateModifiableProperty>( owner );
      ___parent.Changed += FireChangedEvent;
      _name.Changed += FireChangedEvent;
      _namePattern.Changed += FireChangedEvent;
      _templateObject.Changed += FireChangedEvent;
      _fields.Changed += FireChangedEvent;
    }

    public TemplateDefinition()
    {
      Initialize( this );
    }
    private void AssignSelf( TemplateDefinition source )
    {
      DataBase.UndoRedoManager.Start( "Assign for TemplateDefinition" );
      name = source.name;
      namePattern = source.namePattern;
      templateObject = source.templateObject;
      fields = source.fields;
      DataBase.UndoRedoManager.Commit();
    }

    public override void Assign( object _source )
    {
      TemplateDefinition source = _source as TemplateDefinition;
      if ( source == null || this == source )
        return;
      DataBase.UndoRedoManager.Start( "Assign for TemplateDefinition" );
      AssignSelf( source );
      DataBase.UndoRedoManager.Commit();
    }

    public override void SetParent( object _newParent )
    {
      DBPtrBase rawParent = _newParent as DBPtrBase;
      TemplateDefinition newParent = rawParent == null ? null : rawParent.Get<TemplateDefinition>();
      if ( newParent == null && _newParent is TemplateDefinition )
        newParent = _newParent as TemplateDefinition;
      if ( newParent == null && this.__parent.IsValid )
        AssignSelf( this );
      this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
      base.SetParent( newParent );

      _name.SetParent( newParent == null ? null : newParent._name );
      _namePattern.SetParent( newParent == null ? null : newParent._namePattern );
      _templateObject.SetParent( newParent == null ? null : newParent._templateObject );
      _fields.SetParent( newParent == null ? null : newParent._fields );
    }

    public override void Reset()
    {
      _name.Reset();
      _namePattern.Reset();
      _templateObject.Reset();
      _fields.Reset();
      base.Reset();
    }

    public override bool IsDerivedFromParent()
    {
      if ( __parent == null || __parent.Get() == null )
        return true;
      return
        _name.IsDerivedFromParent()
        && _namePattern.IsDerivedFromParent()
        && _templateObject.IsDerivedFromParent()
        && _fields.IsDerivedFromParent()
        && base.IsDerivedFromParent();
    }

    public override void ResetField( string fieldName )
    {
      if ( fieldName == "name" )
        _name.Reset();
      else if ( fieldName == "namePattern" )
        _namePattern.Reset();
      else if ( fieldName == "templateObject" )
        _templateObject.Reset();
      else if ( fieldName == "fields" )
        _fields.Reset();
      else
        base.ResetField( fieldName );
    }

    public override bool IsFieldDerivedFromParent( string fieldName )
    {
      if ( __parent == null || __parent.Get() == null )
        return true;
      if ( fieldName == "__parent" )
        return __parent == null || __parent.Get() == null;
      if ( fieldName == "name" )
        return _name.IsDerivedFromParent();
      if ( fieldName == "namePattern" )
        return _namePattern.IsDerivedFromParent();
      if ( fieldName == "templateObject" )
        return _templateObject.IsDerivedFromParent();
      if ( fieldName == "fields" )
        return _fields.IsDerivedFromParent();
      else
        return base.IsFieldDerivedFromParent( fieldName );
    }
    public override bool HasParent()
    {
      return __parent != null;
    }
  }
}

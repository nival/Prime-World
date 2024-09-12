using System;
using System.Xml.Serialization;
using libdb.Diagnostics;

namespace libdb.DB
{
	public class DBResource : IChangeable, ICompositeDBValue
	{
		private DBID dbid = DBID.Empty;
    private String dataStateName = String.Empty;

		internal void Rename( DBID dbid ) { this.dbid = dbid; }
		public DBID DBId { get { return dbid; } }
    internal void SetStateName( String stateName ) { this.dataStateName = stateName; }
    public String GetStateName() { return this.dataStateName; }

		public event EventHandler Changed;

		protected void FireChangedEvent( object sender, EventArgs e )
		{
			if ( Changed != null )
			{
				Changed( sender, e );
			}
		}

    // Inheritance support
  	[HideInOutliner]
    [NoCode]
    public DBPtr<DBResource> __parent { get; set; }
    public virtual void SetParent( object _newParent ) { }
    public virtual void Reset() { }
    public virtual bool IsDerivedFromParent() { return true; }
    public virtual void ResetField( string fieldName ) 
    {
      Log.AlwaysAssert( "Field with name {0} not found", fieldName );
    }
    public virtual bool IsFieldDerivedFromParent( string fieldName )
    {
      Log.AlwaysAssert( "Field with name {0} not found", fieldName );
      return true;
    }

    public virtual bool HasParent()
    {
      return false;
    }


    public virtual void Assign( object source ) { }
    public virtual DBResource GetOwner() { return this; }
	}
}

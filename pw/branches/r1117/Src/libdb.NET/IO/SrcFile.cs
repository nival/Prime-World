using System;
using System.Collections.Generic;
using System.Text;
using libdb.DB;

namespace libdb.IO
{
	[SimpleType]
	public sealed class SrcFile : TypedSerializable<string, SrcFile.ScrFileSerializeAttributes>, IBasicDBValue
	{
		public class ScrFileSerializeAttributes
		{
			public uint crc = 0;
			public ScrFileSerializeAttributes() { }
			public ScrFileSerializeAttributes( uint crc ) { this.crc = crc; }
		}

		private string fileName = string.Empty;
		private uint checksum = 0;

		public SrcFile() { }

		public SrcFile( DBResource owner )
		{
			this.owner = owner;
		}

    public SrcFile( DBResource owner, SrcFile source )
		{
			this.owner = owner;
      fileName = source.fileName;
      checksum = source.checksum;
		}

		public SrcFile( string fileName ) 
    { 
      this.fileName = fileName; 
    }

    public event EventHandler Changed = null;
    private DBResource owner = null;
    public DBResource GetOwner() { return owner; }

    public void SetFileName( string _fileName ) { fileName = _fileName; OnChanged(); }
    public void SetChecksum( uint _checksum ) { checksum = _checksum; OnChanged(); }

		public string FileName { 
      get {
        if ( parent != null && isDerivedFromParent )
          return parent.FileName;
        return fileName; 
      } 
    }

		public uint Checksum { 
      get {
        if ( parent != null && isDerivedFromParent )
          return parent.Checksum;
        return checksum; 
      } 
    }

		public override string ToString() 
    {
      if ( parent != null && isDerivedFromParent )
        return parent.ToString();
      return System.IO.Path.GetFileName( fileName );
    }

		protected override void SerializeTyped( FieldPath path, out string nestedObject, out ScrFileSerializeAttributes attributes )
		{
			nestedObject = FileName;
			attributes = new ScrFileSerializeAttributes( Checksum );
		}

		protected override bool DeserializeAttributesTyped( ScrFileSerializeAttributes attributes )
		{
			return true;
		}

		protected override bool DeserializeNestedObjectTyped( ScrFileSerializeAttributes attributes, string nestedObject )
		{
			SetChecksum( attributes.crc );
      SetFileName( nestedObject );

			return true;
		}

    private bool isDerivedFromParent = true;
    private SrcFile parent = null;

    public void Assign( object _source ) 
    {
      SrcFile source = _source as SrcFile;
      if ( source == null )
        return;

      fileName = source.fileName; 
      checksum = source.checksum;
      OnChanged();
    }

    private void OnChanged()
    {
      isDerivedFromParent = false;

      if ( Changed != null )
        Changed( this, EventArgs.Empty );

      if ( owner != null && !DBID.IsNullOrEmpty( owner.DBId ) )
        DataBase.ChangeCallback( owner.DBId );
    }

    public void SetParent( object _parent )
    {
      SrcFile parent = _parent as SrcFile;
      if ( parent == null )
        return;
      this.parent = parent;
    }

    public void Reset()
    {
      isDerivedFromParent = true;
    }

    public bool IsDerivedFromParent()
    {
      return parent == null || isDerivedFromParent;
    }
	}
}

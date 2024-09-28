using System;

namespace EditorLib.Extensions
{
	public sealed class EditorAttribute : Attribute
	{
		public readonly string name = string.Empty;
		public readonly bool isDefault = false;
		public readonly Guid guid = Guid.Empty;
		
		/// <summary>
    /// isDefault = false;  guid = Empty;
		/// </summary>
		public EditorAttribute( string name ) { this.name = name; }
		/// <summary>
    /// guid = Empty;
		/// </summary>
		public EditorAttribute( string name, bool _isDefault ) 
    { this.name = name; this.isDefault = _isDefault; }
    public EditorAttribute( string name, bool _isDefault, string _guid )
		{ this.name = name; this.isDefault = _isDefault; this.guid = new Guid(_guid); }
	}

	public sealed class ApplicableForDeriverAttribute : Attribute
	{
		public Type[] Exclude { get; set; }
	}

  [AttributeUsage( AttributeTargets.Enum )]
  public sealed class CustomStandardValuesForAttribute : Attribute
  {
    public readonly string name = string.Empty;

    public CustomStandardValuesForAttribute( string name ) { this.name = name; }
  }

  public sealed class SupressValueEditor : Attribute { }
}

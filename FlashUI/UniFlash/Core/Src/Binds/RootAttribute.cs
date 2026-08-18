using System;

namespace Flash
{
	[AttributeUsage( AttributeTargets.Class)]
	public sealed class RootAttribute : Attribute
	{
		private string _targetRoot;
		public string TargetRoot
		{
			get { return _targetRoot; }
		}
		private readonly bool _writeToXml;
		public bool WriteToXml
		{
			get { return _writeToXml; }
		}

		public RootAttribute()
		{
			_writeToXml = true;
		}
		public RootAttribute( bool writeToXml )
		{
			_writeToXml = writeToXml;
		}
		public RootAttribute( string name )
		{
			_targetRoot = name;
			_writeToXml = true;
		}
		public RootAttribute(string name,bool writeToXml)
		{
			_targetRoot = name;
			_writeToXml = writeToXml;
		}
	}
}

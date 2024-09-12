using System.Xml;

namespace DBCodeGen.VisualStudioSupport
{
	internal class NullProject : Project
	{
		public NullProject( string name ) : base( name )
		{
			SetProjectName( name );
		}

		protected override string GetFileNameInProject( string fileName )
		{
			return ProjectName + "_" + fileName;
		}

		protected override XmlDocument StoreProject()
		{
			return null;
		}
	}
}

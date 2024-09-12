using System.ComponentModel;
using libdb.DB;

namespace EditorLib.PropertiesEditor
{
	public sealed class SrcFileListDescriptionProvider : TypeDescriptionProvider
	{
		private readonly object instance;
		private readonly DBFieldInfo member;
		private readonly IEditorCommonApplication application;

		public SrcFileListDescriptionProvider( IEditorCommonApplication _application, object _instance, DBFieldInfo _member )
		{
			instance = _instance;
			member = _member;
			application = _application;
		}

		public override ICustomTypeDescriptor GetTypeDescriptor( System.Type _1, object _2 )
		{
			return new SrcFileListDescriptor( application, instance, member );
		}
	}
}

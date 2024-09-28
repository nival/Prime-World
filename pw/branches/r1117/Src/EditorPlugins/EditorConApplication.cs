using System;
using EditorLib.Panels;
using WeifenLuo.WinFormsUI.Docking;
using EditorLib.ContextMenus;
using EditorLib.Plugin;
using EditorLib.Operations;
using EditorLib;

namespace EditorPlugins
{
	public abstract class EditorConApplication : EditorNativeApplication, IEditorConApplication
	{
		private NoThreadExecutor operationExecutor = new NoThreadExecutor();

		protected override void RegisterExtensions()
		{
			Extensions.RegisterExtensions( this );
		}

		public IEditorCommonApplication Application { get { return this; } }

		public override Executor OperationExecutor { get { return operationExecutor; } }
	}
}

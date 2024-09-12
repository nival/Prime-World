namespace EditorLib.Menu
{
	public abstract class IEditorCommand
	{
		public abstract void Execute( IEditorWinApplication application );
		
		protected virtual void OnChanged() {}

		public virtual string Name { get { return null; } }
		public virtual bool Visible { get { return true; } }
		public virtual bool Enabled { get{ return true; } }
		public virtual System.Drawing.Bitmap Image { get { return null; } }
    public virtual string TooltipText { get { return Name; } }
    public virtual bool IsChecked { get { return false; } }
  }
}

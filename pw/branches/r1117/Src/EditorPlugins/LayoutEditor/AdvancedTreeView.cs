namespace EditorPlugins.LayoutEditor
{
public class AdvancedTreeView : System.Windows.Forms.TreeView
{

	protected override void DefWndProc(ref System.Windows.Forms.Message m)
	{
		const long WM_NCLBUTTONDBLCLK = 0xA3;
		const long WM_LBUTTONDBLCLK = 0x203;
		//const long WM_LBUTTONDOWN = 0x0201;
		//const long WM_LBUTTONUP = 0x0202;
		if(m.Msg == WM_NCLBUTTONDBLCLK || m.Msg == WM_LBUTTONDBLCLK)
				m.Msg = 0; //Discard the message 
		else
				base.DefWndProc(ref m); 
	}

};
}

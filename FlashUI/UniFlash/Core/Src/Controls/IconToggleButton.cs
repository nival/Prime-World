namespace Flash.Controls
{
    public class IconToggleButton : ToggleButton
    {
        [Bind("icon")]
        protected readonly ImageBox _icon = new ImageBox();

        public string IconImage
        {
            get { return _icon.Image; }
            set { _icon.Image = value; }
        }
    }
}
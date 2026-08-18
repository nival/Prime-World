namespace Flash.Controls
{
	class ImageSelectionButton : SelectionButton
	{
		[Bind("img")]
		protected readonly ImageBox Icon = new ImageBox();

		public string Image
		{
			get { return Icon.Image; }
			set { Icon.Image = value; }
		}
	}

  class VideoSelectionButton : SelectionButton
  {
    [Bind("img")]
    private readonly VideoIconContainer Icon = new VideoIconContainer();

    public ImageBox ButtonIcon
    {
      get { return Icon.Icon; }
    }
  }

  internal class VideoIconContainer : Control
  {
    [Bind("icon")]
    public readonly ImageBox Icon = new ImageBox();
  }
}

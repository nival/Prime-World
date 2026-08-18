namespace Flash.Controls
{
  class ImageButton : Button
  {
    [Bind("icon")]
    private readonly ImageBox _image = new ImageBox();

    protected override void Init()
    {
      base.Init();
      _image.SizeMode = ImageSizeMode.StretchToCurrent;
    }

    public string Image
    {
      get { return _image.Image; }
      set { _image.Image = value; }
    }
  }
}

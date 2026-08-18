using System;

public class ResolutionEventArgs : EventArgs 
{
	public int Width { get; private set; }
	public int Height { get; private set; }

	public ResolutionEventArgs( int width, int height )
	{
		Width = width;
		Height = height;
	}
}

using System;

namespace libdb
{
	public interface IChangeable
	{
		event EventHandler Changed;
	}
}

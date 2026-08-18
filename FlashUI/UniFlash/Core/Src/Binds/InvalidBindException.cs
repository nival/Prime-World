using System;

namespace Flash
{
	public class InvalidBindException : Exception
	{
		public InvalidBindException( string message ): base( message ){}
	}
}

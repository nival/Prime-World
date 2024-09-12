using System;

namespace EditorLib.Operations
{
	public interface IOperationContext
	{
		/// <summary>
		/// Callback that should be called on operation start
		/// </summary>
		/// <param name="knownDuration">Operation has known duration so progress bar can be used for show operation's progress</param>
		/// <param name="blockInterface">Block user interface during the operation's execution</param>
		void Start( bool knownDuration, bool blockInterface );
		
		/// <summary>
		/// Show message during operation execution
		/// </summary>
		/// <param name="message">The message</param>
		void Progress( string message );
		
		/// <summary>
		/// Show message during operation execution and update its progress. Valid only if operation was started with knownDuration equals to true
		/// </summary>
		/// <param name="message">The message</param>
		/// <param name="progress">Progress of current operation in percents (from 0 to 100)</param>
		void Progress( string message, int progress );
	}
}

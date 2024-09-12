using System;
using System.Collections.Generic;
using System.Text.RegularExpressions;
using River.Core.Diagnostics;
using NUnit.Framework;
using System.Diagnostics;

namespace River.Tests
{
	[SetUpFixture]
	public sealed class TestDumper : IDumper
	{
		private class Message
		{
			public readonly Log.Level level;
			public readonly string message;

			public Message( Log.Level level, string message ) { this.level = level; this.message = message; }
		}

		public enum FindCondition
		{
			Equals,
			Contains,
		}

		private static bool FindConditionEquals( string str, string pattern, bool ignoreCase )
		{
			return string.Compare( str, pattern, ignoreCase ? StringComparison.InvariantCultureIgnoreCase : StringComparison.InvariantCulture ) == 0;
		}

		private static bool FindConditionContains( string str, string pattern, bool ignoreCase )
		{
			return str.IndexOf( pattern, ignoreCase ? StringComparison.InvariantCultureIgnoreCase : StringComparison.InvariantCulture ) >= 0;
		}

		private static List<Message> messages = new List<Message>();

		public static bool FindMessage( Log.Level level )
		{
			lock ( messages )
			{
				return messages.Exists( message => message.level == level );
			}
		}

		public static bool FindMessage( string pattern, FindCondition condition, bool ignoreCase )
		{
			lock ( messages )
			{
				switch ( condition )
				{
				case FindCondition.Equals:
					return messages.Exists( message => FindConditionEquals( message.message, pattern, ignoreCase ) );
				case FindCondition.Contains:
					return messages.Exists( message => FindConditionContains( message.message, pattern, ignoreCase ) );
				}
			}

			return false;
		}

		public static bool FindMessage( Log.Level level, string pattern, FindCondition condition, bool ignoreCase )
		{
			lock ( messages )
			{
				switch ( condition )
				{
				case FindCondition.Equals:
					return messages.Exists( message => FindConditionEquals( message.message, pattern, ignoreCase ) && message.level == level );
				case FindCondition.Contains:
					return messages.Exists( message => FindConditionContains( message.message, pattern, ignoreCase ) && message.level == level );
				}
			}

			return false;
		}

		public static void Clear()
		{
			lock ( messages )
			{
				messages.Clear();
			}
		}

		public void Trace( Log.Level level, TimeSpan time, int threadId, string fileName, int lineNumber, string message )
		{
			lock ( messages )
			{
				messages.Add( new Message( level, message ) );
			}
		}
		
		[SetUp]
		public void SetUp()
		{
			Log.AttachDumper( new TestDumper() );
			Log.AttachDumper( new DebuggerDumper( true ) );
		}
	}
}

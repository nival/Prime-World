using System;
using System.Collections.Generic;
using System.Text;

namespace River.Core
{
	[Serializable]
	[AttributeUsage( AttributeTargets.Class, AllowMultiple = true, Inherited = false )]
	public class DistributeAttribute : Attribute
	{
		private readonly int count = 1;

		public DistributeAttribute() { }
		public DistributeAttribute( int count ) { this.count = count; }

		public int Count { get { return count; } }

		public bool IsMatch( BotDescription bot )
		{
			return true;
		}

		public static bool IsEqual( DistributeAttribute a, DistributeAttribute b )
		{
			return true;
		}
	}
}

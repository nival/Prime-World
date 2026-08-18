using System;
using UnityEngine;

namespace Flash
{
	[AttributeUsage( AttributeTargets.Field )]
	public sealed class BindAttribute : Attribute
	{
		private readonly string _targenControl = String.Empty;
		public string TargenControl
		{
			get { return _targenControl; }
		}

		public BindAttribute(string name )
		{
			_targenControl = name;
		}	
	}
}

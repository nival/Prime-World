using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;

namespace DBCodeGen.MaterialsGeneration
{
	public class MaterialPinDefenition
	{
		private readonly string pinName = string.Empty;
		private readonly Type pinType = null;
		private readonly bool pinRuntime = false;

		private int pinMultiplier = 0;

		public MaterialPinDefenition( string pinName, Type pinType, bool pinRuntime )
		{
			this.pinName = pinName;
			this.pinType = pinType;
			//this.pinMultiplier = pinMultiplier;
			this.pinRuntime = pinRuntime;
		}

		public int SetPinMultiplier( int pinMultiplier )
		{
			this.pinMultiplier = pinMultiplier;
			return NextMultiplier;
		}

		public string PinName { get { return pinName; } }
		public Type PinType { get { return pinType; } }
		public int PinMultiplier { get { return pinMultiplier; } }
		public bool PinRuntime { get { return pinRuntime; } }
		public int PinValuesCount { get { return pinType.GetFields( BindingFlags.Public | BindingFlags.Static ).Length; } }

		public int NextMultiplier { get { return pinMultiplier * PinValuesCount; } }

		public static int Compare( MaterialPinDefenition pin1, MaterialPinDefenition pin2 )
		{
			return string.Compare( pin1.pinName, pin2.pinName );
		}
	}
}

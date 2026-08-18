using System;
using System.ComponentModel;
using System.Reflection;

namespace FlashView.Utils
{
	public static class EnumUtils
	{
		public static string GetEnumDescription( Enum enumInstance )	
		{
			MemberInfo[] memInfo = enumInstance.GetType().GetMember( enumInstance.ToString() );
			object[] attributes = memInfo[0].GetCustomAttributes( typeof(DescriptionAttribute), false );

			foreach (object attr in attributes)
			{
				DescriptionAttribute desc = attr as DescriptionAttribute;

				if (desc != null)
				{
					return desc.Description;
				}
			}

			return enumInstance.ToString();
		}
	}
}

using System;
using System.Collections.Generic;
using System.Text;

namespace Tools.MayaExeInteraction
{
	[Serializable]
	class MayaCommand
	{
		public string Name { get; set; }
		public string Script { get; set; }
		public string ParametersOrder { get; set; }          
    public SortedList<string, string> Parameters { get; private set; }

    public MayaCommand()
    {
      Parameters = new SortedList<string, string>();
    }
    
    public virtual string CreateCommand()
    {
      var result = new StringBuilder();

      result.Append( Name );
            
      //Other parameters
    	foreach( var paramName in GetParameters() )
      {
        string paramValue;
        if(Parameters.TryGetValue(paramName, out paramValue))
        {
          result.AppendFormat( " \"{0}\"", paramValue );
        }
      }

      return result.ToString();
    }

		protected string[] GetParameters()
		{
			string[] result;

			if( Parameters.Count == 1 )//если задан всего один параметр, то не надо учитывать ParametersOrder
			{
				result = new[] { Parameters.Keys[0] };
			}
			else
			{
				if( ParametersOrder == null )
					ParametersOrder = string.Empty;

				result = ParametersOrder.Split( '|' );
			}

			return result;
		}

		public override string ToString()
    {
      return CreateCommand();
    }
	}
}

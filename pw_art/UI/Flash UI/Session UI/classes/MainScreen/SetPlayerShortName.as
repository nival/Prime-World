package MainScreen 
{

	public class SetPlayerShortName
	{
		
		public function SetPlayerShortName() 
		{
			
		}
		
		public function SetPlayerName(playername:String): String
		{
			var _heroName:String = "";
			if (playername == null || playername== "") return "";
			
			if (playername.substr(0, 1) != "[")
				_heroName = playername;
			else 
				_heroName = playername.substring(playername.indexOf("]")+1);
			return _heroName;
		}
	}

}
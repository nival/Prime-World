#ifndef _PROFILE_MANAGER_H_
#define _PROFILE_MANAGER_H_

namespace NProfile
{
	enum EProfileFolder
	{
		FOLDER_GLOBAL,
    FOLDER_COMMON_APPDATA,
		FOLDER_USER,
		FOLDER_PLAYER,
		FOLDER_SAVE,
    FOLDER_SCREENSHOTS,
    FOLDER_LOGS,
    FOLDER_REPLAYS
	};

	void Init( const string &productName );

	bool AddPlayer( const wstring &playerName );
	bool ChangePlayer( const wstring &playerName );
	bool DeletePlayer( const wstring &playerName );
	
	int GetPlayersList( vector<string> *pPlayers );
	
	const string &GetFullFolderPath( const EProfileFolder folder );
	string GetFullFilePath( const string &fileName, const EProfileFolder folder );

  const string &GetRootLogsFolder();
};

#endif


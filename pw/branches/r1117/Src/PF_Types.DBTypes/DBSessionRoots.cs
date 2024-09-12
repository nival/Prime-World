// Automatically generated file, don't change it manually!
using System;
using System.Collections.Generic;
using System.ComponentModel;

using libdb;
using libdb.DB;
using libdb.IO;
using libdb.UndoRedo;
using libdb.Diagnostics;
using libdb.Animated;

namespace DBTypes
{
[Custom("DBServer")]
[UseTypeName("ROOT")]
public class SessionLogicRoot : DBResource
{
	private UndoRedoDBPtr<SessionLogicRoot> ___parent;
	[HideInOutliner]
	public new DBPtr<SessionLogicRoot> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<AILogicParameters> _aiLogic;
	private UndoRedoDBPtr<ScoringTable> _scoringTable;
	private UndoRedoDBPtr<UnitsLogicParameters> _unitLogicParameters;
	private UndoRedoDBPtr<GlyphsDB> _glyphsDB;
	private UndoRedoDBPtr<HeroesDB> _heroes;
	private UndoRedoDBPtr<HeroesLevelUps> _heroesLevelups;
	private UndoRedoDBPtr<ImpulsiveBuffsContainer> _impulsiveBuffs;
	private UndoRedoDBPtr<DefaultFormulas> _defaultFormulas;
	private UndoRedoDBPtr<MapList> _mapList;
	private UndoRedoDBPtr<GuildBuffsCollection> _guildBuffsCollection;

	public DBPtr<AILogicParameters> aiLogic { get { return _aiLogic.Get(); } set { _aiLogic.Set( value ); } }

	public DBPtr<ScoringTable> scoringTable { get { return _scoringTable.Get(); } set { _scoringTable.Set( value ); } }

	public DBPtr<UnitsLogicParameters> unitLogicParameters { get { return _unitLogicParameters.Get(); } set { _unitLogicParameters.Set( value ); } }

	public DBPtr<GlyphsDB> glyphsDB { get { return _glyphsDB.Get(); } set { _glyphsDB.Set( value ); } }

	public DBPtr<HeroesDB> heroes { get { return _heroes.Get(); } set { _heroes.Set( value ); } }

	public DBPtr<HeroesLevelUps> heroesLevelups { get { return _heroesLevelups.Get(); } set { _heroesLevelups.Set( value ); } }

	public DBPtr<ImpulsiveBuffsContainer> impulsiveBuffs { get { return _impulsiveBuffs.Get(); } set { _impulsiveBuffs.Set( value ); } }

	public DBPtr<DefaultFormulas> defaultFormulas { get { return _defaultFormulas.Get(); } set { _defaultFormulas.Set( value ); } }

	public DBPtr<MapList> mapList { get { return _mapList.Get(); } set { _mapList.Set( value ); } }

	public DBPtr<GuildBuffsCollection> guildBuffsCollection { get { return _guildBuffsCollection.Get(); } set { _guildBuffsCollection.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SessionLogicRoot>(owner);
		_aiLogic = new UndoRedoDBPtr<AILogicParameters>( owner );
		_scoringTable = new UndoRedoDBPtr<ScoringTable>( owner );
		_unitLogicParameters = new UndoRedoDBPtr<UnitsLogicParameters>( owner );
		_glyphsDB = new UndoRedoDBPtr<GlyphsDB>( owner );
		_heroes = new UndoRedoDBPtr<HeroesDB>( owner );
		_heroesLevelups = new UndoRedoDBPtr<HeroesLevelUps>( owner );
		_impulsiveBuffs = new UndoRedoDBPtr<ImpulsiveBuffsContainer>( owner );
		_defaultFormulas = new UndoRedoDBPtr<DefaultFormulas>( owner );
		_mapList = new UndoRedoDBPtr<MapList>( owner );
		_guildBuffsCollection = new UndoRedoDBPtr<GuildBuffsCollection>( owner );
		___parent.Changed += FireChangedEvent;
		_aiLogic.Changed += FireChangedEvent;
		_scoringTable.Changed += FireChangedEvent;
		_unitLogicParameters.Changed += FireChangedEvent;
		_glyphsDB.Changed += FireChangedEvent;
		_heroes.Changed += FireChangedEvent;
		_heroesLevelups.Changed += FireChangedEvent;
		_impulsiveBuffs.Changed += FireChangedEvent;
		_defaultFormulas.Changed += FireChangedEvent;
		_mapList.Changed += FireChangedEvent;
		_guildBuffsCollection.Changed += FireChangedEvent;
	}

	public SessionLogicRoot()
	{
		Initialize( this );
	}
	private void AssignSelf( SessionLogicRoot source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SessionLogicRoot" );
		aiLogic = source.aiLogic;
		scoringTable = source.scoringTable;
		unitLogicParameters = source.unitLogicParameters;
		glyphsDB = source.glyphsDB;
		heroes = source.heroes;
		heroesLevelups = source.heroesLevelups;
		impulsiveBuffs = source.impulsiveBuffs;
		defaultFormulas = source.defaultFormulas;
		mapList = source.mapList;
		guildBuffsCollection = source.guildBuffsCollection;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SessionLogicRoot source = _source as SessionLogicRoot;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SessionLogicRoot" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SessionLogicRoot newParent = rawParent == null ? null : rawParent.Get<SessionLogicRoot>();
		if ( newParent == null && _newParent is SessionLogicRoot )
			newParent = _newParent as SessionLogicRoot;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_aiLogic.SetParent( newParent == null ? null : newParent._aiLogic );
		_scoringTable.SetParent( newParent == null ? null : newParent._scoringTable );
		_unitLogicParameters.SetParent( newParent == null ? null : newParent._unitLogicParameters );
		_glyphsDB.SetParent( newParent == null ? null : newParent._glyphsDB );
		_heroes.SetParent( newParent == null ? null : newParent._heroes );
		_heroesLevelups.SetParent( newParent == null ? null : newParent._heroesLevelups );
		_impulsiveBuffs.SetParent( newParent == null ? null : newParent._impulsiveBuffs );
		_defaultFormulas.SetParent( newParent == null ? null : newParent._defaultFormulas );
		_mapList.SetParent( newParent == null ? null : newParent._mapList );
		_guildBuffsCollection.SetParent( newParent == null ? null : newParent._guildBuffsCollection );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_aiLogic.Reset();
		_scoringTable.Reset();
		_unitLogicParameters.Reset();
		_glyphsDB.Reset();
		_heroes.Reset();
		_heroesLevelups.Reset();
		_impulsiveBuffs.Reset();
		_defaultFormulas.Reset();
		_mapList.Reset();
		_guildBuffsCollection.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_aiLogic.IsDerivedFromParent()
			&& _scoringTable.IsDerivedFromParent()
			&& _unitLogicParameters.IsDerivedFromParent()
			&& _glyphsDB.IsDerivedFromParent()
			&& _heroes.IsDerivedFromParent()
			&& _heroesLevelups.IsDerivedFromParent()
			&& _impulsiveBuffs.IsDerivedFromParent()
			&& _defaultFormulas.IsDerivedFromParent()
			&& _mapList.IsDerivedFromParent()
			&& _guildBuffsCollection.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "aiLogic" )
			_aiLogic.Reset();
		else if ( fieldName == "scoringTable" )
			_scoringTable.Reset();
		else if ( fieldName == "unitLogicParameters" )
			_unitLogicParameters.Reset();
		else if ( fieldName == "glyphsDB" )
			_glyphsDB.Reset();
		else if ( fieldName == "heroes" )
			_heroes.Reset();
		else if ( fieldName == "heroesLevelups" )
			_heroesLevelups.Reset();
		else if ( fieldName == "impulsiveBuffs" )
			_impulsiveBuffs.Reset();
		else if ( fieldName == "defaultFormulas" )
			_defaultFormulas.Reset();
		else if ( fieldName == "mapList" )
			_mapList.Reset();
		else if ( fieldName == "guildBuffsCollection" )
			_guildBuffsCollection.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "aiLogic" )
			return _aiLogic.IsDerivedFromParent();
		if ( fieldName == "scoringTable" )
			return _scoringTable.IsDerivedFromParent();
		if ( fieldName == "unitLogicParameters" )
			return _unitLogicParameters.IsDerivedFromParent();
		if ( fieldName == "glyphsDB" )
			return _glyphsDB.IsDerivedFromParent();
		if ( fieldName == "heroes" )
			return _heroes.IsDerivedFromParent();
		if ( fieldName == "heroesLevelups" )
			return _heroesLevelups.IsDerivedFromParent();
		if ( fieldName == "impulsiveBuffs" )
			return _impulsiveBuffs.IsDerivedFromParent();
		if ( fieldName == "defaultFormulas" )
			return _defaultFormulas.IsDerivedFromParent();
		if ( fieldName == "mapList" )
			return _mapList.IsDerivedFromParent();
		if ( fieldName == "guildBuffsCollection" )
			return _guildBuffsCollection.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[Custom("DBServer")]
[DbRoot]
[UseTypeName("ROOT")]
public class SessionRoot : DBResource
{
	private UndoRedoDBPtr<SessionRoot> ___parent;
	[HideInOutliner]
	public new DBPtr<SessionRoot> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<SessionUIRoot> _uiRoot;
	private UndoRedoDBPtr<SessionLogicRoot> _logicRoot;
	private UndoRedoDBPtr<SessionVisualRoot> _visualRoot;
	private UndoRedoDBPtr<SessionAudioRoot> _audioRoot;
	private UndoRedoDBPtr<RollSettings> _rollSettings;
	private UndoRedoDBPtr<SessionMessages> _sessionMessages;

	public DBPtr<SessionUIRoot> uiRoot { get { return _uiRoot.Get(); } set { _uiRoot.Set( value ); } }

	public DBPtr<SessionLogicRoot> logicRoot { get { return _logicRoot.Get(); } set { _logicRoot.Set( value ); } }

	public DBPtr<SessionVisualRoot> visualRoot { get { return _visualRoot.Get(); } set { _visualRoot.Set( value ); } }

	public DBPtr<SessionAudioRoot> audioRoot { get { return _audioRoot.Get(); } set { _audioRoot.Set( value ); } }

	public DBPtr<RollSettings> rollSettings { get { return _rollSettings.Get(); } set { _rollSettings.Set( value ); } }

	public DBPtr<SessionMessages> sessionMessages { get { return _sessionMessages.Get(); } set { _sessionMessages.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<SessionRoot>(owner);
		_uiRoot = new UndoRedoDBPtr<SessionUIRoot>( owner );
		_logicRoot = new UndoRedoDBPtr<SessionLogicRoot>( owner );
		_visualRoot = new UndoRedoDBPtr<SessionVisualRoot>( owner );
		_audioRoot = new UndoRedoDBPtr<SessionAudioRoot>( owner );
		_rollSettings = new UndoRedoDBPtr<RollSettings>( owner );
		_sessionMessages = new UndoRedoDBPtr<SessionMessages>( owner );
		___parent.Changed += FireChangedEvent;
		_uiRoot.Changed += FireChangedEvent;
		_logicRoot.Changed += FireChangedEvent;
		_visualRoot.Changed += FireChangedEvent;
		_audioRoot.Changed += FireChangedEvent;
		_rollSettings.Changed += FireChangedEvent;
		_sessionMessages.Changed += FireChangedEvent;
	}

	public SessionRoot()
	{
		Initialize( this );
	}
	private void AssignSelf( SessionRoot source )
	{
		DataBase.UndoRedoManager.Start( "Assign for SessionRoot" );
		uiRoot = source.uiRoot;
		logicRoot = source.logicRoot;
		visualRoot = source.visualRoot;
		audioRoot = source.audioRoot;
		rollSettings = source.rollSettings;
		sessionMessages = source.sessionMessages;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		SessionRoot source = _source as SessionRoot;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for SessionRoot" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		SessionRoot newParent = rawParent == null ? null : rawParent.Get<SessionRoot>();
		if ( newParent == null && _newParent is SessionRoot )
			newParent = _newParent as SessionRoot;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_uiRoot.SetParent( newParent == null ? null : newParent._uiRoot );
		_logicRoot.SetParent( newParent == null ? null : newParent._logicRoot );
		_visualRoot.SetParent( newParent == null ? null : newParent._visualRoot );
		_audioRoot.SetParent( newParent == null ? null : newParent._audioRoot );
		_rollSettings.SetParent( newParent == null ? null : newParent._rollSettings );
		_sessionMessages.SetParent( newParent == null ? null : newParent._sessionMessages );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_uiRoot.Reset();
		_logicRoot.Reset();
		_visualRoot.Reset();
		_audioRoot.Reset();
		_rollSettings.Reset();
		_sessionMessages.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_uiRoot.IsDerivedFromParent()
			&& _logicRoot.IsDerivedFromParent()
			&& _visualRoot.IsDerivedFromParent()
			&& _audioRoot.IsDerivedFromParent()
			&& _rollSettings.IsDerivedFromParent()
			&& _sessionMessages.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "uiRoot" )
			_uiRoot.Reset();
		else if ( fieldName == "logicRoot" )
			_logicRoot.Reset();
		else if ( fieldName == "visualRoot" )
			_visualRoot.Reset();
		else if ( fieldName == "audioRoot" )
			_audioRoot.Reset();
		else if ( fieldName == "rollSettings" )
			_rollSettings.Reset();
		else if ( fieldName == "sessionMessages" )
			_sessionMessages.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "uiRoot" )
			return _uiRoot.IsDerivedFromParent();
		if ( fieldName == "logicRoot" )
			return _logicRoot.IsDerivedFromParent();
		if ( fieldName == "visualRoot" )
			return _visualRoot.IsDerivedFromParent();
		if ( fieldName == "audioRoot" )
			return _audioRoot.IsDerivedFromParent();
		if ( fieldName == "rollSettings" )
			return _rollSettings.IsDerivedFromParent();
		if ( fieldName == "sessionMessages" )
			return _sessionMessages.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes

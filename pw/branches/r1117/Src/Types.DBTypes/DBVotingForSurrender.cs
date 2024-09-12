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
public enum VFSMessageType
{
	ShowMessageToPlayer = 0,
	ShowMessageToCommand = 1,
	ShowMessageToAll = 2,
};

public enum VFSUserMessages
{
	CantStartAnotherInProgress = 0,
	CantStartCooldown = 1,
	PlayerStartVoting = 2,
	CantMakeDecisionIsntInProgress = 3,
	CantMakeDecisionAlreadyVoted = 4,
	CommandAcceptSurrender = 5,
	CommandDeclineSurrender = 6,
};

public class VFSMessageDesc : libdb.ICompositeDBValue, libdb.IChangeable
{
	private DBResource owner = null;
	public DBResource GetOwner() { return owner; }

	private VFSMessageDesc __parent = null;

	public event EventHandler Changed;

	protected void FireChangedEvent( object sender, EventArgs e )
	{
		if ( Changed != null ) Changed( sender, e );
	}

	private UndoRedo<VFSMessageType> _type;
	private TextRef _text;

	public VFSMessageType type { get { return _type.Get(); } set { _type.Set( value ); } }

	public TextRef text { get { return _text; } set { _text.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		_type = new UndoRedo<VFSMessageType>( owner, VFSMessageType.ShowMessageToAll );
		_text = new TextRef( owner, new TextRef() );
		_type.Changed += FireChangedEvent;
		_text.Changed += FireChangedEvent;
	}

	public VFSMessageDesc()
	{
		Initialize( GetOwner() );
	}

	public VFSMessageDesc( DBResource owner )
	{
		this.owner = owner;
		Initialize( GetOwner() );
	}

	public VFSMessageDesc( DBResource owner, VFSMessageDesc source )
		: this(owner, source, true){}

	protected VFSMessageDesc( DBResource owner, VFSMessageDesc source, bool fireEvent )
	{
		_type = new UndoRedo<VFSMessageType>( owner, source.type );
		_text = new TextRef( owner, source.text );
		_type.Changed += FireChangedEvent;
		_text.Changed += FireChangedEvent;
		this.owner = owner;
		if(fireEvent)
			FireChangedEvent( this, EventArgs.Empty );
	}

	public virtual void Assign( object _source )
	{
		VFSMessageDesc source = _source as VFSMessageDesc;
		if ( null == source || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for VFSMessageDesc" );
		type = source.type;
		text = source.text;
		DataBase.UndoRedoManager.Commit();
	}

	public virtual void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		VFSMessageDesc newParent = _newParent as VFSMessageDesc;
		if ( newParent == null && this.__parent != null )
			Assign( this );
		this.__parent = newParent;

		_type.SetParent( newParent == null ? null : newParent._type );
		_text.SetParent( newParent == null ? null : newParent._text );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public virtual void Reset()
	{
		_type.Reset();
		_text.Reset();
	}

	public virtual bool IsDerivedFromParent()
	{
		if ( __parent == null )
			return true;
		return 
			_type.IsDerivedFromParent()
			&& _text.IsDerivedFromParent()
			;
	}

	public virtual void ResetField( string fieldName )
	{
		if ( fieldName == "type" )
			_type.Reset();
		else if ( fieldName == "text" )
			_text.Reset();
		else
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
	}

	public virtual bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null;
		if ( fieldName == "type" )
			return _type.IsDerivedFromParent();
		if ( fieldName == "text" )
			return _text.IsDerivedFromParent();
		else
		{
			Log.AlwaysAssert( "Field with name {0} not found", fieldName );
			return true;
		}
	}
	public virtual bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
public class VotingForSurrender : DBResource
{
	private UndoRedoDBPtr<VotingForSurrender> ___parent;
	[HideInOutliner]
	public new DBPtr<VotingForSurrender> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedoDBPtr<VotingForSurrenderPerMission> _defaultMissionSettings;
	private UndoRedo<float> _delayBeforeVotingComplete;
	private UndoRedo<float> _votingDuration;
	private UndoRedo<int> _warforOpenedRadius;
	private UndoRedoAssignableList<VFSMessageDesc> _messages;

	[Description( "Настройки по-умолчанию для миссии. Будут использоваться если такие настройки не указаны в данных миссии" )]
	public DBPtr<VotingForSurrenderPerMission> defaultMissionSettings { get { return _defaultMissionSettings.Get(); } set { _defaultMissionSettings.Set( value ); } }

	[Description( "Задержка после успешного голосования перед капитуляцией" )]
	public float delayBeforeVotingComplete { get { return _delayBeforeVotingComplete.Get(); } set { _delayBeforeVotingComplete.Set( value ); } }

	[Description( "Продолжительность голосования" )]
	public float votingDuration { get { return _votingDuration.Get(); } set { _votingDuration.Set( value ); } }

	[Description( "Радиус области под варфогом, которая открывается после капитуляции" )]
	public int warforOpenedRadius { get { return _warforOpenedRadius.Get(); } set { _warforOpenedRadius.Set( value ); } }

	[Description( "Сообщения пользователю" )]
	[EnumArray(typeof(VFSUserMessages))]
	public libdb.IChangeableList<VFSMessageDesc> messages { get { return _messages; } set { _messages.Assign( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<VotingForSurrender>(owner);
		_defaultMissionSettings = new UndoRedoDBPtr<VotingForSurrenderPerMission>( owner );
		_delayBeforeVotingComplete = new UndoRedo<float>( owner, 5.0f );
		_votingDuration = new UndoRedo<float>( owner, 60.0f );
		_warforOpenedRadius = new UndoRedo<int>( owner, 80 );
		_messages = new UndoRedoAssignableList<VFSMessageDesc>( owner, typeof( VFSUserMessages ) );
		___parent.Changed += FireChangedEvent;
		_defaultMissionSettings.Changed += FireChangedEvent;
		_delayBeforeVotingComplete.Changed += FireChangedEvent;
		_votingDuration.Changed += FireChangedEvent;
		_warforOpenedRadius.Changed += FireChangedEvent;
		_messages.Changed += FireChangedEvent;
	}

	public VotingForSurrender()
	{
		Initialize( this );
	}
	private void AssignSelf( VotingForSurrender source )
	{
		DataBase.UndoRedoManager.Start( "Assign for VotingForSurrender" );
		defaultMissionSettings = source.defaultMissionSettings;
		delayBeforeVotingComplete = source.delayBeforeVotingComplete;
		votingDuration = source.votingDuration;
		warforOpenedRadius = source.warforOpenedRadius;
		messages = source.messages;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		VotingForSurrender source = _source as VotingForSurrender;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for VotingForSurrender" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		VotingForSurrender newParent = rawParent == null ? null : rawParent.Get<VotingForSurrender>();
		if ( newParent == null && _newParent is VotingForSurrender )
			newParent = _newParent as VotingForSurrender;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_defaultMissionSettings.SetParent( newParent == null ? null : newParent._defaultMissionSettings );
		_delayBeforeVotingComplete.SetParent( newParent == null ? null : newParent._delayBeforeVotingComplete );
		_votingDuration.SetParent( newParent == null ? null : newParent._votingDuration );
		_warforOpenedRadius.SetParent( newParent == null ? null : newParent._warforOpenedRadius );
		_messages.SetParent( newParent == null ? null : newParent._messages );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_defaultMissionSettings.Reset();
		_delayBeforeVotingComplete.Reset();
		_votingDuration.Reset();
		_warforOpenedRadius.Reset();
		_messages.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_defaultMissionSettings.IsDerivedFromParent()
			&& _delayBeforeVotingComplete.IsDerivedFromParent()
			&& _votingDuration.IsDerivedFromParent()
			&& _warforOpenedRadius.IsDerivedFromParent()
			&& _messages.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "defaultMissionSettings" )
			_defaultMissionSettings.Reset();
		else if ( fieldName == "delayBeforeVotingComplete" )
			_delayBeforeVotingComplete.Reset();
		else if ( fieldName == "votingDuration" )
			_votingDuration.Reset();
		else if ( fieldName == "warforOpenedRadius" )
			_warforOpenedRadius.Reset();
		else if ( fieldName == "messages" )
			_messages.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "defaultMissionSettings" )
			return _defaultMissionSettings.IsDerivedFromParent();
		if ( fieldName == "delayBeforeVotingComplete" )
			return _delayBeforeVotingComplete.IsDerivedFromParent();
		if ( fieldName == "votingDuration" )
			return _votingDuration.IsDerivedFromParent();
		if ( fieldName == "warforOpenedRadius" )
			return _warforOpenedRadius.IsDerivedFromParent();
		if ( fieldName == "messages" )
			return _messages.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

[DBVersion(1)]
public class VotingForSurrenderPerMission : DBResource
{
	private UndoRedoDBPtr<VotingForSurrenderPerMission> ___parent;
	[HideInOutliner]
	public new DBPtr<VotingForSurrenderPerMission> __parent { get { return ___parent.Get(); }
		set { if ( GeneratedCodeUtilities.CanSetParent( this, value ) ) { SetParent( value ); } } }

	private UndoRedo<float> _cooldownAfterStart;
	private UndoRedo<float> _cooldownAfterPrevisionVoting;
	private UndoRedo<int> _maxUsersForFightIgnored;
	private UndoRedo<float> _timeDisconnectedPlayersVoteForFight;

	[Description( "Минимальная задержка перед первым голосованием" )]
	public float cooldownAfterStart { get { return _cooldownAfterStart.Get(); } set { _cooldownAfterStart.Set( value ); } }

	[Description( "Минимальная задержка после завершившегося голосования перед началом следующего" )]
	public float cooldownAfterPrevisionVoting { get { return _cooldownAfterPrevisionVoting.Get(); } set { _cooldownAfterPrevisionVoting.Set( value ); } }

	[Description( "Минимальное количество пользователей, которые могут проголосовать против при общем положительном итоге" )]
	public int maxUsersForFightIgnored { get { return _maxUsersForFightIgnored.Get(); } set { _maxUsersForFightIgnored.Set( value ); } }

	[Description( "Время (в секундах), в течение которого отключенные игроки (не ливеры!) автоматически голосуют ПРОТИВ" )]
	public float timeDisconnectedPlayersVoteForFight { get { return _timeDisconnectedPlayersVoteForFight.Get(); } set { _timeDisconnectedPlayersVoteForFight.Set( value ); } }

	private void Initialize( DBResource owner )
	{
		___parent = new UndoRedoDBPtr<VotingForSurrenderPerMission>(owner);
		_cooldownAfterStart = new UndoRedo<float>( owner, 60.0f );
		_cooldownAfterPrevisionVoting = new UndoRedo<float>( owner, 15.0f );
		_maxUsersForFightIgnored = new UndoRedo<int>( owner, 1 );
		_timeDisconnectedPlayersVoteForFight = new UndoRedo<float>( owner, 180.0f );
		___parent.Changed += FireChangedEvent;
		_cooldownAfterStart.Changed += FireChangedEvent;
		_cooldownAfterPrevisionVoting.Changed += FireChangedEvent;
		_maxUsersForFightIgnored.Changed += FireChangedEvent;
		_timeDisconnectedPlayersVoteForFight.Changed += FireChangedEvent;
	}

	public VotingForSurrenderPerMission()
	{
		Initialize( this );
	}
	private void AssignSelf( VotingForSurrenderPerMission source )
	{
		DataBase.UndoRedoManager.Start( "Assign for VotingForSurrenderPerMission" );
		cooldownAfterStart = source.cooldownAfterStart;
		cooldownAfterPrevisionVoting = source.cooldownAfterPrevisionVoting;
		maxUsersForFightIgnored = source.maxUsersForFightIgnored;
		timeDisconnectedPlayersVoteForFight = source.timeDisconnectedPlayersVoteForFight;
		DataBase.UndoRedoManager.Commit();
	}

	public override void Assign( object _source )
	{
		VotingForSurrenderPerMission source = _source as VotingForSurrenderPerMission;
		if ( source == null || this == source )
			return;
		DataBase.UndoRedoManager.Start( "Assign for VotingForSurrenderPerMission" );
		AssignSelf( source );
		DataBase.UndoRedoManager.Commit();
	}

	public override void SetParent( object _newParent )
	{
		DataBase.UndoRedoManager.SerializeSuspend();
		DBPtrBase rawParent = _newParent as DBPtrBase;
		VotingForSurrenderPerMission newParent = rawParent == null ? null : rawParent.Get<VotingForSurrenderPerMission>();
		if ( newParent == null && _newParent is VotingForSurrenderPerMission )
			newParent = _newParent as VotingForSurrenderPerMission;
		if ( newParent == null && this.__parent.IsValid )
			AssignSelf( this );
		this.__parent.Set( newParent == null ? DBID.Empty : newParent.DBId );
		base.SetParent( newParent );

		_cooldownAfterStart.SetParent( newParent == null ? null : newParent._cooldownAfterStart );
		_cooldownAfterPrevisionVoting.SetParent( newParent == null ? null : newParent._cooldownAfterPrevisionVoting );
		_maxUsersForFightIgnored.SetParent( newParent == null ? null : newParent._maxUsersForFightIgnored );
		_timeDisconnectedPlayersVoteForFight.SetParent( newParent == null ? null : newParent._timeDisconnectedPlayersVoteForFight );
		DataBase.UndoRedoManager.SerializeResume();
	}

	public override void Reset()
	{
		_cooldownAfterStart.Reset();
		_cooldownAfterPrevisionVoting.Reset();
		_maxUsersForFightIgnored.Reset();
		_timeDisconnectedPlayersVoteForFight.Reset();
		base.Reset();
	}

	public override bool IsDerivedFromParent()
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		return 
			_cooldownAfterStart.IsDerivedFromParent()
			&& _cooldownAfterPrevisionVoting.IsDerivedFromParent()
			&& _maxUsersForFightIgnored.IsDerivedFromParent()
			&& _timeDisconnectedPlayersVoteForFight.IsDerivedFromParent()
			&& base.IsDerivedFromParent();
	}

	public override void ResetField( string fieldName )
	{
		if ( fieldName == "cooldownAfterStart" )
			_cooldownAfterStart.Reset();
		else if ( fieldName == "cooldownAfterPrevisionVoting" )
			_cooldownAfterPrevisionVoting.Reset();
		else if ( fieldName == "maxUsersForFightIgnored" )
			_maxUsersForFightIgnored.Reset();
		else if ( fieldName == "timeDisconnectedPlayersVoteForFight" )
			_timeDisconnectedPlayersVoteForFight.Reset();
		else
			base.ResetField( fieldName );
	}

	public override bool IsFieldDerivedFromParent( string fieldName )
	{
		if ( __parent == null || __parent.Get() == null )
			return true;
		if ( fieldName == "__parent" )
			return __parent == null || __parent.Get() == null;
		if ( fieldName == "cooldownAfterStart" )
			return _cooldownAfterStart.IsDerivedFromParent();
		if ( fieldName == "cooldownAfterPrevisionVoting" )
			return _cooldownAfterPrevisionVoting.IsDerivedFromParent();
		if ( fieldName == "maxUsersForFightIgnored" )
			return _maxUsersForFightIgnored.IsDerivedFromParent();
		if ( fieldName == "timeDisconnectedPlayersVoteForFight" )
			return _timeDisconnectedPlayersVoteForFight.IsDerivedFromParent();
		else
			return base.IsFieldDerivedFromParent( fieldName );
	}
	public override bool HasParent()
	{
		return __parent != null;
	}

}

}; // namespace DBTypes

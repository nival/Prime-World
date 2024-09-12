using System;
using System.Collections.Generic;
using System.Threading;

namespace libdb.UndoRedo
{
	public class UndoRedoManager
	{
		private List<UndoRedoCommand> history = new List<UndoRedoCommand>();
		private int currentHistoryPosition = -1;
		private int commandsStarted = 0;

		private UndoRedoCommand currentCommand = null;

		public bool CanUndo { get { return currentHistoryPosition >= 0; } }
		public bool CanRedo { get { return currentHistoryPosition < history.Count - 1; } }

		private bool isUndo = false;
		public bool IsUndo { get { return isUndo; } }

		private bool isRedo = false;
		public bool IsRedo { get { return isRedo; } }
		
		public delegate void UndoRedoEventHandler();
		public event UndoRedoEventHandler UndoRedoEvent = null;
		
		public void Undo()
		{
			if ( CanUndo )
			{
				UndoRedoCommand command = history[currentHistoryPosition--];
				isUndo = true;
				command.Undo();
				isUndo = false;
				if ( UndoRedoEvent != null )
					UndoRedoEvent();
			}
		}

		public void Redo()
		{
			if ( CanRedo )
			{
				UndoRedoCommand command = history[++currentHistoryPosition];
				isRedo = true;
				command.Redo();
				isRedo = false;
				if ( UndoRedoEvent != null )
					UndoRedoEvent();
			}
		}

		// The same LocalDataStoreSlot object can be used across all threads.
		private readonly LocalDataStoreSlot serializeSlot = Thread.GetNamedDataSlot( "serializeSlot" );

		// This property has a separate value on each thread.
		private int SerializeLevel
		{
			get
			{
				object data = Thread.GetData( serializeSlot );
				return data == null ? 0 : (int)data;    // null == uninitialized
			}
			set { Thread.SetData( serializeSlot, value ); }
		}
   
		public void SerializeSuspend()
    {
      ++SerializeLevel;
    }

    public void SerializeResume()
    {
      --SerializeLevel;
    }

		public void Start( string commandCaption )
		{
			if ( SerializeLevel > 0 )
        return;
			if ( !IsCommandStarted )
				currentCommand = new UndoRedoCommand( commandCaption );
			++commandsStarted;
		  TraceStart();
		}

		public void AddOperation( IUndoRedoOperation operation )
		{
      if ( IsUndo || IsRedo )
				return;

			operation.Redo();

			if ( SerializeLevel > 0 )
        return;

			if ( operation.GetOwner() == null || !operation.GetOwner().DBId.IsEmpty )
			{
				bool oneOperationCommand = !IsCommandStarted;
				if ( oneOperationCommand )
					Start( operation.DefaultCaption );

				currentCommand.AddOperation( operation );

				if ( oneOperationCommand )
					Commit();
			}
		}

		public void Commit()
		{
			if ( SerializeLevel > 0 )
        return;
      --commandsStarted;

      TraceEnd();
      
      if ( IsCommandStarted || currentCommand == null )
				return;

      if ( !currentCommand.IsEmpty )
      {
				if ( SerializeLevel == 0 )
        {
          int count = history.Count - currentHistoryPosition - 1;
          history.RemoveRange( ++currentHistoryPosition, count );
          history.Add( currentCommand );
          TruncateHistory();
        }
        currentCommand.Commit();
        if ( UndoRedoEvent != null )
          UndoRedoEvent();
      }

      currentCommand = null;
    }

		public void Cancel()
		{
			if ( SerializeLevel > 0 )
				return;

      TraceEnd();
     
      if ( commandsStarted > 1 )
      {
        --commandsStarted; 
        return;
      }
			currentCommand.Undo();
			commandsStarted = 0;
			currentCommand = null;
		}

		/// <summary>
		/// Clears all history. It does not affect current data but history only. 
		/// It is useful after any data initialization if you want forbid user to undo this initialization.
		/// </summary>
		public void Clear()
		{
			currentCommand = null;
			currentHistoryPosition = -1;
			history.Clear();
    }

    public bool IsCommandStarted { get { return commandsStarted > 0; } }

		private int maxHistorySize = 0;

		public int MaxHistorySize
		{
			get { return maxHistorySize; }
			set
			{
				if ( IsCommandStarted )
					throw new InvalidOperationException( "Max size may not be set while command is run." );
				if ( value < 0 )
					throw new ArgumentOutOfRangeException( "Value may not be less than 0" );
				maxHistorySize = value;
				TruncateHistory();
			}
		}

		private void TruncateHistory()
		{
			if ( maxHistorySize > 0 && history.Count > maxHistorySize )
			{
				int count = history.Count - maxHistorySize;
				history.RemoveRange( 0, count );
				currentHistoryPosition -= count;
			}
		}

    public List<string> GetOperationHistory( int maxDepth )
    {
      List<string> result = new List<string>();

      int depth = maxDepth > 0 ? maxDepth : history.Count;
      for ( int i = currentHistoryPosition; i >= 0 && depth > 0; --i, --depth )
        result.Add( history[i].Caption );

      return result;
    }

    #region Commands Trace

	  private const int MAX_TRACE_ITEMS = 500;

    private Queue<string> commandsTrace = new Queue<string>( MAX_TRACE_ITEMS );

    private void TraceStart()
    {
      if( commandsTrace.Count == MAX_TRACE_ITEMS )
        commandsTrace.Dequeue();
      
      commandsTrace.Enqueue( string.Format( "start: {0}", currentCommand.Caption ) );
    }

    private void TraceEnd()
    {
      if( commandsTrace.Count == MAX_TRACE_ITEMS )
        commandsTrace.Dequeue();

      commandsTrace.Enqueue( string.Format( "commit: {0}", currentCommand != null ? currentCommand.Caption : "" ) );
    }
    
    /// <summary>
    /// For test purposes only. Don't use this method for logic. It's removed after testing.
    /// </summary>
    public string[] GetCommandsTrace()
    {
      return commandsTrace.ToArray();
    }

    public void ClearCommandsTrace()
    {
      commandsTrace.Clear();
    }

    #endregion
  }
}

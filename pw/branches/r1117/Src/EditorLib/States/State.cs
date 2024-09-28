using libdb.DB;

namespace EditorLib.States
{
	public abstract class State
	{
		private IStateMachine stateMachine;

		protected internal IStateMachine StateMachine
		{
			get { return stateMachine; }
			internal set
			{
				if ( ReferenceEquals( stateMachine, value ) )
					return;

				if ( !ReferenceEquals( stateMachine, null ) )
				{
          stateMachine = null;
					OnDeactivated();
				}
				if ( !ReferenceEquals( value, null ) )
				{
					OnActivated();
					stateMachine = value;
				}
			}
		}

		public abstract void OnUpdate();

		protected virtual void OnActivated()
		{
			// Do nothing.
		}

		protected virtual void OnDeactivated()
		{
			// Do nothing.
		}


    #region DBOperations

    bool isDBOperationStarted = false;

    protected void StartDBOperation(string _caption)
    {
      if( isDBOperationStarted )
        return;

      DataBase.UndoRedoManager.Start( _caption );
      isDBOperationStarted = true;
    }

    protected void LeaveDBOperation()
    {
      if( !isDBOperationStarted )
        return;

      DataBase.UndoRedoManager.Commit();
      isDBOperationStarted = false;
    }

    #endregion
	}
}

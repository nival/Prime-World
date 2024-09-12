namespace EditorLib.States
{
	public sealed class StateMachine : IStateMachine
	{
		private sealed class NullState : State
		{
			public override void OnUpdate()
			{
				// Do nothing.
			}
		}

		private State currentState;

		public StateMachine()
			: this ( null )
		{
		}

		public StateMachine( State initialState )
		{
			currentState = initialState ?? new NullState();
			currentState.StateMachine = this;
		}

		private State desiredState;

		public State State
		{
      get { return currentState; }
      set
			{
				desiredState = value;
				State stateToDeactivate = currentState;
				currentState = null;
				if ( !ReferenceEquals( stateToDeactivate, null ) )
					stateToDeactivate.StateMachine = null;
				if ( !ReferenceEquals( desiredState, currentState ) )
				{
					currentState = desiredState ?? new NullState();
					currentState.StateMachine = this;
				}
			}
		}

		public void Update()
		{
      if( currentState != null )
  			currentState.OnUpdate();
		}
	}
}

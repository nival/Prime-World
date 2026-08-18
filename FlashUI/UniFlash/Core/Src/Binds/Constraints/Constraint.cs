using System;

namespace Flash
{
	public abstract class ConstraintAttribute : Attribute
	{
		public abstract bool Validate(MovieClip target);
	  public abstract string LastValidationError { get; }
	}
}


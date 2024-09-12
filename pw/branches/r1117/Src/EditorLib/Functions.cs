namespace EditorLib
{
	public delegate bool Predicate();
	public delegate bool Predicate<T0>( T0 arg0 );
	public delegate bool Predicate<T0, T1>( T0 arg0, T1 arg1 );
	public delegate bool Predicate<T0, T1, T2>( T0 arg0, T1 arg1, T2 arg2 );
	public delegate bool Predicate<T0, T1, T2, T3>( T0 arg0, T1 arg1, T2 arg2, T3 arg3 );
	public delegate bool Predicate<T0, T1, T2, T3, T4>( T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4 );
	public delegate bool Predicate<T0, T1, T2, T3, T4, T5>( T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5 );
	public delegate bool Predicate<T0, T1, T2, T3, T4, T5, T6>( T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6 );
	public delegate bool Predicate<T0, T1, T2, T3, T4, T5, T6, T7>( T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6, T7 arg7 );
	public delegate bool Predicate<T0, T1, T2, T3, T4, T5, T6, T7, T8>( T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6, T7 arg7, T8 arg8 );
	public delegate bool Predicate<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>( T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6, T7 arg7, T8 arg8, T9 arg9 );

	public delegate void Operation();
	public delegate void Operation<T0>( T0 arg0 );
	public delegate void Operation<T0, T1>( T0 arg0, T1 arg1 );
	public delegate void Operation<T0, T1, T2>( T0 arg0, T1 arg1, T2 arg2 );
	public delegate void Operation<T0, T1, T2, T3>( T0 arg0, T1 arg1, T2 arg2, T3 arg3 );
	public delegate void Operation<T0, T1, T2, T3, T4>( T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4 );
	public delegate void Operation<T0, T1, T2, T3, T4, T5>( T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5 );
	public delegate void Operation<T0, T1, T2, T3, T4, T5, T6>( T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6 );
	public delegate void Operation<T0, T1, T2, T3, T4, T5, T6, T7>( T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6, T7 arg7 );
	public delegate void Operation<T0, T1, T2, T3, T4, T5, T6, T7, T8>( T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6, T7 arg7, T8 arg8 );
	public delegate void Operation<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>( T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6, T7 arg7, T8 arg8, T9 arg9 );

	public delegate TResult Function<TResult>();
	public delegate TResult Function<TResult, T0>( T0 arg0 );
	public delegate TResult Function<TResult, T0, T1>( T0 arg0, T1 arg1 );
	public delegate TResult Function<TResult, T0, T1, T2>( T0 arg0, T1 arg1, T2 arg2 );
	public delegate TResult Function<TResult, T0, T1, T2, T3>( T0 arg0, T1 arg1, T2 arg2, T3 arg3 );
	public delegate TResult Function<TResult, T0, T1, T2, T3, T4>( T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4 );
	public delegate TResult Function<TResult, T0, T1, T2, T3, T4, T5>( T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5 );
	public delegate TResult Function<TResult, T0, T1, T2, T3, T4, T5, T6>( T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6 );
	public delegate TResult Function<TResult, T0, T1, T2, T3, T4, T5, T6, T7>( T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6, T7 arg7 );
	public delegate TResult Function<TResult, T0, T1, T2, T3, T4, T5, T6, T7, T8>( T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6, T7 arg7, T8 arg8 );
	public delegate TResult Function<TResult, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>( T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5, T6 arg6, T7 arg7, T8 arg8, T9 arg9 );

	public sealed class Tuple<T0>
	{
		public Tuple( T0 arg0 ) { Arg0 = arg0; }
		public T0 Arg0 { get; private set; }
	}

	public sealed class Tuple<T0, T1>
	{
		public Tuple( T0 arg0, T1 arg1 ) { Arg0 = arg0; Arg1 = arg1; }
		public T0 Arg0 { get; private set; }
		public T1 Arg1 { get; private set; }
	}

	public sealed class Tuple<T0, T1, T2>
	{
		public Tuple( T0 arg0, T1 arg1, T2 arg2 ) { Arg0 = arg0; Arg1 = arg1; Arg2 = arg2; }
		public T0 Arg0 { get; private set; }
		public T1 Arg1 { get; private set; }
		public T2 Arg2 { get; private set; }
	}

	public sealed class Tuple<T0, T1, T2, T3>
	{
		public Tuple( T0 arg0, T1 arg1, T2 arg2, T3 arg3 ) { Arg0 = arg0; Arg1 = arg1; Arg2 = arg2; Arg3 = arg3; }
		public T0 Arg0 { get; private set; }
		public T1 Arg1 { get; private set; }
		public T2 Arg2 { get; private set; }
		public T3 Arg3 { get; private set; }
	}
}

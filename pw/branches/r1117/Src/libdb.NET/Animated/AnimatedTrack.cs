using libdb.DB;
using libdb.UndoRedo;

namespace libdb.Animated
{
  public interface IKeyValue<T>
  {
    float Key { get; }
		T Value { get; }
  }

  public interface IAnimatedTrack
  {
    int FindKey( float key );
    bool DeleteKey( int index );
    float GetKey( int index );
    void SetKey( int index, float key );

    int AddObjectKey( float key, object value );
    object GetObjectValue( int index );
    void SetObjectValue( int index, object value );

    int KeysCount { get; }
    float Length { get; }

    object Serialize();
    void Deserialize( object storage );
  }

  public sealed class AnimatedTrack<T> : IAnimatedTrack
	{
		#region Nested Types

		public interface ITrackCallback
		{
			void BeforeChanged();
			void Changed();
			AnimatedTrack<T> GetParentTrack();
		}

		private class KeyValue : IKeyValue<T>
		{
			private readonly DBResource owner;

			private float key = 0.0f;
			private T value = default( T );

			public KeyValue( DBResource _owner, T _value ) 
				: this(_owner, 0.0f, _value)
			{
			}

			public KeyValue( DBResource _owner, float _key, T _value )
			{
				owner = _owner;
				key = _key;
				value = _value;
			}

			public float Key
			{
				get { return key; }
				set
				{
					if(owner != null)
					{
						DataBase.AddOperation( new ChangeKeyValueOperation( this, value, Value ) );	
					}
					else
					{
						SetKeyInternal(value);
					}
					
				}
			}

			public T Value
			{
				get { return value; }
				set
				{
					if(owner != null)
					{
						DataBase.AddOperation( new ChangeKeyValueOperation( this, Key, value ) );	
					}
					else
					{
						SetValueInternal(value);
					}
					
				}
			}

			public bool IsEqual( KeyValue other )
			{
				return key == other.key && value.Equals( other.value );
			}

			internal void SetKeyInternal( float _key )
			{
				key = _key;
			}

			internal void SetValueInternal( T _value )
			{
				value = _value;
			}

			public DBResource Owner { get { return owner; } }
		}

		public class SerializaedKeyValue
		{
			public float Key = 0.0f;
			public T Value = default( T );

			public SerializaedKeyValue() { }
			public SerializaedKeyValue( IKeyValue<T> _keyValue )
			{
				Key = _keyValue.Key;
				Value = _keyValue.Value;
			}
		}

		private class ChangeKeyValueOperation : IUndoRedoOperation
		{
			private KeyValue item;
			private float keyBackup;
			private T valueBackup;

			public ChangeKeyValueOperation( KeyValue _item, float _key, T _value )
			{
				item = _item;
				keyBackup = _key;
				valueBackup = _value;
			}

			public void Undo()
			{
				RestoreItem();
			}

			public void Redo()
			{
				RestoreItem();
			}

			public string DefaultCaption
			{
				get { return "Change Animated KeyValue"; }
			}

			public DBResource GetOwner()
			{
				return item.Owner;
			}

			private void RestoreItem()
			{
				float oldKey = item.Key;
				T oldValue = item.Value;

				item.SetKeyInternal( keyBackup );
				item.SetValueInternal( valueBackup );

				keyBackup = oldKey;
				valueBackup = oldValue;
			}
		}

		#endregion

    private readonly ITrackCallback callback = null;

		private readonly UndoRedoList<KeyValue> values;

  	private readonly DBResource owner;

    public AnimatedTrack( DBResource _owner, T _value, ITrackCallback _callback )
    {
    	owner = _owner;
			callback = _callback;

			values = new UndoRedoList<KeyValue>( _owner ) 
			{
				new KeyValue(owner, _value)
			}; 
    }

    private int FindKeyRight( float key )
    {
      AnimatedTrack<T> parent = callback.GetParentTrack();
      
      if( parent != null )
        return parent.FindKeyRight( key );

      if( values.Count == 0 || key > values[values.Count - 1].Key )
        return -1;

      for( int i = values.Count - 1; i >= 1; --i )
      {
        if( key > values[i - 1].Key )
          return i;
      }

      return 0;
    }

    public int FindKey( float key )
    {
      AnimatedTrack<T> parent = callback.GetParentTrack();
      
      if( parent != null )
        return parent.FindKey( key );

      if( values.Count == 0 || key < values[0].Key )
        return -1;

      for( int i = 0; i < values.Count - 1; ++i )
      {
        if( key < values[i + 1].Key )
          return i;
      }

      return values.Count - 1;
    }

    public int AddKey( float key, T value )
    {
      callback.BeforeChanged();

      int index = FindKeyRight( key );
      if( index == -1 )
      {
        index = values.Count;
				values.Add( new KeyValue( owner, key, value ) );
      }
      else
      {
				values.Insert( index, new KeyValue( owner, key, value ) );
      }

      callback.Changed();
      return index;
    }

    public int AddObjectKey( float key, object value )
    {
      return AddKey( key, (T)value );
    }

    public bool DeleteKey( int index )
    {
      callback.BeforeChanged();

      if( index <= 0 || index > values.Count - 1 )//|| values.Count == 1 )
      {
				return false;
      }

      values.RemoveAt( index );
      if( values.Count == 1 )
        values[0].Key = 0;

      callback.Changed();
      return true;
    }

    public void Clear()
    {
      callback.BeforeChanged();
      T value = GetValue( 0 );
      values.Clear();
			values.Add( new KeyValue( owner, value ) );
      callback.Changed();
    }

    public float GetKey( int index )
    {
      AnimatedTrack<T> parent = callback.GetParentTrack();
      if( parent != null )
        return parent.GetKey( index );

      return values[index].Key;
    }

    public T GetValue( int index )
    {
      AnimatedTrack<T> parent = callback.GetParentTrack();
      if( parent != null )
        return parent.GetValue( index );

      return values[index].Value;
    }

    public object GetObjectValue( int index )
    {
      return GetValue( index );
    }

    public void SetKey( int index, float key )
    {
      callback.BeforeChanged();
      values[index].Key = key;		
      callback.Changed();
    }

    public void SetValue( int index, T value )
    {
      callback.BeforeChanged();
      values[index].Value = value;
      callback.Changed();
    }

    public void SetObjectValue( int index, object value )
    {
      SetValue( index, (T)value );
    }

    public int KeysCount
    {
      get
      {
        AnimatedTrack<T> parent = callback.GetParentTrack();
        if( parent != null )
          return parent.KeysCount;
        return values.Count;
      }
    }

    public void Assign( AnimatedTrack<T> source )
    {
      callback.BeforeChanged();
      values.Clear();

			foreach ( KeyValue key in source.values )
			{
				values.Add( new KeyValue( owner, key.Key, key.Value ) );
			}
    }

    public bool IsEqual( AnimatedTrack<T> source )
    {
      if( values.Count != source.values.Count )
        return false;

      var enum1 = values.GetEnumerator();
      var enum2 = source.values.GetEnumerator();
      while( enum1.MoveNext() && enum2.MoveNext() )
      {
        if( !enum1.Current.IsEqual( enum2.Current ) )
          return false;
      }
      return true;
    }

    public object Serialize()
    {
			UndoRedoList<SerializaedKeyValue> result = new UndoRedoList<SerializaedKeyValue>( null );

			using ( UndoRedoTransaction trans = new UndoRedoTransaction( "Serialize AnimatedTrack" ) )
			{
				foreach ( KeyValue key in values )
				{
					result.Add( new SerializaedKeyValue( key ) );
				}				

				trans.Commit();
			}

      return result;
    }

    public void Deserialize( object storage )
    {
      UndoRedoList<SerializaedKeyValue> track = storage as UndoRedoList<SerializaedKeyValue>;
			if ( track == null || track.Count == 0 )
        return;

			using(UndoRedoTransaction trans = new UndoRedoTransaction("Deserialize AnimatedTrack"))
			{
			  values.Clear();
				foreach( SerializaedKeyValue key in track )
				{
					values.Add( new KeyValue( owner, key.Key, key.Value ) );
				}	

				trans.Commit();
			}
    }

    public float Length
    {
      get
      {
        if( KeysCount > 0 )
          return GetKey( KeysCount - 1 );

        return 0.0f;
      }
    }

    public float GetTime( float _key )
    {
      if( _key < 0.0f )
        return 0.0f;
      if( _key > Length )
        return Length;
      return _key;
    }

  }
}

using System;
using System.Collections.Generic;
using System.Text;
using System.Reflection;

namespace libdb.DB
{
  public static class FieldsWalker
  {
    #region Core private functions

    /// <returns>Returns false is walker should stop go through</returns>
    private static bool CallDepthControlFunctor( object obj, object fieldKeeper, DBFieldInfo field, ref int depth, DepthControlFunctor2 depthFunctor )
    {
      if ( depthFunctor == null )
        return true;

      return depthFunctor( obj, fieldKeeper, field, ref depth );
    }

    /// <returns>Returns true if object was changed</returns>
    private static bool CallFunctor( ref object value, DBFieldInfo field, VisitFieldFunctor functor, out bool canContinue )
    {
      canContinue = true;

      if ( functor == null )
        return false;

      object oldValue = value;
      canContinue = functor( ref value, field );
      return value != oldValue;
    }

    private static bool VisitList( object obj, DBFieldInfo field, int depth, VisitFieldFunctor functor, DepthControlFunctor2 depthFunctor )
    {
      Type objType = obj.GetType();

      PropertyInfo countProperty = TypeUtils.GetProperty( field.FieldType, "Count" );
      PropertyInfo indexProperty = TypeUtils.GetProperty( field.FieldType, "Item" );

      if ( countProperty == null || indexProperty == null )
        return true;

      int count = (int)countProperty.GetValue( obj, new object[0] { } );
      for ( int i = 0; i < count; ++i )
      {
        object[] index = new object[1] { i };

        bool canContinue = true;
        object value = indexProperty.GetValue( obj, index );
        if ( CallFunctor( ref value, field, functor, out canContinue ) && indexProperty.CanWrite )
          indexProperty.SetValue( obj, value, index );

        if ( !canContinue )
          return false;

        int newDepth = depth;
        if ( CallDepthControlFunctor( value, obj, field, ref newDepth, depthFunctor ) )
        {
          if ( !VisitFields( value, field, newDepth, functor, depthFunctor ) )
            return false;
        }
      }

      return true;
    }

    private static bool VisitStruct( object obj, int depth, VisitFieldFunctor functor, DepthControlFunctor2 depthFunctor )
    {
      if ( null == obj )
        return false;
      Type objType = obj.GetType();

      DBFieldInfo[] fields = TypeUtils.GetFields( objType, true );
      if ( fields != null && fields.Length > 0 )
      {
        foreach ( DBFieldInfo field in fields )
        {
          bool canContinue = true;
          object value = field.GetValue( obj );

          if ( null == value )
            continue;

          if ( CallFunctor( ref value, field, functor, out canContinue ) && field.CanWrite )
            field.SetValue( obj, value );

          if ( !canContinue )
            return false;

          int newDepth = depth;
          if ( CallDepthControlFunctor( value, obj, field, ref newDepth, depthFunctor ) )
          {
            if ( !VisitFields( value, field, newDepth, functor, depthFunctor ) )
              return false;
          }
        }
      }

      return true;
    }

    private static bool VisitFields( object obj, DBFieldInfo field, int depth, VisitFieldFunctor functor, DepthControlFunctor2 depthFunctor )
    {
      if ( obj == null )
        return true;

      Type objType = obj.GetType();

      if ( TypeUtils.IsList( objType ) )
        return VisitList( obj, field, depth, functor, depthFunctor );
      else if ( TypeUtils.GetTypeFromPtr( objType ) != null )
      {
        DBPtrBase ptr = obj as DBPtrBase;
        if ( ptr == null )
          return true;

        DBResource resource = ptr.Get<DBResource>();
        if ( resource == null )
          return true;

        return VisitStruct( resource, depth, functor, depthFunctor );
      }
      else if ( !TypeUtils.IsSimpleType( objType ) )
        return VisitStruct( obj, depth, functor, depthFunctor );

      return true;
    }

    #endregion

    #region Public wrappers and delegates for core function

    public delegate bool VisitFieldFunctor( ref object obj, DBFieldInfo field );
    public delegate bool DepthControlFunctor( object obj, ref int depth );
    public delegate bool DepthControlFunctor2( object obj, object fieldKeeper, DBFieldInfo field, ref int depth );

    public static bool VisitFields( object obj, VisitFieldFunctor functor, DepthControlFunctor depthFunctor )
    {
      return VisitFields( obj, null, 0, functor, ( object o, object fk, DBFieldInfo f, ref int d ) => { return depthFunctor( o, ref d ); } );
    }

    public static bool VisitFields( object obj, DBFieldInfo field, VisitFieldFunctor functor, DepthControlFunctor depthFunctor )
    {
      lock ( obj )
      {
        return VisitFields( obj, field, 0, functor, ( object o, object fk, DBFieldInfo f, ref int d ) => { return depthFunctor( o, ref d ); } );
      }
    }

    public static bool VisitFields( object obj, VisitFieldFunctor functor, DepthControlFunctor2 depthFunctor )
    {
      return VisitFields( obj, null, 0, functor, depthFunctor );
    }

    public static bool VisitFields( object obj, DBFieldInfo field, VisitFieldFunctor functor, DepthControlFunctor2 depthFunctor )
    {
      lock ( obj )
      {
        return VisitFields( obj, field, 0, functor, depthFunctor );
      }
    }

    #endregion

    #region Universal depth controller (can control max depth, objects that step into, depth increment)

    [Flags]
    public enum ObjectType
    {
      None = 0,

      DBPtrUninlined = 0x00000001,
      DBPtrInlined = 0x00000002,
      DBPtr = 0x00000003,

      Struct = 0x00000004,
      List = 0x00000008,
      All = 0x0000000F,
    }

    public class DepthController
    {
      private readonly int maxDepth = 0;
      private readonly ObjectType depthIncreaseFlags = ObjectType.All;
      private readonly ObjectType canStepIntoFlags = ObjectType.All;

      public DepthController( int maxDepth, ObjectType depthIncreaseFlags, ObjectType canStepIntoFlags )
      {
        this.maxDepth = maxDepth;
        this.depthIncreaseFlags = depthIncreaseFlags;
        this.canStepIntoFlags = canStepIntoFlags;
      }

      private static ObjectType GetObjectType( object obj )
      {
        DBPtrBase ptr = obj as DBPtrBase;
        if ( ptr != null )
          return ptr.DBId.IsInlined ? ObjectType.DBPtrInlined : ObjectType.DBPtrUninlined;
        else if ( TypeUtils.IsList( obj.GetType() ) )
          return ObjectType.List;
        else if ( TypeUtils.IsStruct( obj.GetType() ) )
          return ObjectType.Struct;

        return ObjectType.None;
      }

      public bool Functor( object obj, ref int depth )
      {
        if ( null == obj )
          return false;

        ObjectType objType = GetObjectType( obj );

        if ( ( objType & canStepIntoFlags ) != ObjectType.None )
        {
          if ( ( objType & depthIncreaseFlags ) != ObjectType.None )
          {
            if ( maxDepth >= 0 && depth >= maxDepth )
              return false;

            ++depth;
          }

          return true;
        }

        return false;
      }
    }

    #endregion

    public delegate bool TypedFieldVisitor<T>( ref T obj );

    private class TypedFieldVisitorFunctor<T>
    {
      private readonly TypedFieldVisitor<T> functor = null;

      public TypedFieldVisitorFunctor( TypedFieldVisitor<T> functor )
      {
        this.functor = functor;
      }

      public bool Functor( ref object obj, DBFieldInfo field )
      {
        Type objType = obj.GetType();
        if ( !TypeUtils.IsSubclassOf( objType, typeof( T ) ) && objType != typeof( T ) )
          return true;

        T typedObj = (T)obj;
        bool result = functor( ref typedObj );
        obj = typedObj;

        return result;
      }
    }

    public static bool VisitFields<T>( object obj, TypedFieldVisitor<T> functor, DepthControlFunctor depthFunctor )
    {
      TypedFieldVisitorFunctor<T> visitor = new TypedFieldVisitorFunctor<T>( functor );

      return VisitFields( obj, visitor.Functor, depthFunctor );
    }

    public static bool VisitFields<T>( object obj, TypedFieldVisitor<T> functor, DepthControlFunctor2 depthFunctor )
    {
      TypedFieldVisitorFunctor<T> visitor = new TypedFieldVisitorFunctor<T>( functor );

      return VisitFields( obj, visitor.Functor, depthFunctor );
    }

    public delegate bool TypedFieldWithAttributeVisitor<T, TAttribute>( ref T obj, TAttribute attrbite, string fieldName ) where TAttribute : Attribute;
    public delegate bool TypedFieldWithAttributeVisitor2<T, TAttribute>( ref T obj, TAttribute attrbite, DBFieldInfo field ) where TAttribute : Attribute;

    private class TypedFieldWithAttributeVisitorFunctor<T, TAttribute> where TAttribute : Attribute
    {
      private readonly TypedFieldWithAttributeVisitor2<T, TAttribute> functor = null;

      public TypedFieldWithAttributeVisitorFunctor( TypedFieldWithAttributeVisitor<T, TAttribute> functor )
      {
        this.functor = ( ref T o, TAttribute a, DBFieldInfo f ) => { return functor( ref o, a, f.Name ); };
      }

      public TypedFieldWithAttributeVisitorFunctor( TypedFieldWithAttributeVisitor2<T, TAttribute> functor )
      {
        this.functor = functor;
      }

      public bool Functor( ref object obj, DBFieldInfo field )
      {
        Type objType = obj.GetType();
        if ( !TypeUtils.IsSubclassOf( objType, typeof( T ) ) && objType != typeof( T ) )
          return true;

        TAttribute[] attrs = field.GetCustomAttributes<TAttribute>( true );
        if ( attrs == null || attrs.Length != 1 )
          return true;

        T typedObj = (T)obj;
        bool result = functor( ref typedObj, attrs[0], field );
        obj = typedObj;

        return result;
      }
    }

    public static bool VisitFields<T, TAttribute>( object obj, TypedFieldWithAttributeVisitor<T, TAttribute> functor, DepthControlFunctor depthFunctor ) where TAttribute : Attribute
    {
      TypedFieldWithAttributeVisitorFunctor<T, TAttribute> visitor = new TypedFieldWithAttributeVisitorFunctor<T, TAttribute>( functor );

      return VisitFields( obj, visitor.Functor, depthFunctor );
    }

    public static bool VisitFields<T, TAttribute>( object obj, TypedFieldWithAttributeVisitor2<T, TAttribute> functor, DepthControlFunctor2 depthFunctor ) where TAttribute : Attribute
    {
      TypedFieldWithAttributeVisitorFunctor<T, TAttribute> visitor = new TypedFieldWithAttributeVisitorFunctor<T, TAttribute>( functor );

      return VisitFields( obj, visitor.Functor, depthFunctor );
    }

    private class DBPtrBaseCollector
    {
      private readonly List<DBPtrBase> ptrs = new List<DBPtrBase>();

      public bool Functor( ref DBPtrBase ptr )
      {
        ptrs.Add( ptr );
        return true;
      }

      public DBPtrBase[] GetPtrs() { return ptrs.ToArray(); }
    }

    public static DBPtrBase[] CollectDBPtrs( object obj, DepthControlFunctor depthFunctor )
    {
      DBPtrBaseCollector collector = new DBPtrBaseCollector();
      VisitFields<DBPtrBase>( obj, collector.Functor, depthFunctor );
      return collector.GetPtrs();
    }

    public static DBPtrBase[] CollectDBPtrs( System.Collections.IEnumerable objects, DepthControlFunctor depthFunctor )
    {
      DBPtrBaseCollector collector = new DBPtrBaseCollector();
      foreach ( var obj in objects )
      {
        VisitFields<DBPtrBase>( obj, collector.Functor, depthFunctor );
      }
      return collector.GetPtrs();
    }

    private class RelatedObjectsCollector
    {
      private Dictionary<DBID, bool> result;
      private bool collectInlined;

      public RelatedObjectsCollector( Dictionary<DBID, bool> _result, bool _collectInlined ) 
      { 
        result = _result;
        collectInlined = _collectInlined;
      }

      public bool Functor( ref DBPtrBase ptr )
      {
        if ( ptr.DBId != null && !ptr.DBId.IsEmpty && ( collectInlined || !ptr.DBId.IsInlined ) )
        {
          if ( !result.ContainsKey( ptr.DBId ) )
            result[ptr.DBId] = true;
        }
        return true;
      }
    }

    public static List<DBID> CollectRelatedObjects( DBID rootDbid, int maxDepth, bool includeInlined )
    {
      if ( rootDbid.IsEmpty )
        return new List<DBID>();

      Dictionary<DBID, bool> result = new Dictionary<DBID, bool>();
      result[rootDbid] = true;

      DepthController depthController = new DepthController( maxDepth, includeInlined ? ObjectType.DBPtr : ObjectType.DBPtrUninlined, ObjectType.All );
      RelatedObjectsCollector collector = new RelatedObjectsCollector( result, includeInlined );
      DBResource res = DataBase.Get<DBResource>( rootDbid );
      VisitFields<DBPtrBase>( res, collector.Functor, depthController.Functor );

      return new List<DBID>( result.Keys );
    }

    
  }
}

using System;
using System.Reflection;
using UnityEngine;

namespace Flash
{
  public class ClipboardHelper
  {
    private static string _internalClipboard;
    private static PropertyInfo m_systemCopyBufferProperty = null;
    private static PropertyInfo GetSystemCopyBufferProperty()
    {
      if ( m_systemCopyBufferProperty == null )
      {
        Type t = typeof( GUIUtility );
        m_systemCopyBufferProperty = t.GetProperty( "systemCopyBuffer", BindingFlags.Static | BindingFlags.Public );
        if ( m_systemCopyBufferProperty == null )
        {
          Debug.LogError(
            "Can't access internal member 'GUIUtility.systemCopyBuffer' it may have been removed / renamed" );
          return null;
        }
      }
      return m_systemCopyBufferProperty;
    }

    public static string clipBoard
    {
      get
      {
        PropertyInfo p = GetSystemCopyBufferProperty();
        if ( p == null )
          return _internalClipboard;

        return (string)p.GetValue( null, null );
      }
      set
      {
        PropertyInfo p = GetSystemCopyBufferProperty();
        if ( p == null )
          _internalClipboard = value;
        else
          p.SetValue( null, value, null );
      }
    }
  }
}
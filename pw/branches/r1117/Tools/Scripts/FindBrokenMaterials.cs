/*
 * http://SITE
 * 
#about Выдать список эффектов с неправильно настроенными материалами
#ref EditorNative.dll
#ref EditorPlugins.dll
#ref PF_Types.DBTypes.dll
#ref PF_Editor.exe
*/

using System;
using System.Collections;
using System.Collections.Generic;
using DBTypes;
using EditorLib.IO;
using libdb.DB;
using libdb.Diagnostics;

namespace Scripts
{
  public class FindBrokenMaterials
  {
    public IEnumerable Main( EditorLib.IEditorWinApplication app )
    {
      Dictionary<Type, List<DBID>> dbids;
      Type[] types = new[]
                     {
                       typeof (ParticleFXMaterial), 
                       typeof (BasicFXMaterial), 
                       typeof (DecalMaterial),
                       typeof (BasicMaterial)
                     };

      ObjectsSelector.CollectObjects( app.Application, "/", types, true, true, out dbids );

      int cnt = 0;

      foreach( Type type in dbids.Keys )
      {
        foreach( DBID dbid in dbids[type] )
        {
          DBPtr<DBResource> ptr = DataBase.Get<DBResource>( dbid );
          DBResource material = ptr.Get();

          if( Validate( material ) )
            continue;

          cnt++;

          string message = string.Format( "Invalid material: {0}", GetCaption( material ) );

          if( material.DBId.IsInlined )
          {
            Log.TraceMessage( "{0} inlined in {1}", message, DBID.FromDBID( material.DBId, false ) );
          }
          else
          {
            Log.TraceMessage( "{0} linked to:", message );

            Dictionary<DBID, int> backlinks = ptr.GetBackLinks();

            foreach( DBID linkDbId in backlinks.Keys )
            {
              Log.TraceMessage( "... {0}", linkDbId );
            }
          }

        }
      }

      Log.TraceMessage( "Broken materials: {0}", cnt );

      yield return true;
    }

    private static string GetCaption( DBResource _material )
    {
      string result = string.Empty;

      if( _material is ParticleFXMaterial )
        result = ( (ParticleFXMaterial)_material ).caption;
      else if( _material is BasicFXMaterial )
        result = ( (BasicFXMaterial)_material ).caption;
      else if( _material is DecalMaterial )
        result = ( (DecalMaterial)_material ).caption;
      else if( _material is BasicMaterial )
        result = ( (BasicMaterial)_material ).caption;

      if( string.IsNullOrEmpty( result ) )
        result = _material.DBId.ToString();

      return result;
    }

    #region Validation

    private static bool Validate( DBResource _material )
    {
      if( _material is ParticleFXMaterial )
        return Validate( (ParticleFXMaterial)_material );

      if( _material is BasicFXMaterial )
        return Validate( (BasicFXMaterial)_material );

      if( _material is DecalMaterial )
        return Validate( (DecalMaterial)_material );

      if( _material is BasicMaterial )
        return Validate( (BasicMaterial)_material );

      Log.AlwaysAssert( "Сюда мы никогда не должны попасть" );

      return false;
    }

    private static bool Validate( ParticleFXMaterial _material )
    {
      bool invalid = _material.renderState.blendMode != BlendMode.Off &&
                     _material.OpacityAndEmissiveModePinValue == OpacityAndEmissiveModePin.Emissive;
      return !invalid;
    }

    private static bool Validate( BasicFXMaterial _material )
    {
      bool invalid = _material.renderState.blendMode != BlendMode.Off &&
                     _material.OpacityAndEmissiveModePinValue == OpacityAndEmissiveModePin.Emissive;

      return !invalid;
    }

    private static bool Validate( DecalMaterial _material )
    {
      bool invalid = _material.renderState.blendMode != BlendMode.Off &&
                    _material.OpacityAndEmissiveModePinValue == OpacityAndEmissiveModePin.Emissive;

      return !invalid;
    }

    private static bool Validate( BasicMaterial _material )
    {
      bool invalid = _material.renderState.blendMode != BlendMode.Off &&
                     _material.EmissivePinValue != EEmissivePin.EmissiveOff;

      return !invalid;
    }

    #endregion
  }
}

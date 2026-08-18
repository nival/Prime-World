using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.Serialization;
using Flash.Utils;
using Flash.Utils.Atlasses;
using SwfDotNet.IO;
using SwfDotNet.IO.Tags;
using Resources = ResourcesManager.Resources;

#if UNITY_EDITOR

#endif
using UnityEngine;
using Rect = UnityEngine.Rect;

namespace Flash
{
  [Serializable]
  public class MyTagId : ISerializable
  {
    public int id;
    public UniBaseTag baseTag;

    public MyTagId( int id, UniBaseTag baseTag )
    {
      this.id = id;
      this.baseTag = baseTag;
    }

    public MyTagId( SerializationInfo info, StreamingContext context )
    {
      SerializeHelpers.Unpack( info, "id", out id );
      SerializeHelpers.Unpack( info, "baseTag", out baseTag );
    }

    public void GetObjectData( SerializationInfo info, StreamingContext context )
    {
      SerializeHelpers.Pack( info, "id", id );
      SerializeHelpers.Pack( info, "baseTag", baseTag );
    }
  }

  [Serializable]
  public class UniSwf : ISerializable
  {
    private readonly string _name;

    public string Name
    {
      get { return _name; }
    }

    public AtlasData AtlasData { get; private set; }
    private readonly Rect _rect;
    public Rect Rect
    {
      get { return _rect; }
    }
    private readonly List<IDisplayTag> _tags = new List<IDisplayTag>();
    public List<IDisplayTag> Tags
    {
      get { return _tags; }
    }
    private float _swfTimeDuration;
    public float SwfTimeDuration
    {
      get { return _swfTimeDuration; }
      set { _swfTimeDuration = value; }
    }
    private readonly Dictionary<int, UniBaseTag> _uniDictionary = new Dictionary<int, UniBaseTag>();
    public Dictionary<int, UniBaseTag> UniDictionary
    {
      get { return _uniDictionary; }
    }
    private readonly List<Texture2D> _textureResources = new List<Texture2D>();
    public List<Texture2D> TextureResources
    {
      get { return _textureResources; }
    }
    
    private readonly List<MyTagId> _allTags = new List<MyTagId>();

    public bool AtlasIsNotCached()
    {
      return !FlashEnv.CACHE_ENABLED || AtlasData == null;
    }

    void ISerializable.GetObjectData( SerializationInfo info, StreamingContext context )
    {
      SerializeHelpers.Pack( info, "_name", _name );
      SerializeHelpers.Pack( info, "_tags", _tags );
      SerializeHelpers.Pack( info, "_rect", _rect );
      SerializeHelpers.Pack( info, "_swfTimeDuration", _swfTimeDuration );
      SerializeHelpers.Pack( info, "_allTags", _allTags );
      SerializeHelpers.Pack( info, "_fontsLoadingList", FontStorage.LoadedFontsNames );
    }

    public UniSwf( SerializationInfo info, StreamingContext context )
    {
      SerializeHelpers.Unpack( info, "_name", out _name );
      SerializeHelpers.Unpack( info, "_tags", out _tags );
      SerializeHelpers.Unpack( info, "_rect", out _rect );
      SerializeHelpers.Unpack( info, "_swfTimeDuration", out _swfTimeDuration );
      SerializeHelpers.Unpack( info, "_allTags", out _allTags );
      var fontsLoadingList = new Dictionary<int, string>();
      SerializeHelpers.Unpack( info, "_fontsLoadingList", out fontsLoadingList );

      foreach ( var font in fontsLoadingList )
        FontStorage.TryLoadFontToMap( font.Key, font.Value );
    }

    public static void ParseTags( BaseTagCollection tags, List<IDisplayTag> uniTags, UniSwf uniSwf )
    {
      foreach ( BaseTag tag in tags )
      {
        if ( tag is SetBackgroundColorTag )
        {
          UniSetBackgroundColorTag setBackgroundColorTag = new UniSetBackgroundColorTag( tag, uniSwf );
          uniTags.Add( setBackgroundColorTag );
        }

        if ( tag is FrameLabelTag )
        {
          UniFrameLabelTag frameLabelTag = new UniFrameLabelTag( tag, uniSwf );
          uniTags.Add( frameLabelTag );
        }

        if ( tag is ShowFrameTag )
        {
          UniShowFrameTag showFrameTag = new UniShowFrameTag( uniSwf );
          uniTags.Add( showFrameTag );
        }

        if ( tag is PlaceObject2Tag )
        {
          UniPlaceObjectTag placeObjectTag = new UniPlaceObjectTag( tag, uniSwf );
          uniTags.Add( placeObjectTag );
        }

        if ( tag is RemoveObject2Tag )
        {
          UniRemoveObjectTag removeObjectTag = new UniRemoveObjectTag( tag, uniSwf );
          uniTags.Add( removeObjectTag );
        }

        if ( tag is DefineScalingGrid )
        {
          DefineScalingGrid scalingGrid = tag as DefineScalingGrid;
          if ( uniSwf.UniDictionary[scalingGrid.TargetCharacterId] is UniDefineSpriteTag )
          {
            ( (UniDefineSpriteTag)uniSwf.UniDictionary[scalingGrid.TargetCharacterId] ).Scale9Grid = scalingGrid;
          }
        }

        if ( tag is DefineFontName )
        {
          var fontTag = tag as DefineFontName;
          FontStorage.TryLoadFontToMap( fontTag.FontId, fontTag.FontName );
        }

        if ( tag is DoActionTag )
        {
          UniDoActionTag doActionTag = new UniDoActionTag( (DoActionTag)tag );
          uniTags.Add( doActionTag );
        }
      }
    }
    public static void ShowTags( IEnumerable tags )
    {
      Debug.Log( "********************TAGS******************************" );
      foreach ( BaseTag tag in tags )
      {
        Debug.Log( "Code: " + (TagCodeEnum)tag.TagCode + " Type: " + tag.GetType().ToString() );

        if ( tag is PlaceObject3Tag )
        {
          Debug.Log( ( (PlaceObject3Tag)tag ).TargetCharacterId );
        }

        if ( (TagCodeEnum)tag.TagCode == TagCodeEnum.FrameLabel )
        {
          Debug.Log( ( (FrameLabelTag)tag ).Name );
        }
      }
    }

    public UniSwf( Swf swf, string name, bool parseTags, bool excludeMeshGeneration )
    {
      _name = name;

      TryApplyAtlas();

      _rect = new Rect( swf.Size.Rectangle.X, swf.Size.Rectangle.Y, swf.Size.Rectangle.Width, swf.Size.Rectangle.Height );
      _swfTimeDuration = 1.0F / swf.Header.Fps;
      Timer.TimeDuration = _swfTimeDuration;

      //ShowDictionary(swf);
      //ShowTags(swf.Tags);

      ParseDictionary( swf );

      if ( !excludeMeshGeneration )
        BuildMeshes();

      if ( parseTags )
        ParseTags( swf.Tags, _tags, this );
    }

    private bool TryApplyAtlas()
    {
      AtlasData = null;

      // Cache
      if ( FlashEnv.CACHE_ENABLED )
      {
        AtlasData = TextureUtils.LoadAtlas( _name );
        return AtlasData != null;
      }
    }

    public void Release()
    {
      foreach ( KeyValuePair<int, UniBaseTag> keyValuePair in UniDictionary )
      {
        keyValuePair.Value.Release();
      }
    }

    public void Dispose()
    {
      if ( AtlasData != null )
      {
        AtlasData.Dispose();
        AtlasData = null;
      }
    }

    private void ShowDictionary( Swf swf )
    {
      Debug.Log( "********************DICTIONARY******************************" );
      foreach ( DefineTag tag in swf.Dictionary.Values )
      {
        Debug.Log( tag.CharacterId + "  " + tag.GetType().ToString() );
      }
    }

    private void ParseDictionary( Swf swf )
    {
      foreach ( ushort key in swf.Dictionary.Keys )
      {
        DefineTag tag = swf.Dictionary[key];
        Type type = tag.GetType();

        // Bitmaps
        if ( type == typeof( DefineBitsJpeg2Tag ) ||
            type == typeof( DefineBitsJpeg3Tag ) ||
            type == typeof( DefineBitsTag ) ||
            type == typeof( DefineBitsLossLessTag ) ||
            type == typeof( DefineBitsLossLess2Tag ) )
        {
          //Profiler.BeginSample("####### JPEG_TAG ########");
          UniDefineBitsJpegTag defineBitJpegTag = null;

          // Try get from cache
          if ( AtlasIsNotCached() )
          {
            if ( type == typeof( DefineBitsJpeg2Tag ) )
              defineBitJpegTag = new UniDefineBitsJpegTag( (DefineBitsJpeg2Tag)tag, this );
            else if ( type == typeof( DefineBitsJpeg3Tag ) )
              defineBitJpegTag = new UniDefineBitsJpegTag( (DefineBitsJpeg3Tag)tag, this );
            else if ( type == typeof( DefineBitsTag ) )
              defineBitJpegTag = new UniDefineBitsJpegTag( (DefineBitsTag)tag, this );
            else if ( type == typeof( DefineBitsLossLessTag ) )
              defineBitJpegTag = new UniDefineBitsJpegTag( (DefineBitsLossLessTag)tag, this );
            else if ( type == typeof( DefineBitsLossLess2Tag ) )
              defineBitJpegTag = new UniDefineBitsJpegTag( (DefineBitsLossLess2Tag)tag, this );
          }
          else
          {
            defineBitJpegTag = new UniDefineBitsJpegTag( (Texture2D)null, this );
          }

          defineBitJpegTag.Id = key;
          _uniDictionary.Add( tag.CharacterId, defineBitJpegTag );
          _textureResources.Add( defineBitJpegTag.Texture );
          defineBitJpegTag.TextureIdResources = _textureResources.Count - 1;
          //Profiler.EndSample();
          continue;
        }

        // Shapes
        if ( tag is DefineShape )
        {
          //Profiler.BeginSample("####### DEFINE_SHAPE ########");
          UniDefineShapeTag defineShapeTag = new UniDefineShapeTag( tag as BaseTag, this );
          _uniDictionary.Add( tag.CharacterId, defineShapeTag );
          //Profiler.EndSample();
          continue;
        }

        // Morph
        if ( tag is DefineMorphShapeTag )
        {
          //Profiler.BeginSample("####### DEFINE_MORPH ########");
          UniDefineMorphShapeTag defineMorphShapeTag = new UniDefineMorphShapeTag( tag as BaseTag, this );
          _uniDictionary.Add( tag.CharacterId, defineMorphShapeTag );
          //Profiler.EndSample();
          continue;
        }

        //Sprites
        if ( tag is DefineSpriteTag )
        {
          //Profiler.BeginSample("####### PARSE_SPRITES ########");
          UniDefineSpriteTag defineSpriteTag = new UniDefineSpriteTag( tag as BaseTag, this );
          _uniDictionary.Add( tag.CharacterId, defineSpriteTag );
          //Profiler.EndSample();
          continue;
        }

        // Text
        if ( tag is DefineEditTextTag )
        {
          //Profiler.BeginSample("####### DEFINE_MORPH ########");
          UniDefineEditTextTag editTextTag = new UniDefineEditTextTag( tag as BaseTag, this );
          _uniDictionary.Add( tag.CharacterId, editTextTag );
          //Profiler.EndSample();
          continue;
        }

        // If tag is not supported
        UniBaseTag baseTag = new UniBaseTag( this );
        _uniDictionary.Add( tag.CharacterId, baseTag );
      }

      if ( AtlasIsNotCached() )
      {
        AtlasData = TextureUtils.GenerateTextureAtlas( _textureResources );

        if ( AtlasData == null )
          return;

        if ( !Application.isEditor )
        {
          foreach ( Texture2D texture2D in _textureResources )
            Texture2D.Destroy( texture2D );
        }
      }

      //fill tags
      foreach ( int tagId in _uniDictionary.Keys )
      {
        _allTags.Add( new MyTagId( tagId, _uniDictionary[tagId] ) );
      }
    }

    private void BuildMeshes()
    {
      //Profiler.BeginSample("####### BUILD_MESHES ########");
      // build meshes
      foreach ( KeyValuePair<int, UniBaseTag> keyValuePair in _uniDictionary )
      {
        if ( keyValuePair.Value is UniBaseShapeTag )
          ( (UniBaseShapeTag)keyValuePair.Value ).BuildMeshes();
      }
      //Profiler.EndSample();
    }

    private void RestoreDictionary()
    {
      _uniDictionary.Clear();

      foreach ( MyTagId myTagId in _allTags )
      {
        _uniDictionary[myTagId.id] = myTagId.baseTag;
      }
    }

    public bool DeserializeCompleted()
    {
      RestoreDictionary();

      if ( !TryApplyAtlas() )
      {
        NivalCLI.CLI.DataAssert( "BinaryData deserialization error. Can't find atlas cache for: {0}", _name );
        return false;
      }

      BuildMeshes();
      Timer.TimeDuration = _swfTimeDuration;

      return true;
    }
  }
}
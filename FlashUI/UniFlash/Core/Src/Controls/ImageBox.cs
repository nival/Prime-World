using System;
using System.Collections.Generic;
using Flash.Utils;
using Flash.Utils.Atlasses;
using ModelData.Network;
using NivalCLI;
using UnityEngine;
using Resources = ResourcesManager.Resources;

namespace Flash.Controls
{
  public class ImageBox : SystemTooltipControl, IDragIcon
  {
    private static readonly List<string> _requestUrls = new List<string>();
    private float _initialHeight;
    private float _initialWidth;
    public Loader _loader;
    private string _image;
    private string _loadingPath;

    private bool procedural;

    public string AnimatedIconPath { get; set; }

    public void InitProcedural(Texture tex)
    {
      procedural = true;
      float curWidth = Width;
      float curHeight = Height;
      if (_loader != null)
      {
        RemoveChild(_loader);
      }
      _loader = null;
      if ( _loader == null )
      {
        _loader = new Loader();
        AddChild( _loader );
      }
      if ( SizeMode == ImageSizeMode.Stretch )
      {
        _loader.Width = _initialWidth;
        _loader.Height = _initialHeight;
      }
      else if ( SizeMode == ImageSizeMode.StretchToCurrent )
      {
        _loader.Width = curWidth;
        _loader.Height = curHeight;
      }
      _loader.Load(tex, null);
      _loader.Visible = true;
      _loader.Texture = tex;
      UpdateLocalBounds();
      Scale = Vector3.one;
    }

    /// <summary>
    /// If format is Folder/Subfolder/SomeImage then load from Assets/Resources.
    /// If format is http://site/img.jpg than async load from url
    /// </summary>
    public string Image
    {
      get { return _image; }
      set
      {
        
        _image = value;
        _loadingPath = _image;

        if ( string.IsNullOrEmpty( _image ) )
        {
          if ( _loader != null )
            _loader.Visible = false;

          return;
        }

        if ( _image.StartsWith( "http://" ) || _image.StartsWith( "https://" ) )
        {
          Texture2D image = null;

          // Founded in requests
          if ( _requestUrls.Contains( _image ) )
          {
            UniFlashPlayer.RegisterTextureFromCacheRequest( _image, CreateLoader );
            return;
          }

          // Founded in cache
          if ( UniFlashPlayer.WebTexturesDic.TryGetValue( _image, out image ) )
          {
            CreateLoader( image, _image );
            return;
          }

          _requestUrls.Add( _image );
          NivalCLI.CLI.Info( "Loading image '{0}'...", _image );
          UniFlashPlayer.WWWQueue.SendGetRequest( _image, args => OnLoadImageAsync( args, CreateLoader, err => EventHelper.Invoke( OnError, this, err ) ) );
        }
        else
        {
          _loadingPath = _image.TrimStart('/', '\\');
          AtlassedTexture image;
          if (AtlassedTexturesLoader.TryToLoad(_loadingPath, out image))
          {
            CreateLoader(image, _loadingPath);
          }
          else
          {
            if (_loadingPath.IndexOf('.') != -1)
              _loadingPath = _loadingPath.Substring(0, _loadingPath.IndexOf('.'));

            if (AtlassedTexturesLoader.TryToLoad(_loadingPath, out image))
              CreateLoader(image, _loadingPath);
            else
            {
              Texture2D texture = null;

              try
              {
                texture = Resources.Load(_loadingPath) as Texture2D;
              }
              catch (Exception ex)
              {
                CLI.Error("Loading texture by path '{0}' error: {1}", _loadingPath, ex.Message);
              }

              if ( texture != null )
                CreateLoader(texture, _loadingPath);
              else
                CLI.Warning("[ImageBox] NOT FOUND: original='{0}', trimmed='{1}' (not in atlas, not in Resources)", _image, _loadingPath);
            }
          }
        }
        
      }
    }

    /// <summary>
    /// Preloads image texture to the internal cahce. Works only with urls
    /// </summary>
    /// <param name="url">url to image</param>
    public static void PreloadImage( string url )
    {
      if ( string.IsNullOrEmpty( url ) )
        return;

      if ( !url.StartsWith( "http://" ) && !url.StartsWith( "https://" ) )
        return;

      // Founded in requests
      if ( _requestUrls.Contains( url ) )
        return;

      // Founded in cache
      Texture2D image = null;
      if ( UniFlashPlayer.WebTexturesDic.TryGetValue( url, out image ) )
        return;
      NivalCLI.CLI.Info( "Preloading image '{0}'...", url );
      _requestUrls.Add( url );
      UniFlashPlayer.WWWQueue.SendGetRequest( url, OnPreloadDone );
    }

    private static void OnPreloadDone( HTTPResponseArgs args )
    {
      OnLoadImageAsync( args, null, null );
    }

    public ImageSizeMode SizeMode { get; set; }

    public event EventHandler<WWWErrorEventArgs> OnError;

    public ImageBox()
    {
      SizeMode = ImageSizeMode.Stretch;
    }

    public void SetImageSize( float width, float heigth )
    {
      _initialHeight = heigth;
      _initialWidth = width;
    }

    protected override void Init()
    {
      base.Init();

      AnimatedIconPath = "";

      SetImageSize( Width, Height );

      //удаляем всех чилдов, т.к. в ImageBox могут быть картинки-заглушки из SWF
      ClearChildren();
    }

    /// <summary>
    /// Creates loader from atlassed texture data
    /// </summary>
    /// <param name="image"></param>
    /// <param name="name"></param>
    private void CreateLoader( AtlassedTexture image, string name )
    {
      Action<AtlassedTexture, Loader, string> load = ( img, ldr, n ) => ldr.Load( img, n );
      CreateLoader( image, name, load );
    }

    private void CreateLoader( Texture2D image, string name )
    {
      Action<Texture2D, Loader, string> load = ( img, ldr, n ) =>
      {
        img.mipMapBias = -2;
        ldr.Load( img, n );
      };

      CreateLoader( image, name, load );
    }

    private void CreateLoader<T>( T image, string name, Action<T, Loader, string> loadAction )
      where T : class
    {
      // Check if we still need this image in this ImageBox
      // It is fix for case, when we already change image needed, but old image
      //were loaded after this.
      if (!String.Equals(name, _loadingPath)) return;

      if (procedural && _loader != null)
      {
        RemoveChild(_loader);
        _loader = null;
      }

      if ( image == null )
      {
        if ( _loader != null )
          _loader.Visible = false;

        return;
      }

      float curWidth = Width;
      float curHeight = Height;

      if ( _loader == null )
      {
        _loader = new Loader();
        AddChild( _loader );
      }

      _loader.Visible = true;


      loadAction( image, _loader, name );

      if ( SizeMode == ImageSizeMode.Stretch )
      {
        _loader.Width = _initialWidth;
        _loader.Height = _initialHeight;
      }
      else if ( SizeMode == ImageSizeMode.StretchToCurrent )
      {
        _loader.Width = curWidth;
        _loader.Height = curHeight;
      }

      UpdateLocalBounds();
    }

    private static void OnLoadImageAsync( HTTPResponseArgs httpResponseArgs, Action<Texture2D, string> successHandler, Action<WWWErrorEventArgs> errorHandler )
    {
      NivalCLI.CLI.Info( "Loading image '{0}'...Done with code={1} ({2}s)",
        httpResponseArgs.Url, httpResponseArgs.Code, httpResponseArgs.Duration.ToString( "0.00" ) );
      var wwwResponseArgs = httpResponseArgs as HTTPSocketComponent.WWWResponseArgs;
      if ( wwwResponseArgs == null )
      {
        NivalCLI.CLI.Assert( "Could not cast to WWWResponseArgs image loading response" );
        EventHelper.Invoke( errorHandler, null );
        return;
      }

      _requestUrls.Remove( wwwResponseArgs.WWW.url );

      if ( !String.IsNullOrEmpty( wwwResponseArgs.Error ) )
      {
        var args = new WWWErrorEventArgs( wwwResponseArgs.Error );
        NivalCLI.CLI.Assert( "WWWError occured on image loading: '{0}' url: '{1}'", wwwResponseArgs.Error, wwwResponseArgs.WWW.url );
        EventHelper.Invoke( errorHandler, args );
        return;
      }

      Texture2D texture = null;
      string contentType = wwwResponseArgs.WWW.GetResponseHeader("CONTENT-TYPE");
      if ( contentType.Contains( "image" ) && contentType != "image/jpg" && contentType != "image/png" && contentType != "image/jpeg" )
      {
        texture = new Texture2D( 1, 1, TextureFormat.ARGB32, false );
        if ( !texture.LoadFromBytes( wwwResponseArgs.Packet ) )
        {
          NivalCLI.CLI.Assert( @"Can't convert received image data to Texture2D. 
          Please, check that image file was not corrupted. url '{0}'", wwwResponseArgs.WWW.url );

          EventHelper.Invoke( errorHandler, null );
          return;
        }
        GarbageCollectorTimer.Collect();
      }
      else
      {
        texture = new Texture2D( 2, 2 );
        texture.LoadImage( wwwResponseArgs.Packet );
      }

      UniFlashPlayer.AddWebTextureToCache( wwwResponseArgs.WWW.url, texture );
      EventHelper.Invoke( successHandler, texture, wwwResponseArgs.WWW.url );
    }
  }

  public enum ImageSizeMode
  {
    /// <summary>
    /// Размен ImageBox становится равным размеру картинки
    /// </summary>
    AutoSize,
    /// <summary>
    /// Картинка скейлится под те размеры ImageBox, которые ему були заданы при Init
    /// </summary>
    Stretch,
    /// <summary>
    /// Картинка скейлится под те размеры ImageBox, которые у него выставлены на момент сета картинки
    /// </summary>
    StretchToCurrent
  }
}
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using System.Runtime.Serialization.Formatters.Binary;
using Flash.Utils;
using ModelData.Network;
using SwfDotNet.IO;
using Unity.Components.SoundsManager;
using UnityEngine;
using System.Linq;

namespace Flash
{
  public class UniFlashPlayer : MonoBehaviour
  {

    /// Offset for manual fixing positioning problems from swf.net.
    public const byte SWFNET_POSITIONING_OFFSET = 2;

    private const int MaxHeight = 1080;

    private static readonly HTTPQueue _wwwQueue = new HTTPQueue(Lobby.Tools.Utils.GetHTTPComponent(),
      FlashEnv.MAX_WWW_REQUEST_COUNT);

    public static HTTPQueue WWWQueue
    {
      get { return _wwwQueue; }
    }

    private static readonly Dictionary<string, Texture2D> _webTexturesDic = new Dictionary<string, Texture2D>();

    public static Dictionary<string, Texture2D> WebTexturesDic
    {
      get { return _webTexturesDic; }
    }

    private static readonly List<KeyValuePair<string, Action<Texture2D, string>>> _textureCacheHandlers =
      new List<KeyValuePair<string, Action<Texture2D, string>>>();

    private static AudioSource _audioSource;

    public static AudioSource AudioSource
    {
      get
      {
        if (_audioSource == null)
          _audioSource = Sound.CreateAudioSource(SourceType.UI);
        return _audioSource;
      }
    }

    private static bool _focused = true;

    public static bool Focused
    {
      get { return _focused; }
    }

    private static bool _isInit;
    private static UniFlashPlayer _mainFlashPlayer;

    public static UniFlashPlayer MainFlashPlayer
    {
      get { return _mainFlashPlayer; }
    }

    private static bool _showMouseFocus;

    public static bool ShowMouseFocus
    {
      get { return _showMouseFocus; }
      set { _showMouseFocus = value; }
    }

    public static bool ShowMasks { get; set; }

    private static readonly List<ControlsTree> _trees = new List<ControlsTree>();

    public static List<ControlsTree> Trees
    {
      get { return _trees; }
    }

    private static readonly Dictionary<MovieClip, UniSwf> _swfs = new Dictionary<MovieClip, UniSwf>();
    private static Camera _camera;

    public static Camera Camera
    {
      get { return _camera; }
    }

    private static Stage _stage;

    public static Stage MainStage
    {
      get { return _stage; }
    }

    public static bool IsWindowOpened
    {
      get { return FlashInput.MouseFocus != MainStage; }
    }

    // Freeze Scene
    private static bool _dirtyFreezeTex;
    private static int _camLayerMask;
    private static Texture2D _freezeTexture;
    private static bool _freezeScene = false;

    public static bool FreezeScene
    {
      get { return _freezeScene; }
    }

    public static event EventHandler<ResolutionEventArgs> FullScreen;
    public static event EventHandler<ResolutionEventArgs> PostFullScreen;
    public static event EventHandler<ResolutionEventArgs> ResolutionChanged;
    private bool _fullScreenPrev;
    private static bool _deviceLost;
    public static event Action DeviceObtained;
    public static event Action DeviceLost;
    public static event Action MaterialsReseted;

    public static bool IsDeviceActive
    {
      get { return !_deviceLost; }
    }

    private static bool _lastFrameRendered;

    #region Resolution & scale

    private const float TestScaleBias = 0.1f;
    [Range(-3f, 3f)]
    public float TestScale = 0f;
    private float _testScale = 0f;

    private static float _scale = 1f; // Определяет, во сколько раз 'точка' в интерфейсе больше экранной точки
    private static int _prevScreenWidth;
    private static int _prevScreenHeight;
    private static int _width;
    private static int _height;
    private static float _whAspect;

    public static int Width { get { return _width; } }
    public static int Height { get { return _height; } }
    public static float Scale { get { return _scale; } }
    public static float WHAspect { get { return _whAspect; } }

    #endregion

    public static UniFlashPlayer Init()
    {
      if (_isInit)
        return _mainFlashPlayer;

      var flashPlayer = new GameObject("__FLASH");
      _mainFlashPlayer = flashPlayer.AddComponent<UniFlashPlayer>();

      _camera = flashPlayer.AddComponent<Camera>();
      flashPlayer.AddComponent<Timer>();

      DontDestroyOnLoad(_mainFlashPlayer);
      _mainFlashPlayer.ResolutionUpdate();

      BuildControlsTree();

      _stage = new Stage {Name = "__Stage"};

      SetupCamera();

      _isInit = true;

      return _mainFlashPlayer;
    }

    /// <exception>Throws Exception when T has no applied Root Attribute.</exception>
    /// <exception>Throws RootAlreadyBindedException when Root of type T is already binded on another MovieClip.</exception>
    public static T PushSwf<T>(string fileName, params object[] constructorArgs) where T : MovieClip
    {
      NivalCLI.Profiler.Start("PushSWF " + fileName);
      var binAsset = Resources.Load(fileName + ".bin", typeof (TextAsset)) as TextAsset;

      //Profiler.BeginSample( "######## PUSH SWF ##############" );

      // Read
      UniSwf swf;

      if (binAsset != null)
      {
        DateTime dt1 = DateTime.UtcNow;

        swf = (UniSwf) new BinaryFormatter().Deserialize(new MemoryStream(binAsset.bytes));
        if (!swf.DeserializeCompleted())
          return null;

        NivalCLI.CLI.Debug("Binary data \"{0}\" loaded in {1} ms", fileName, (DateTime.UtcNow - dt1).TotalMilliseconds);
      }
      else
      {
        var swfAsset = Resources.Load(fileName, typeof (TextAsset)) as TextAsset;

        DateTime dt2 = DateTime.UtcNow;

        swf = ReadSwf(swfAsset);

        NivalCLI.CLI.Debug("SWF data \"{0}\" loaded in {1} ms", fileName, (DateTime.UtcNow - dt2).TotalMilliseconds);
      }

      Type type = typeof (T);
      if (type != typeof (MovieClip) && type.GetCustomAttributes(typeof (RootAttribute), false).Length == 0)
      {
        _mainFlashPlayer.gameObject.SetActive(false);
        throw new Exception("Root attribute is not applied to class " + type.Name);
      }

      // Make root
      var rootCharacter = new UniDefineSpriteTag(swf) {Tags = swf.Tags};
      if (constructorArgs == null)
        constructorArgs = new object[] { };
      var root = GetCustomRoot<T>(constructorArgs);
      root.SetAsRoot();
      _stage.AddChild(root);
      root.Push(rootCharacter);

      // Validate Binding for root
      ((IInteractive) root).ValidateBinding();

      // INIT TO ROOT
      ((IInteractive) root).InitInternal();

      FlashInput.Reset();
      _prevScreenWidth = 0;
      _prevScreenHeight = 0;

      _swfs.Add(root, swf);

      swf.Release();
      GarbageCollectorTimer.Collect();

      NivalCLI.Profiler.Stop("PushSWF " + fileName);

      //Profiler.EndSample();

      return root;
    }

    /// <exception>Throws ArgumentException when root is not Root object in hierarchy.</exception>
    public static void UnloadSwf(MovieClip root)
    {
      int index = -1;
      if (!_stage.Children.Contains(ref index, root))
      {
        NivalCLI.CLI.Assert("Does not contain root. Contains Only");
        foreach (DisplayInstance displayInstance in _stage.Children)
        {
          NivalCLI.CLI.Assert(displayInstance.GetType().Name);
        }

        throw new ArgumentException(root.GetType().Name + " is not Root in hierarchy.");
      }

      _stage.RemoveChild(root);
      ((IBindable) root).ControlNode.ReleaseBindChildren();
      root.Character.Swf.Dispose();
      root.Dispose();
      _swfs.Remove(root);

      GarbageCollectorTimer.Collect();
    }

    public static Vector2 WorldToGUISpace(Vector3 worldPosition)
    {
      if (Camera.main == null)
        return worldPosition;

      Vector2 pos = Camera.main.WorldToScreenPoint(worldPosition);
      Vector2 result = new Vector2(pos.x / _scale, _height - pos.y / _scale);
      return result;
    }

    public IEnumerator LoadImageFromUrl(ImageLoader loader)
    {
      yield return loader.Www.SendWebRequest();
      loader.Finished();
    }

    // LoadMovieFromUrl (MovieTexture через WWW.GetMovieTexture) удалён при миграции на Unity 2019:
    // стрим видео по URL теперь делает VideoPlayer.url в MediaPlayer.

    public static Font LoadFont(string name)
    {
      return Resources.Load(FlashEnv.FONTS_PATH + name) as Font;
    }

    public static void AddWebTextureToCache(string url, Texture2D texture)
    {
      _webTexturesDic.Add(url, texture);

      for (int i = _textureCacheHandlers.Count - 1; i > -1; --i)
      {
        if (_textureCacheHandlers[i].Key == url)
        {
          _textureCacheHandlers[i].Value(texture, url);
          _textureCacheHandlers.RemoveAt(i);
        }
      }
    }

    public static void RegisterTextureFromCacheRequest(string url, Action<Texture2D, string> handler)
    {
      _textureCacheHandlers.Add(new KeyValuePair<string, Action<Texture2D, string>>(url, handler));
    }

    private static UniSwf ReadSwf(TextAsset swfAsset)
    {
      var stream = new MemoryStream(swfAsset.bytes);
      var reader = new SwfReader(stream);
      //Profiler.BeginSample( "######## READ SWF ##############" );
      var swf = reader.ReadSwf();
      //Profiler.EndSample();
      //Profiler.BeginSample( "######## NEW UNI SWF ##############" );
      var result = new UniSwf(swf, swfAsset.name, true, false);
      //Profiler.EndSample();
      return result;
    }

    private static void SetupCamera()
    {
      _camera.enabled = true;
      _camera.orthographic = true;
      _camera.clearFlags = CameraClearFlags.Depth;

      UpdateCamera();

      _camera.nearClipPlane = 0;
      _camera.farClipPlane = 1;
      _camera.cullingMask = 0;
      _camera.renderingPath = RenderingPath.VertexLit;
    }

    private static void UpdateCamera()
    {
        if (_width == 0 || _height == 0)
            return;

      _camera.orthographicSize = (float) _height/2;
      _camera.aspect = (float) _width/_height;
      var camPos = new Vector3((float) _width/2, (float) _height/2);

      if (Application.platform == RuntimePlatform.WindowsPlayer || Application.platform == RuntimePlatform.WindowsEditor)
      {
        camPos.x += 0.5f;
        camPos.y += 0.5f;
      }

      _camera.transform.position = camPos;

      _camera.ResetProjectionMatrix();

      // Invert Y
      Matrix4x4 proj = _camera.projectionMatrix;
      proj.m11 = -Math.Abs(proj.m11);
      _camera.projectionMatrix = proj;

      Shader.SetGlobalMatrix("_worldToView", Camera.transform.worldToLocalMatrix);

      _camera.allowHDR = false;
    }

    private static void BuildControlsTree()
    {
      Assembly assembly = typeof (RootAttribute).Assembly;
      Type[] types = assembly.GetTypes();

      foreach (Type type in types)
      {
        if (type.IsSubclassOf(typeof (MovieClip)))
        {
          var attr = type.GetCustomAttributes(typeof (RootAttribute), false) as RootAttribute[];
          if (attr != null && attr.Length > 0)
          {
            ControlsTree tree = null;
            try
            {
              var root = new ControlNode(attr[0].TargetRoot, null, type, null, -1);
              tree = new ControlsTree(root, attr[0].WriteToXml);
            }
            catch (Exception e)
            {
              Debug.LogError(e.Message);
            }

            _trees.Add(tree);
          }
        }
      }

#if UNITY_EDITOR
      foreach (ControlsTree tree in _trees)
        tree.DampTree();
#endif
    }

    private static T GetCustomRoot<T>(object[] constructorArgs) where T : MovieClip
    {
      T result = null;
      ControlNode rootNode = null;

      if (_trees.Count > 0)
      {
        foreach (ControlsTree tree in _trees)
        {
          if (tree.Root.Type == typeof (T))
          {
            rootNode = tree.Root;
            break;
          }
        }
      }

      if (rootNode != null)
      {
        if (rootNode.Bind != null)
        {
          throw new RootAlreadyBindedException();
        }

        var constructorInfo = rootNode.Type.GetConstructor(constructorArgs.Select(a => a.GetType()).ToArray());
        if (constructorInfo != null)
          result = (T)constructorInfo.Invoke(constructorArgs);
        var bindable = (IBindable) result;
        if (bindable != null) bindable.ControlNode = rootNode;
        rootNode.Bind = result;
      }
      else
        result = (T) new MovieClip();

      if (result != null)
        result.Name = "__Root_" + typeof (T).Name;

      return result;
    }

    private static void Freeze()
    {
      if (_width == 0 || _height == 0)
        return;

      int newWidth = 1;
      int newHeight = 1;
      TextureUtils.GetNextPowOfTwo(_width, _height, ref newWidth, ref newHeight);

      if (_freezeTexture == null)
      {
        _freezeTexture = new Texture2D(newWidth, newHeight, TextureFormat.ARGB32, false);
        _freezeTexture.wrapMode = TextureWrapMode.Clamp;
      }
      else
        _freezeTexture.Reinitialize(newWidth, newHeight);

      _dirtyFreezeTex = true;
      // Видимый freeze-оверлей рисует RenderFreeze() (GL + MiscMaterial) каждый кадр с UV-коррекцией pow2.
      // Легаси-GUITexture-оверлей здесь был рудиментом (без позиции/размера/UV) и удалён при миграции на Unity 2019.
    }

    private static void Unfreeze()
    {
      if (_camLayerMask != 0)
        Camera.main.cullingMask = _camLayerMask;
    }

    protected void Update()
    {
      if (_lastFrameRendered && _deviceLost)
      {
        _deviceLost = false;
        CallDeviceObtained();
      }

      if (!_deviceLost && !_lastFrameRendered)
      {
        _deviceLost = true;
        CallDeviceLost();
      }

      _lastFrameRendered = false;
      ResolutionUpdate();
      FlashInput.Update();
    }

    /// <summary>
    /// Fixed updates count without OnPostRender invokes. Limit excess means that d3dDevice was lost(minimized fullscreen window, etc.)
    /// </summary>
    protected void OnGUI()
    {
      FlashInput.OnGUI();
    }

    public void CallDeviceObtained()
    {
      if (DeviceObtained != null)
        DeviceObtained();
    }

    private void CallDeviceLost()
    {
      if (DeviceLost != null)
        DeviceLost();
    }

    protected void OnPostRender()
    {
      _lastFrameRendered = true;
      if (_fullScreenPrev != Screen.fullScreen)
      {
        if (FullScreen != null)
          FullScreen(this, new ResolutionEventArgs(_width, _height));
        StartCoroutine(OnFullScreen());
        StartCoroutine(OnPostFullScreen());
      }
      _fullScreenPrev = Screen.fullScreen;

      FlashInput.Reset();
      PrePender();
      Render();
      PostRender();
    }

    private void PrePender()
    {
      if (_freezeScene && _dirtyFreezeTex && _freezeTexture != null)
        UpdateFreezeTexture();

      // animation
      _stage.UpdateFrame();
    }

    private void Render()
    {
      if (_freezeScene)
        RenderFreeze();

      ClearAlpha(1);

      _stage.PreRender();
    }

    private void PostRender()
    {
      if (_showMouseFocus && FlashInput.TopmostObject != null)
        FlashInput.TopmostObject.DrawBounds(new Color(1, 0, 0, 0.5F), false);

      _stage.CallPostRender();
    }

    protected void DrawMousePosition()
    {
      FlashDebug.DrawMaterial.SetPass(0);
      GL.GetGPUProjectionMatrix(_camera.projectionMatrix, false);
      GL.Begin(GL.QUADS);
      GL.Color(Color.yellow);
      GL.Vertex(new Vector3(FlashInput.MousePosition.x - 4, FlashInput.MousePosition.y - 4));
      GL.Vertex(new Vector3(FlashInput.MousePosition.x + 4, FlashInput.MousePosition.y - 4));
      GL.Vertex(new Vector3(FlashInput.MousePosition.x + 4, FlashInput.MousePosition.y + 4));
      GL.Vertex(new Vector3(FlashInput.MousePosition.x - 4, FlashInput.MousePosition.y + 4));
      GL.End();
    }

    protected void OnApplicationFocus(bool focus)
    {
      if (focus && _deviceLost)
      {
        _deviceLost = false;
        CallDeviceObtained();
      }

      if (!_deviceLost && !focus)
      {
        _deviceLost = true;
        CallDeviceLost();
      }

      FlashInput.Enabled = _focused = focus;
      if (_focused)
      {
        Input.ResetInputAxes();
        FlashInput.InvalidateCursorState();
        StartCoroutine(OnFullScreen());
        if (Application.isEditor && MaterialsReseted != null)
          MaterialsReseted();
      }
    }

    private IEnumerator OnFullScreen()
    {
      yield return new WaitForEndOfFrame();
    }

    private IEnumerator OnPostFullScreen()
    {
      yield return new WaitForEndOfFrame();

      if (PostFullScreen != null)
        PostFullScreen(this, new ResolutionEventArgs(_width, _height));
    }

    private void RenderFreeze()
    {
      if (_width == 0 || _height == 0)
        return;

      if (FlashDebug.MiscMaterial)
      {
        FlashDebug.MiscMaterial.mainTexture = _freezeTexture;
        FlashDebug.MiscMaterial.SetPass(0);
        GL.GetGPUProjectionMatrix(_camera.projectionMatrix, false);
        // Because of pow of 2 texture extending
        float v = (float) _height/_freezeTexture.height;
        float u = (float) _width/_freezeTexture.width;
        GL.Begin(GL.QUADS);
        GL.Color(Color.white);
        GL.TexCoord(new Vector3(0, 1 - v));
        GL.Vertex(new Vector3(0, _height));
        GL.TexCoord(new Vector3(u, 1 - v));
        GL.Vertex(new Vector3(_width, _height));
        GL.TexCoord(new Vector3(u, 1));
        GL.Vertex(new Vector3(_width, 0));
        GL.TexCoord(new Vector3(0, 1));
        GL.Vertex(new Vector3(0, 0));
        GL.End();
      }
    }

    private void ClearAlpha(float alpha)
    {
      if (_width == 0 || _height == 0)
        return;

      if (FlashDebug.MiscMaterial)
      {
        FlashDebug.MiscMaterial.SetPass(1);
        GL.GetGPUProjectionMatrix(_camera.projectionMatrix, false);
        GL.Begin(GL.QUADS);
        GL.Color(new Color(0, 0, 0, alpha));
        GL.Vertex(new Vector3(0, _height));
        GL.Vertex(new Vector3(_width, _height));
        GL.Vertex(new Vector3(_width, 0));
        GL.Vertex(new Vector3(0, 0));
        GL.End();
      }
    }

    private void UpdateFreezeTexture()
    {
      if (_width == 0 || _height == 0)
        return;

      _freezeTexture.ReadPixels(new Rect(0, 0, _width, _height), 0, _freezeTexture.height - _height,
        false);
      _freezeTexture.Apply();
      if (Camera.main != null)
        if (Camera.main.cullingMask != 0)
        {
          _camLayerMask = Camera.main.cullingMask;
          Camera.main.cullingMask = 0;
        }
      _dirtyFreezeTex = false;
    }

    private void ResolutionUpdate()
    {
      if (_freezeScene && Camera.main != null && Camera.main.cullingMask != 0)
      {
        Freeze();
      }

      bool isResolutionChanged = (Screen.width != _prevScreenWidth || Screen.height != _prevScreenHeight) ||
          (Application.isEditor && TestScale != _testScale);

      if (isResolutionChanged)
      {
        if (Application.isEditor)
        {
          _testScale = TestScale;
          if (Mathf.Abs(_testScale) < TestScaleBias)
          {
            _scale = 1f;
          }
          else if (_testScale < 0f)
          {
            _scale = 1f / (1f - _testScale);
          }
          else
          {
            _scale = 1f + _testScale;
          }
        }
        else
        {
          _scale = Screen.height > MaxHeight ? (float)Screen.height / (float)MaxHeight : 1f;
        }

        if (_scale == 1f)
        {
          _width = Screen.width;
          _height = Screen.height;
        }
        else
        {
          _width = Mathf.RoundToInt((float)Screen.width / _scale);
          _height = Mathf.RoundToInt((float)Screen.height / _scale);
        }

        _whAspect = (float)_width / (float)_height;

        UpdateCamera();
        if (_freezeScene)
        {
          Unfreeze();
          Freeze();
        }
        if (ResolutionChanged != null)
          ResolutionChanged(this, new ResolutionEventArgs(_width, _height));
      }

      _prevScreenWidth = Screen.width;
      _prevScreenHeight = Screen.height;
    }

    public static Vector2 ScreenSpace2FlashSpace(Vector2 ss_pos)
    {
      return new Vector2(
        ss_pos.x * Width / Screen.width,
        (Screen.height - ss_pos.y) * Height / Screen.height);
    }

    public class FlashDebug
    {
      private static Material _drawMaterial;

      public static Material DrawMaterial
      {
        get
        {
          if (!_drawMaterial)
          {
            // PF-102388 при переходе на 5.3.4 сломались шейдеры, используем стандартный
            _drawMaterial = new Material(Shader.Find("Unlit/ColorCustom"))
            {
              hideFlags = HideFlags.HideAndDontSave,
              shader = {hideFlags = HideFlags.HideAndDontSave}
            };

            /*_drawMaterial = new Material("Shader \"Lines/Colored Blended\" {" +
                                                                 "SubShader { Pass { " +
                                                                 " Blend SrcAlpha OneMinusSrcAlpha " +
                                                                 " ZWrite Off ZTest Always Cull Off Fog { Mode Off } " +
                                                                 " BindChannels {" +
                                                                 " Bind \"Vertex\", vertex Bind \"Color\", color }" +
                                                                 "} } }" );*/
          }

          return _drawMaterial;
        }
      }

      private static Material _miscMaterial;

      public static Material MiscMaterial
      {
        get
        {
          if (!_miscMaterial)
          {
            var shader = Shader.Find("Flash/DebugShader");
            if (shader != null)
            {
              _miscMaterial = new Material(shader);
              _miscMaterial.hideFlags = HideFlags.HideAndDontSave;
            }
          }
          return _miscMaterial;
        }
      }
    }
  }

  internal class RootAlreadyBindedException : Exception { }
}
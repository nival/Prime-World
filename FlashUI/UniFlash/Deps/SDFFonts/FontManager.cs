using System.Collections.Generic;
using System.Linq;
using Flash;
using SDFFonts.UniFlash;
using UnityEngine;
using UnityEngine.Assertions;

using Font = SDFFonts.Font;

namespace SDFFonts
{
  public class FontManager : MonoBehaviour
  {
    [SerializeField]
    private List<Font> _fonts;

    private static FontManager _instance;
    private readonly List<StorageInstance> _flashFonts = new List<StorageInstance>();

    public static FontManager Instance { get { return _instance; } }

    public static bool IsLegacyLineSpacing { get { return _instance._isLegacyLineSpacing; } }
    public static float OverrideLetterSpacing { get { return _instance._overrideLetterSpacing; } }

    [Range(0f, 1f)]
    public float SDFMedian = 0.48f;
    [Range(0f, 0.5f)]
    public float SDFSmooth = 0.25f;
    [Range(0f, 0.3f)]
    public float SDFOutlineWidth = 0.1f;
    [Range(0f, 0.3f)]
    public float SDFOutlineSmooth = 0.15f;

    [SerializeField]
    private bool _isLegacyLineSpacing = false;
    [SerializeField]
    private float _overrideLetterSpacing = 0f;

    private float _pSDFMedian;
    private float _pSDFSmooth;
    private float _pSDFOutlineWidth;
    private float _pSDFOutlineSmooth;

    private IconCache _iconCache;

    public void Init()
    {
      _instance = this;

#if SDFFONT
      Assert.IsTrue(_fonts != null && _fonts.Count > 0);
      _fonts.ForEach(
              f => f.LoadFont()
      );

      SetShaderParams();

      _iconCache = new IconCache();
#endif
    }

#if SDFFONT && UNITY_EDITOR
    void Update()
    {
      if (!Mathf.Approximately(_pSDFMedian, SDFMedian)
       || !Mathf.Approximately(_pSDFSmooth, SDFSmooth)
       || !Mathf.Approximately(_pSDFOutlineSmooth, SDFOutlineSmooth)
       || !Mathf.Approximately(_pSDFOutlineWidth, SDFOutlineWidth))
      {
        SetShaderParams();

        _pSDFMedian = SDFMedian;
        _pSDFSmooth = SDFSmooth;
        _pSDFOutlineWidth = SDFOutlineWidth;
        _pSDFOutlineSmooth = SDFOutlineSmooth;
      }
    }
#endif

    private void SetShaderParams()
    {
      Shader.SetGlobalFloat("_SDF_Median", SDFMedian);
      Shader.SetGlobalFloat("_SDF_Smooth", SDFSmooth);
      Shader.SetGlobalFloat("_SDF_OutlineWidth", SDFOutlineWidth);
      Shader.SetGlobalFloat("_SDF_OutlineSmooth", SDFOutlineSmooth);
    }

    public IFontStorage GetFontStorage(string name, FontStyle style, int size)
    {
      StorageInstance storage = _flashFonts.FirstOrDefault(
          s => s.Name == name && s.Style == style && s.Size == size
      );
      if (storage == null)
      {
        storage = InitFontStorage(name, style, size);
      }
      return storage;
    }

    public Font this[string name, FontStyle style] {
      get {
        Font font = _fonts.FirstOrDefault(
            f => f.FontName == name && f.FontStyle == style
        );
        return font != null ? font : _fonts[0];
      }
    }

    private StorageInstance InitFontStorage(string name, FontStyle style, int size)
    {
      Font font = this[name, style];
      StorageInstance storage = new StorageInstance(name, font, size, _iconCache);
      _flashFonts.Add(storage);
      return storage;
    }
  }
}

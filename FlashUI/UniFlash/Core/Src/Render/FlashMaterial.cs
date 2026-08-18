using UnityEngine;

namespace Flash.Render
{
  public enum BlendModePin
  {
    Normal = 0,
    Add = 1,
    Alpha = 2,
  }

  public enum FillTypePin
  {
    Solid = 0,
    Bitmap = 1,
    RadialGradient = 2,
    Line = 3,
  }

  public enum BooleanPin
  {
    None = 0,
    Present = 1,
  }

	public class FlashMaterial
	{
    public static Material LastRenderedMaterial { get; set; }

    public int Kind { get; protected set; }

    public FlashMaterial(Material source)
    {
      RenderMaterial = new Material(source);
      InitFields(); 
    }
    public FlashMaterial(Shader shader)
    {
      RenderMaterial = new Material(shader);
      InitFields(); 
    }
    public Material RenderMaterial { get; set; }

    private void InitFields()
    {
      ConcatenatedAlpha = 1;
      RenderMaterial.SetFloat("_Alpha", ConcatenatedAlpha);

      HasColorTransform = false;
      RenderMaterial.SetColor("_Color", Color.white);
      RenderMaterial.SetColor("_AddColor", Color.clear);

      HasColorMatrix = false;
      RenderMaterial.SetMatrix("_colorMatrix_mul", Matrix4x4.identity);
      RenderMaterial.SetVector("_colorMatrix_add", Vector4.zero);

      RenderMaterial.SetColor("_GlowColor", Color.clear);
      GlowColor = Color.clear;
      MaskDepth = 1;

      HasScaleGrid = false;
      ScaleGridMatrix = Matrix4x4.identity;
    }

    public float ConcatenatedAlpha { get; set; }
    public bool HasColorTransform { get; set; }
    public bool HasColorMatrix { get; set; }
    public Color GlowColor { get; set; }
    public float MaskDepth { get; set; }

    public bool HasScaleGrid { get; set; }
    public Matrix4x4 ScaleGridMatrix { get; set; }

    public void Release() 
    {
      Material.Destroy(RenderMaterial);
    }

    public void SetPass()
    {
      RenderMaterial.SetPass(GetCurrentPass());
    }

    // ubershading

    public virtual BlendModePin Pin_BlendMode { get { return 0; } set { } }

    public virtual BooleanPin Pin_HasColorMatrix { get { return 0; } set { } }

    public virtual BooleanPin Pin_HasScaleGrid { get { return 0; } set { } }

    public virtual BooleanPin Pin_IsMask { get { return 0; } set { } }

    public virtual BooleanPin Pin_EnableWrap { get { return 0; } set { } }

    public virtual FillTypePin Pin_FillType { get { return 0; } set { } }

    protected virtual int GetCurrentPass() { return 0; }

  }
}

using UnityEngine;
using Flash.Render;

namespace Flash
{
  public class MorphShape : DisplayObject
  {
    private Bounds _localBoundsStart;
    public Bounds LocalBoundsStart
    {
      get { return _localBoundsStart; }
      private set { _localBoundsStart = value; }
    }
    private Bounds _localBoundsEnd;
    public Bounds LocalBoundsEnd
    {
      get { return _localBoundsEnd; }
      private set { _localBoundsEnd = value; }
    }

   
    public override void Push(UniBaseTag character)
    {
      base.Push(character);

      LocalBoundsStart = ((UniDefineMorphShapeTag)character).LocalBoundsStart;
      LocalBoundsEnd = ((UniDefineMorphShapeTag)character).LocalBoundsEnd;
    }

    public override void PreRender()
    {
      base.PreRender();
      UpdateLocalBounds();
    }

    public override void UpdateLocalBounds()
    {
      LocalBounds = Bounds.Lerp(LocalBoundsStart, LocalBoundsEnd, Transform.Ratio);
    }

    protected override void SetupMaterialProperty(FlashMaterial material, RenderableElement element)
    {
      base.SetupMaterialProperty(material, element);

      MorphElement morphElement = (MorphElement)element;
      material.RenderMaterial.SetFloat("_t", Transform.Ratio);
      material.RenderMaterial.SetFloat("_focalPoint", Mathf.Lerp(morphElement.StartFillFocalPoint, morphElement.EndFillFocalPoint, Transform.Ratio));

      if (morphElement.StartFillTextureTransform != null)
      {
        material.RenderMaterial.SetMatrix("_LerpBitmapMatrix", TextureTransform.Slerp(morphElement.StartFillTextureTransform,
                                                                 morphElement.EndFillTextureTransform,
                                                                 Transform.Ratio));
      }
    }
  }
}

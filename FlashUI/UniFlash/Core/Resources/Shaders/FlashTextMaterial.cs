// Automatically generated file, don't change it manually!
using UnityEngine;

namespace Flash.Render
{

public class FlashTextMaterial : FlashMaterial
{
  public FlashTextMaterial():
    base(Shader.Find( "Flash/TextShaderNew" ))
  {
    this._BlendMode = (BlendModePin)0;
    this._HasColorMatrix = (BooleanPin)0;
    this._HasScaleGrid = (BooleanPin)0;
    this._IsMask = (BooleanPin)0;
    Kind = 0;
  }

  public FlashTextMaterial(string shaderName):
    base(Shader.Find(name: shaderName))
  {
    this._BlendMode = (BlendModePin)0;
    this._HasColorMatrix = (BooleanPin)0;
    this._HasScaleGrid = (BooleanPin)0;
    this._IsMask = (BooleanPin)0;
    Kind = 1;
  }

  private BlendModePin _BlendMode;
  public override BlendModePin Pin_BlendMode { get { return _BlendMode; } set { _BlendMode = value; } }

  private BooleanPin _HasColorMatrix;
  public override BooleanPin Pin_HasColorMatrix { get { return _HasColorMatrix; } set { _HasColorMatrix = value; } }

  private BooleanPin _HasScaleGrid;
  public override BooleanPin Pin_HasScaleGrid { get { return _HasScaleGrid; } set { _HasScaleGrid = value; } }

  private BooleanPin _IsMask;
  public override BooleanPin Pin_IsMask { get { return _IsMask; } set { _IsMask = value; } }

  protected override int GetCurrentPass()
  {
    return  (int)_BlendMode*1 + (int)_HasColorMatrix*3 + (int)_HasScaleGrid*6 + (int)_IsMask*12 ;
  }
}

}

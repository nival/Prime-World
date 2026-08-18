// Automatically generated file, don't change it manually!
using UnityEngine;

namespace Flash.Render
{

public class FlashMorphMaterial : FlashMaterial
{
  public FlashMorphMaterial():
    base(Shader.Find( "Flash/MorphShaderNew" ))
  {
    this._BlendMode = (BlendModePin)0;
    this._EnableWrap = (BooleanPin)1;
    this._FillType = (FillTypePin)0;
    this._HasColorMatrix = (BooleanPin)0;
    this._HasScaleGrid = (BooleanPin)0;
    this._IsMask = (BooleanPin)0;
  }

  private BlendModePin _BlendMode;
  public override BlendModePin Pin_BlendMode { get { return _BlendMode; } set { _BlendMode = value; } }

  private BooleanPin _EnableWrap;
  public override BooleanPin Pin_EnableWrap { get { return _EnableWrap; } set { _EnableWrap = value; } }

  private FillTypePin _FillType;
  public override FillTypePin Pin_FillType { get { return _FillType; } set { _FillType = value; } }

  private BooleanPin _HasColorMatrix;
  public override BooleanPin Pin_HasColorMatrix { get { return _HasColorMatrix; } set { _HasColorMatrix = value; } }

  private BooleanPin _HasScaleGrid;
  public override BooleanPin Pin_HasScaleGrid { get { return _HasScaleGrid; } set { _HasScaleGrid = value; } }

  private BooleanPin _IsMask;
  public override BooleanPin Pin_IsMask { get { return _IsMask; } set { _IsMask = value; } }

  protected override int GetCurrentPass()
  {
    return  (int)_BlendMode*1 + (int)_EnableWrap*3 + (int)_FillType*6 + (int)_HasColorMatrix*24 + (int)_HasScaleGrid*48 + (int)_IsMask*96 ;
  }
}

}

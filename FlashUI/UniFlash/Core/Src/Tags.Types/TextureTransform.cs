using Flash.Utils;
using UnityEngine;
using System.Runtime.Serialization;

namespace Flash
{
  [System.Serializable]
  public class TextureTransform : ISerializable
  {
    private Vector3 _position = Vector3.zero;
    private Quaternion _rotation = Quaternion.identity;
    private Vector3 _scale = Vector3.one;
    private float _shearXY;
    private Matrix4x4 _texSpaceMatrix = Matrix4x4.identity;

    public void GetObjectData(SerializationInfo info, StreamingContext context) {
        Flash.SerializeHelpers.Pack(info, "_position", _position);
        Flash.SerializeHelpers.Pack(info, "_rotation", _rotation);            
        Flash.SerializeHelpers.Pack(info, "_scale", _scale);
        Flash.SerializeHelpers.Pack(info, "_shearXY", _shearXY);            
        Flash.SerializeHelpers.Pack(info, "_texSpaceMatrix", _texSpaceMatrix);
    }
        
    public TextureTransform(SerializationInfo info, StreamingContext context) {
        Flash.SerializeHelpers.Unpack(info, "_position", out _position);
        Flash.SerializeHelpers.Unpack(info, "_rotation", out _rotation);            
        Flash.SerializeHelpers.Unpack(info, "_scale", out _scale);
        Flash.SerializeHelpers.Unpack(info, "_shearXY", out _shearXY);            
        Flash.SerializeHelpers.Unpack(info, "_texSpaceMatrix", out _texSpaceMatrix);
    }

    public static Matrix4x4 Slerp(TextureTransform start, TextureTransform end, float t)
    {
      Matrix4x4 result = Matrix4x4.identity;

      Matrix4x4 lerpTexSpace = Matrix4x4.identity;

      lerpTexSpace[0, 0] = Mathf.Lerp(start._texSpaceMatrix[0, 0], end._texSpaceMatrix[0, 0], t);
      lerpTexSpace[1, 1] = Mathf.Lerp(start._texSpaceMatrix[1, 1], end._texSpaceMatrix[1, 1], t);
      lerpTexSpace[0, 3] = Mathf.Lerp(start._texSpaceMatrix[0, 3], end._texSpaceMatrix[0, 3], t);
      lerpTexSpace[1, 3] = Mathf.Lerp(start._texSpaceMatrix[1, 3], end._texSpaceMatrix[1, 3], t);

      Matrix4x4 lerpRotation = Matrix4x4.TRS(Vector3.zero, Quaternion.Slerp(start._rotation, end._rotation, t), Vector3.one);

      Matrix4x4 lerpScale = Matrix4x4.Scale(Vector3.Lerp(start._scale, end._scale, t));

      Matrix4x4 lerpShear = Matrix4x4.identity;
      lerpShear[0, 1] = Mathf.Lerp(start._shearXY, end._shearXY, t);

      Matrix4x4 lerpTranslate = Matrix4x4.TRS(Vector3.Lerp(start._position, end._position, t), Quaternion.identity,
                                              Vector3.one);

      result = lerpTexSpace * lerpScale * lerpShear * lerpRotation * lerpTranslate;

      return result;
    }

    public TextureTransform() { }
    public TextureTransform(DecomposedMatrix decomposed, Matrix4x4 textureSpace)
    {
      _position = decomposed.position;
      _rotation = Quaternion.Euler(decomposed.rotation);
      _scale = new Vector3(1.0F / decomposed.scale.x, 1.0F / decomposed.scale.y, 1.0F / decomposed.scale.z);
      _shearXY = decomposed.shearXY;
      _texSpaceMatrix = textureSpace;
    }
  }
}
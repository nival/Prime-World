using UnityEngine;

namespace Flash.Controls
{
  interface IDragIcon
  {
    string Image { get; set; }

    float X { get; set; }
    float Y { get; set; }
    float Width { get; set; }
    float Height { get; set; }

    Vector2 GlobalToLocal( Vector3 point );
    Vector2 LocalToGlobal( Vector3 point );
  }
}

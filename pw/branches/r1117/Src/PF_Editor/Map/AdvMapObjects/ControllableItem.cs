using System;
using DBTypes;
using EditorNative;

namespace PF_Editor.Map.AdvMapObjects
{
  public sealed class ControllableItem : IDisposable
  {
    private readonly AdvMapObject advMapObject = null;
    private readonly PointLightInfo pointLight = null;
    private readonly ScriptArea scriptArea = null;

    public ControllableItem(AdvMapObject obj)
    {
      advMapObject = obj;
      advMapObject.Changed += new EventHandler(advMapObject_Changed);
    }

    public ControllableItem(PointLightInfo obj)
    {
      pointLight = obj;
      pointLight.Changed += new EventHandler(pointLight_Changed);
    }

    public ControllableItem( ScriptArea obj )
    {
      scriptArea = obj;
      scriptArea.Changed += new EventHandler( scriptArea_Changed );
    }

    public PointLightInfo GetPointLightInfo()
    {
      return pointLight;
    }

    public ScriptArea GetScriptArea()
    {
      return scriptArea;
    }

    private void pointLight_Changed(object sender, EventArgs e)
    {
      if (Changed != null)
        Changed(sender, e);
    }

    private void advMapObject_Changed(object sender, EventArgs e)
    {
      if (Changed != null)
        Changed(sender, e);
    }

    private void scriptArea_Changed( object sender, EventArgs e )
    {
      if ( Changed != null )
        Changed( sender, e );
    }

    public event EventHandler Changed;

    public Vec3 Location
    {
      get 
      { 
        if (advMapObject != null)
        {
          Vec3 location = new Vec3();
          location.x = advMapObject.offset.translateX;
          location.y = advMapObject.offset.translateY;
          location.z = advMapObject.offset.translateZ;
          return location;
        }
        else if ( pointLight != null )
        {
          return pointLight.location;
        }
        else
        {
          Vec3 location = new Vec3();
          location.x = scriptArea.position.x;
          location.y = scriptArea.position.y;
          location.z = 0;
          return location;
        }
      }
      set
      {
        if ( advMapObject != null )
        {
          advMapObject.offset.translateX = value.x;
          advMapObject.offset.translateY = value.y;
          advMapObject.offset.translateZ = value.z;
        }
        else if ( pointLight != null )
        {
          pointLight.location = value;
        }
        else
        {
          scriptArea.position.x = value.x;
          scriptArea.position.y = value.y;
        }
      }
    }

    public Quat Rotation
    {
      get
      {
        if (advMapObject != null)
        {
          Placement place = new Placement();
          PlacementConverter converter = new PlacementConverter();
          converter.convertPlacement( advMapObject.offset, place );
          Quat quat = new Quat();
          quat.x = place.rotation.x;
          quat.y = place.rotation.y;
          quat.z = place.rotation.z;
          quat.w = place.rotation.w;
          return quat;
        }
        else
        {
          return new Quat(null);
        }
      }
      set
      {
        if ( advMapObject != null )
        {
          Placement place = new Placement();
          PlacementConverter converter = new PlacementConverter();
          converter.convertPlacement( advMapObject.offset, place );
          place.rotation.x = value.x;
          place.rotation.y = value.y;
          place.rotation.z = value.z;
          place.rotation.w = value.w;
          converter.convertPlacement( place, advMapObject.offset );
        }
      }
    }

    public Scale Scale
    {
      get
      {
        Scale scale = new Scale();
        if (advMapObject != null)
        {
          scale.x = advMapObject.offset.scaleX;
          scale.y = advMapObject.offset.scaleY;
          scale.z = advMapObject.offset.scaleZ;
        }
        else if ( pointLight != null )
        {
          scale.x = pointLight.range;
          scale.y = pointLight.range;
          scale.z = pointLight.range;
        }
        return scale;
      }
      set
      {
        if ( advMapObject != null )
        {
          advMapObject.offset.scaleX = value.x;
          advMapObject.offset.scaleY = value.y;
          advMapObject.offset.scaleZ = value.z;
        }
        else if ( pointLight != null )
        {
          if ( value.x >= 0.0f && value.y >= 0.0f && value.z >= 0.0f )
          {
            if ( value.x != pointLight.range )
            {
              pointLight.range = value.x;
              return;
            }
            else if ( value.y != pointLight.range )
            {
              pointLight.range = value.y;
              return;
            }
            else if ( value.z != pointLight.range )
            {
              pointLight.range = value.z;
              return;
            }
          }
        }
      }
    }

    public object Resource
    {
      get 
      {
        if (advMapObject != null)
        {
          return advMapObject;
        }
        else if ( pointLight != null )
        {
          return pointLight;
        }
        else
        {
          return scriptArea;
        }
      }
    }

    public void Dispose()
    {
      if ( advMapObject != null )
        advMapObject.Changed -= advMapObject_Changed;

      if ( pointLight != null )
        pointLight.Changed -= pointLight_Changed;

      if ( scriptArea != null )
        scriptArea.Changed -= scriptArea_Changed;

      GC.SuppressFinalize( this );
    }

    ~ControllableItem()
    {
      Dispose();
    }
  }
}